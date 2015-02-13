#include "level.h"
#include "game.h"
#include "dialogBox.h"
#include <QGraphicsTextItem>
#include <QDebug>
#include <QTextCodec>

extern Game * game;

//�����������
Level::Level(QGraphicsView *parent) : QGraphicsScene(parent)
{

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));

    //���������� �������������� ��������� �����
    PLAYER_HEIGHT = game->CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    ENEMY_HEIGHT = game->CELL_SIZE * 3;
    ENEMY_WIDTH = ENEMY_HEIGHT * 1.5;

    numberOfEnemies = 0;
    connect(this, SIGNAL(win()), game, SLOT(nextLevel()));
    connect(this, SIGNAL(lose()), game, SLOT(resetLevel()));
}

//�������� ����� �� ������� �����
void Level::init(QString map[])
{
    //������������ ���
    QStringList colors = map[2].split(' ');
    setBackgroundBrush(QBrush(QColor(colors[0].toInt(), colors[1].toInt(), colors[2].toInt())));

    //������ ������, ������� ����� ��������� ���������
    updateTimer = new QTimer(this);

    //�������� ���������� �� ������� �����
    short sceneLength = 0;
    for (int row = 4; row < 20; row++)
    {
        //���������� ����� ����� �� ����� ������� ������
        if (map[row].length() > sceneLength)
        {
            sceneLength = map[row].length();
        }
        //������� ������
        for (int column = 0; column < map[row].length(); column++)
        {
            //��������� ������
            if (map[row][column] == 'p')
            {
                player = new Player(":/img/dasha");
                float scaleFactor = PLAYER_HEIGHT / player->boundingRect().height();
                player->setScale(scaleFactor);
                player->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - PLAYER_HEIGHT);
                player->setZValue(10);
                addItem(player);
                connect(updateTimer, SIGNAL(timeout()), player, SLOT(move()));
            }
            //��������� ����������
            if (map[row][column] == 'v')
            {
                enemy[numberOfEnemies] = new Enemy(":/img/van/", this);
                float scaleFactor = ENEMY_HEIGHT / enemy[numberOfEnemies]->boundingRect().height();
                enemy[numberOfEnemies]->setScale(scaleFactor);
                enemy[numberOfEnemies]->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - ENEMY_HEIGHT);
                addItem(enemy[numberOfEnemies]);
                connect(updateTimer, SIGNAL(timeout()), enemy[numberOfEnemies], SLOT(move()));

                numberOfEnemies++;
            }
            //��������� ������
            if (map[row][column] == 't')
            {
                Cell * target = new Cell(":/img/ground", 0, this);
                float scaleFactor = game->CELL_SIZE / target->boundingRect().width();
                target->setScale(scaleFactor);
                target->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                target->isTarget = true;
                target->setOpacity(0);
                addItem(target);
            }
            //��������� ����
            if (map[row][column] == 'f')
            {
                Cell * floor = new Cell(":/img/ground", 0, this);
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //��������� ����
            if (map[row][column] == 'g')
            {
                Cell * floor = new Cell(":/img/ground", 1, this);
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //��������� ����
            if (map[row][column] == 'y')
            {
                Cell * floor = new Cell(":/img/ground", 2, this);
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //��������� ��������� ����
            if (map[row][column] == 'w')
            {
                Cell * wall = new Cell(":/img/ground", 0, this);
                float scaleFactor = game->CELL_SIZE / wall->boundingRect().width();
                wall->setScale(scaleFactor);
                wall->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                wall->isSolid = true;
                wall->setOpacity(0);
                addItem(wall);
            }
            //��������� ��������� - �����������
            if (map[row][column] == 'h')
            {
                Cell * hydrant = new Cell(":/img/hydrant", 0, this);
                float scaleFactor = game->CELL_SIZE / hydrant->boundingRect().width();
                hydrant->setScale(scaleFactor);
                hydrant->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                hydrant->isSolid = true;
                hydrant->addInteraction('h');
                hydrant->setCellActive();
                hydrant->interactionDialogue[0] = QString("����� � �� ���� ��� ������ �������...");
                addItem(hydrant);
            }
            //��������� ������� ���������
            if (map[row][column] == 'H')
            {
                Cell * hydrant = new Cell(":/img/hydrant", 0, this);
                float scaleFactor = game->CELL_SIZE / hydrant->boundingRect().width();
                hydrant->setScale(scaleFactor);
                hydrant->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                hydrant->addInteraction('h');
                hydrant->setCellActive();
                hydrant->interactionDialogue[0] = QString("����� � �� ���� ��� ������ �������...");
                addItem(hydrant);
            }
            //��������� ���������� ��� ������
            if (map[row][column] == 'n')
            {
                Cell * van_ns = new Cell(":/img/van_ns", 0, this);
                float scaleFactor = game->CELL_SIZE * 4 / van_ns->boundingRect().height();
                van_ns->setScale(scaleFactor);
                van_ns->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * van_ns->boundingRect().height());
                van_ns->addInteraction('n');
                van_ns->setCellActive();
                van_ns->interactionDialogue[0] = QString("��� ������ ����������� ��������.");
                addItem(van_ns);
                van_ns->setZValue(2);
            }
            //��������� ������� ������
            if (map[row][column] == 'b')
            {
                Cell * bush = new Cell(":/img/bush", 0, this);
                float scaleFactor = (float)game->CELL_SIZE * 3 / bush->boundingRect().height();
                bush->setScale(scaleFactor);
                bush->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * bush->boundingRect().height());
                addItem(bush);
            }
            //��������� ������� ������
            if (map[row][column] == 'B')
            {
                Cell * bush = new Cell(":/img/bush", 1, this);
                float scaleFactor = (float)game->CELL_SIZE * 3 / bush->boundingRect().height();
                bush->setScale(scaleFactor);
                bush->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * bush->boundingRect().height());
                addItem(bush);
            }
            //��������� ������
            if (map[row][column] == 's')
            {
                Cell * ball = new Cell(":/img/ball", 0, this);
                float scaleFactor = game->CELL_SIZE / ball->boundingRect().height();
                ball->setScale(scaleFactor);
                ball->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                ball->addInteraction('s');
                ball->setCellActive();
                ball->interactionDialogue[0] = QString("��� ����� ��� ��� � ��������. ��� �� ����� ������?..");
                addItem(ball);
                ball->setZValue(-1);
            }

            //��������� ������ ��� ������
            if (map[row][column] == 'c')
            {
                Cell * cell = new Cell(":/img/cell", 0, this);
                float scaleFactor = (float)game->CELL_SIZE * 5 / cell->boundingRect().height();
                cell->setScale(scaleFactor);
                cell->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * cell->boundingRect().height());
                cell->addInteraction('c');
                cell->setCellActive();
                cell->interactionDialogue[0] = QString("�������, ��� ����� - ������������ ������ ��������� �� ������.");
                cell->interactionDialogue[1] = QString("...��� ���� ������ ������ ������� �������?");
                addItem(cell);
            }
            //��������� �-�� ��������
            if (map[row][column] == 'o')
            {
                Cell * mr = new Cell(":/img/ogurtsov", 0, this);
                float scaleFactor = (float)PLAYER_HEIGHT / mr->boundingRect().height();
                mr->setScale(scaleFactor);
                mr->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * mr->boundingRect().height());
                mr->addInteraction('o');
                mr->setCellActive();
                mr->interactionDialogue[0] = QString("� ������ ����, �������� �������. ������� ����������� ����� ����������.");
                mr->interactionDialogue[1] = QString("��� �� �������� �������?");
                mr->interactionDialogue[2] = QString("� ��. ���� � ���, ��� ������� ����� �� ����� ������ ������ ��������� ������.");
                mr->interactionDialogue[3] = QString("����� ���, ������� ��� ������!");
                mr->interactionDialogue[4] = QString("� �� ������� �� ���������. �������, � ���� ���� ����� �� ������?");
                mr->interactionDialogue[5] = QString("� � ������ �������.");
                mr->interactionDialogue[6] = QString("� ���� � � ��� ������������?");
                mr->interactionDialogue[7] = QString("� �����, ��� ���. ������� �� �� ����� �� ������.");
                mr->interactionDialogue[8] = QString("� ���������...");
                addItem(mr);
            }
        }
    }

    //��������� ������ ����
    clues = map[20];
    clues.remove(' ');

    //��������� ��������� � ��������� ��������� ������
    int i;
    for (i = 22; i < 32; i++)
    {
        if (map[i] == QString("---")) break;
        startMessage[i - 22] = map[i];
    }
    startMessage[i - 22] = "";

    i++;
    int j;
    for (j = i; j < i + 10; j++)
    {
        if (map[j] == QString("---")) break;
        endMessage[j - i] = map[j];
    }
    qDebug() << QString::number(j-i);
    endMessage[j - i] = "";

    //���������� ������� �����
    setSceneRect(0, 0, sceneLength * game->CELL_SIZE, game->WINDOW_HEIGHT);

    //������������� ������ � ��������� ������ �������
    game->setScene(this);
    game->centerOn(player);

    //������ ���������� ����
    dialog = new DialogBox();
    addItem(dialog);
    dialog->setParent(this);
    connect(player, SIGNAL(investigating(Cell*)), dialog, SLOT(setDialog(Cell*)));
    connect(dialog, SIGNAL(ended(Cell*)), player, SLOT(addClue(Cell*)));

    //��������� ������, ����������� ���������
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    connect(updateTimer, SIGNAL(timeout()), dialog, SLOT(move()));
    updateTimer->start(20);

    //�������� ���������� �������
    dialog->setDialog(startMessage);
    qDebug() << endMessage[5];
}

//���������� � ������ �������
void Level::gameOver(QString comment)
{
    updateTimer->stop();
    emit lose();
}

void Level::levelCompleted(QString message[])
{
    updateTimer->stop();
    dialog->setDialog(message);
    connect (dialog, SIGNAL(ended()), this, SIGNAL(win()));
}

//����� �������� ������
void Level::checkRules()
{
}

//��������� ������� ������
void Level::keyPressEvent(QKeyEvent *event)
{
    //����� ��������� �������
    if (dialog->isOn == true)
    {
        switch (event->key())
        {
        //��������� �������
        case (Qt::Key_Space):
            dialog->nextLine();
            break;

        //����� �� �������
        case (Qt::Key_Escape):
            dialog->skip();
            break;

        //� ��������� ������ ���������� �������
        default:
            break;
        }

    //������� ����� ����
    } else
    {
        switch (event->key())
        {
        //����� �� ����
        case (Qt::Key_Escape):
            game->close();
            break;

        //������� ���������� ���������
        default:
            player->keyPressEvent(event);
            break;
        }
    }
}

//��������� ���������� �������
void Level::keyReleaseEvent(QKeyEvent *event)
{
    player->keyReleaseEvent(event);
}
