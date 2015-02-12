#include "player.h"
#include "cell.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QList>
#include <typeinfo>
#include <math.h>
#include <float.h>
#include <game.h>
#include <QVector>
#include <QPointF>
#include <QPolygonF>

extern Game * game;

//����������� ������
Player::Player(QString dir, QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    clues = "";

    JUMP_SPEED = ceil(float(game->CELL_SIZE) / 3.5);
    WALK_SPEED = ceil(float(game->CELL_SIZE) / 8);
    RUN_SPEED = ceil(float(game->CELL_SIZE) / 5);
    MAX_STEP_HEIGHT = ceil(float(game->CELL_SIZE) / 3);

    frame = 0;
    animationSpeed = 0.3;
    shiftIsPressed = false;
    action = ACT_STAND;
    direction = DIR_RIGHT;

    spriteSheet = QPixmap(dir);
    setPixmap(spriteSheet.copy(0, 0, 50, 90));
    QVector <QPointF> areaCorners;
    //��������� ������� �������� ������
    areaCorners << QPointF(0, 0) << QPointF(boundingRect().width() * 3 / 2, 0) \
                   << QPointF(boundingRect().width() * 3 / 2, boundingRect().height()) \
                      << QPointF(0, boundingRect().height());

    actionArea = new QGraphicsPolygonItem(QPolygonF(areaCorners), this);
    actionArea->setVisible(false);
    horizontalSpeed = 0;
    verticalSpeed = 0;
}

//�������� ������
void Player::move()
{
    //��������
    frame += animationSpeed;
    if (action == ACT_STAND) setPixmap((spriteSheet.copy(0, 0, 50, 90)));
    if (action == ACT_JUMP) setPixmap((spriteSheet.copy(50, 0, 50, 90)));
    if (action == ACT_GO) setPixmap(spriteSheet.copy(50*(int(frame) % 8), 90, 50, 90));
    if (action == ACT_RUN) setPixmap(spriteSheet.copy(50*(int(frame) % 8), 180, 50, 90));

    //��������� �������� ��������
    while (collideWithSolid() == true)
    {
        if (collideWithSolid() == true) setPos(x(), y() - 1);
        if (collideWithSolid() == true) setPos(x() - pow(-1, (direction == DIR_RIGHT) + 1), y());
    }

    //������������ �� ���������
    unsigned int oldY = y();
    setPos(x(), y() - verticalSpeed);
    verticalSpeed -= game->GRAVITY;

    if (collideWithSolid() == true)
    {
        //����������� ������ �����
        if (verticalSpeed <= 0) {
            if (horizontalSpeed == 0) action = ACT_STAND;
            else if (shiftIsPressed == true) {
                action = ACT_RUN;
                horizontalSpeed = RUN_SPEED * pow(-1, (direction == DIR_RIGHT) + 1);
            } else
            {
                action = ACT_GO;
                horizontalSpeed = WALK_SPEED * pow(-1, (direction == DIR_RIGHT) + 1);
            }
        }
    }

    //����������� �� ������������� �����������
    if (collideWithSolid() == true)
    {
        while (collideWithSolid() == true)
        {
            setPos(x(), y() - pow(-1, (verticalSpeed <= 0) + 1));
        }

        //�� ��������� ��������� ����������� �� ������� �����������
        if (abs(y() - oldY) > MAX_STEP_HEIGHT)  setPos(x(), oldY);

        verticalSpeed = 0;
    }

    //������������ �� �����������
    setPos(x() + horizontalSpeed, y());

    //����������� �� ��������������� �����������
    while (collideWithSolid() == true)
    {
        setPos(x() - pow(-1, (direction == DIR_RIGHT) + 1), y());
    }

}

//������������ �������������� � ������
void Player::addClue(Cell * c)
{
    if (clues.contains(c->shortSymbol, Qt::CaseSensitive) == false)
    {
        clues.append(c->shortSymbol);
    }
}

//�������� �� �������� � ������� ����������
bool Player::collideWithSolid()
{
    QList <QGraphicsItem *> collisionList = collidingItems();
    for (int i = 0; i < collisionList.size(); i++) {
        if (typeid(*collisionList[i]) == typeid(Cell)) {
            if (((Cell*)(collisionList[i]))->isSolid == true) {
                return true;
            }
        }
    }
    return false;
}

//��������� ������� �������
void Player::keyPressEvent(QKeyEvent *event)
{
    //��������������
    if (event->key() == Qt::Key_Space)
    {
        QList <QGraphicsItem *> availableItems = actionArea->collidingItems();
        for (int i = 0; i < availableItems.size(); i++) {

            //������������ ������������� ������ � ���� ��������
            if ((typeid(*availableItems[i]) == typeid(Cell)) && (((Cell*)availableItems[i])->isInteractive == true)) {

                //��������������� ��� ��������������
                horizontalSpeed = 0;

                //����������� ������ � ����� "�����������"
                Cell * c = dynamic_cast<Cell *>(availableItems[i]);
                c->setCellActivated();

                //���������� ������
                emit investigating(c);

                //��������������� � ����� ������� �� ���
                break;
            }
        }
    }

    //�������� ������ ��� �����
    if ((event->key() == Qt::Key_Right) || (event->key() == Qt::Key_Left))
    {
        if (action == ACT_STAND)
        {
            //����� ��� ������� shift
            if (shiftIsPressed == true)
            {
                action = ACT_RUN;
            //��� ��� ������� shift
            } else {
                action = ACT_GO;
            }
        }

        //�������� ����������� ��������
        if ((event->key() == Qt::Key_Right) && (direction == DIR_LEFT))
        {
            frame = 0;
            setOffset(-boundingRect().width() / 4, 0);
            scale(-1, 1);
            direction = DIR_RIGHT;
        }

        if ((event->key() == Qt::Key_Left) && (direction == DIR_RIGHT))
        {
            frame = 0;
            setOffset(-boundingRect().width() / 4, 0);
            scale(-1, 1);
            direction = DIR_LEFT;
        }

        //�������� �������� ��������
        if (shiftIsPressed == true) horizontalSpeed = RUN_SPEED;
        else horizontalSpeed = WALK_SPEED;

        horizontalSpeed *= pow(-1, (direction == DIR_RIGHT) + 1);
    }

    //�������, ���� ��� ��������
    if ((event->key() == Qt::Key_Up) && (action != ACT_JUMP))
    {
        frame = 0;
        action = ACT_JUMP;
        verticalSpeed = JUMP_SPEED;
    }

    //��������� ��������
    if (event->key() == Qt::Key_Shift)
    {
        shiftIsPressed = true;

        //��������� �� ���
        if (action == ACT_GO)
        {
            action = ACT_RUN;
            horizontalSpeed = RUN_SPEED * pow(-1, (direction == DIR_RIGHT) + 1);
        }
    }
}

//��������� ���������� �������
void Player::keyReleaseEvent(QKeyEvent *event)
{
    //���������� ��������
    if (((event->key() == Qt::Key_Left) && (direction == DIR_LEFT)) || \
            ((event->key() == Qt::Key_Right) && (direction == DIR_RIGHT)))
    {
        horizontalSpeed = 0;

        //���������������, ���� ����� �� � ������
        if ((action == ACT_GO) || (action == ACT_RUN)) {
            action = ACT_STAND;
        }
    }

    //���������� ��������
    if (event->key() == Qt::Key_Shift)
    {
        shiftIsPressed = false;

        //��������� �� ���
        if (action == ACT_RUN)
        {
            action = ACT_GO;
            horizontalSpeed = WALK_SPEED * pow(-1, (direction == DIR_RIGHT) + 1);
        }
    }
}
