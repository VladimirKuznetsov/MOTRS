#include "level.h"
#include "game.h"
#include "dialogBox.h"
#include <QGraphicsTextItem>
#include <QDebug>
#include <QTextCodec>

extern Game * game;

//конструктор
Level::Level(QGraphicsView *parent) : QGraphicsScene(parent)
{

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));

    //определяем геометрические параметры сцены
    check = true;
    PLAYER_HEIGHT = game->CELL_SIZE * 2.5;
    PLAYER_WIDTH = PLAYER_HEIGHT * 0.75;
    ENEMY_HEIGHT = game->CELL_SIZE * 3;
    ENEMY_WIDTH = ENEMY_HEIGHT * 1.5;

    numberOfEnemies = 0;
    connect(this, SIGNAL(win()), game, SLOT(nextLevel()));
    connect(this, SIGNAL(lose()), game, SLOT(resetLevel()));
}

//загрузка карты из массива строк
void Level::init(QString map[])
{
    //отрисовываем фон
    QStringList colors = map[2].split(' ');
    setBackgroundBrush(QBrush(QColor(colors[0].toInt(), colors[1].toInt(), colors[2].toInt())));

    //создаём таймер, который будет управлять движением
    updateTimer = new QTimer(this);

    //загрузка информации из массива строк
    short sceneLength = 0;
    for (int row = 4; row < 20; row++)
    {
        //определяем длину сцены по самой длинной строке
        if (map[row].length() > sceneLength)
        {
            sceneLength = map[row].length();
        }
        //парсинг строки
        for (int column = 0; column < map[row].length(); column++)
        {
            //отрисовка игрока
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
            //отрисовка игрока - крупнее
            if (map[row][column] == 'P')
            {
                player = new Player(":/img/dasha");
                player->setZoom(2);
                float scaleFactor = PLAYER_HEIGHT * 3 / player->boundingRect().height();
                player->setScale(scaleFactor);
                player->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - PLAYER_HEIGHT*3);
                player->setZValue(10);
                addItem(player);
                connect(updateTimer, SIGNAL(timeout()), player, SLOT(move()));
            }
            //отрисовка игрока - средний
            if (map[row][column] == 'I')
            {
                player = new Player(":/img/dasha");
                player->setZoom(2);
                float scaleFactor = PLAYER_HEIGHT * 2 / player->boundingRect().height();
                player->setScale(scaleFactor);
                player->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - PLAYER_HEIGHT*2);
                player->setZValue(10);
                addItem(player);
                connect(updateTimer, SIGNAL(timeout()), player, SLOT(move()));
            }
            //отрисовка автомобиля
            if (map[row][column] == 'v')
            {
                enemy[numberOfEnemies] = new Enemy(":/img/van/", this);
                float scaleFactor = ENEMY_HEIGHT / enemy[numberOfEnemies]->boundingRect().height();
                enemy[numberOfEnemies]->setScale(scaleFactor);
                enemy[numberOfEnemies]->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - ENEMY_HEIGHT);
                addItem(enemy[numberOfEnemies]);
                enemy[numberOfEnemies]->setParent(this);
                connect(updateTimer, SIGNAL(timeout()), enemy[numberOfEnemies], SLOT(move()));

                numberOfEnemies++;
            }
            //отрисовка выхода
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
            //отрисовка пола
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
            //отрисовка пола
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
            //отрисовка пола
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
            //отрисовка деревянного пола
            if (map[row][column] == 'W')
            {
                Cell * floor = new Cell(":/img/wood", 0, this);
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //отрисовка деревянных cтен
            if (map[row][column] == 'R')
            {
                Cell * wall = new Cell(":/img/wood", 1, this);
                float scaleFactor = game->CELL_SIZE / wall->boundingRect().width();
                wall->setScale(scaleFactor);
                wall->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                wall->isSolid = true;
                addItem(wall);
            }
            //отрисовка деревянного потолка
            if (map[row][column] == 'T')
            {
                Cell * ceiling = new Cell(":/img/wood", 2, this);
                float scaleFactor = game->CELL_SIZE / ceiling->boundingRect().width();
                ceiling->setScale(scaleFactor);
                ceiling->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                ceiling->isSolid = true;
                addItem(ceiling);
            }
            //отрисовка цельного дерева
            if (map[row][column] == 'S')
            {
                Cell * solid = new Cell(":/img/wood_s", 0, this);
                float scaleFactor = game->CELL_SIZE / solid->boundingRect().width();
                solid->setScale(scaleFactor);
                solid->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                solid->isSolid = true;
                addItem(solid);
            }
            //отрисовка бетонного пола
            if (map[row][column] == 'C')
            {
                Cell * floor = new Cell(":/img/concrete", 0, this);
                float scaleFactor = game->CELL_SIZE / floor->boundingRect().width();
                floor->setScale(scaleFactor);
                floor->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                floor->isSolid = true;
                floor->isFloor = true;
                addItem(floor);
            }
            //отрисовка бетонных cтен
            if (map[row][column] == 'r')
            {
                Cell * wall = new Cell(":/img/concrete", 1, this);
                float scaleFactor = game->CELL_SIZE / wall->boundingRect().width();
                wall->setScale(scaleFactor);
                wall->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                wall->isSolid = true;
                addItem(wall);
            }
            //отрисовка бетонного потолка
            if (map[row][column] == 'U')
            {
                Cell * ceiling = new Cell(":/img/concrete", 2, this);
                float scaleFactor = game->CELL_SIZE / ceiling->boundingRect().width();
                ceiling->setScale(scaleFactor);
                ceiling->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                ceiling->isSolid = true;
                addItem(ceiling);
            }
            //отрисовка цельного бетона
            if (map[row][column] == 'F')
            {
                Cell * solid = new Cell(":/img/concrete_s", 0, this);
                float scaleFactor = game->CELL_SIZE / solid->boundingRect().width();
                solid->setScale(scaleFactor);
                solid->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                solid->isSolid = true;
                addItem(solid);
            }
            //отрисовка невидимых стен
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
            //отрисовка гидрантов - препятствий
            if (map[row][column] == 'h')
            {
                Cell * hydrant = new Cell(":/img/hydrant", 0, this);
                float scaleFactor = game->CELL_SIZE / hydrant->boundingRect().width();
                hydrant->setScale(scaleFactor);
                hydrant->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                hydrant->isSolid = true;
                hydrant->addInteraction('h');
                hydrant->setCellActive();
                hydrant->interactionDialogue[0] = QString("Лучше я не буду тут ничего трогать...");
                addItem(hydrant);
            }
            //отрисовка фоновых гидрантов
            if (map[row][column] == 'H')
            {
                Cell * hydrant = new Cell(":/img/hydrant", 0, this);
                float scaleFactor = game->CELL_SIZE / hydrant->boundingRect().width();
                hydrant->setScale(scaleFactor);
                hydrant->setPos(column * game->CELL_SIZE, (row - 4) * game->CELL_SIZE);
                hydrant->addInteraction('h');
                hydrant->setCellActive();
                hydrant->interactionDialogue[0] = QString("Лучше я не буду тут ничего трогать...");
                addItem(hydrant);
            }
            //отрисовка автомобиля без тюленя
            if (map[row][column] == 'n')
            {
                Cell * van_ns = new Cell(":/img/van_ns", 0, this);
                float scaleFactor = game->CELL_SIZE * 4 / van_ns->boundingRect().height();
                van_ns->setScale(scaleFactor);
                van_ns->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * van_ns->boundingRect().height());
                van_ns->addInteraction('n');
                van_ns->setCellActive();
                van_ns->interactionDialogue[0] = QString("Эта машина принадлежит зоопарку.");
                addItem(van_ns);
                van_ns->setZValue(2);
            }
            //отрисовка фоновых кустов
            if (map[row][column] == 'b')
            {
                Cell * bush = new Cell(":/img/bush", 0, this);
                float scaleFactor = (float)game->CELL_SIZE * 3 / bush->boundingRect().height();
                bush->setScale(scaleFactor);
                bush->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * bush->boundingRect().height());
                addItem(bush);
            }
            //отрисовка фоновых кустов
            if (map[row][column] == 'B')
            {
                Cell * bush = new Cell(":/img/bush", 1, this);
                float scaleFactor = (float)game->CELL_SIZE * 3 / bush->boundingRect().height();
                bush->setScale(scaleFactor);
                bush->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * bush->boundingRect().height());
                addItem(bush);
            }
            //отрисовка мячика
            if (map[row][column] == 's')
            {
                Cell * ball = new Cell(":/img/ball", 0, this);
                float scaleFactor = game->CELL_SIZE * 4 / ball->boundingRect().height();
                ball->setScale(scaleFactor);
                ball->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * ball->boundingRect().height());
                ball->addInteraction('s');
                ball->setCellActive();
                ball->interactionDialogue[0] = QString("Это мячик для шоу с тюленями. Что он здесь делает?..");
                addItem(ball);
                ball->setZValue(-2);
            }
            //отрисовка клетки для тюленя
            if (map[row][column] == 'c')
            {
                Cell * cell = new Cell(":/img/cell", 0, this);
                float scaleFactor = (float)game->CELL_SIZE * 5 / cell->boundingRect().height();
                cell->setScale(scaleFactor);
                cell->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * cell->boundingRect().height());
                cell->addInteraction('c');
                cell->setCellActive();
                cell->interactionDialogue[0] = QString("Кажется, эта дверь - единственный способ выбраться из клетки.");
                cell->interactionDialogue[1] = QString("...что если нашему тюленю помогли сбежать?");
                addItem(cell);
            }
            //отрисовка г-на Огурцова
            if (map[row][column] == 'o')
            {
                Cell * mr = new Cell(":/img/ogurtsov", 0, this);
                float scaleFactor = (float)PLAYER_HEIGHT / mr->boundingRect().height();
                mr->setScale(scaleFactor);
                mr->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * mr->boundingRect().height());
                mr->addInteraction('o');
                mr->setCellActive();
                mr->interactionDialogue[0] = QString("– Добрый день, господин Огурцов. Старший следователь Дарья Винокурова.");
                mr->interactionDialogue[1] = QString("Вы вызвали полицию?");
                mr->interactionDialogue[2] = QString("– Да. Дело в том, что сегодня ночью из своей клетки пропал полосатый тюлень.");
                mr->interactionDialogue[3] = QString("Прошу вас, найдите его скорее!");
                mr->interactionDialogue[4] = QString("– Мы сделаем всё возможное. Скажите, у кого были ключи от клетки?");
                mr->interactionDialogue[5] = QString("– У нашего сторожа.");
                mr->interactionDialogue[6] = QString("– Могу я с ним побеседовать?");
                mr->interactionDialogue[7] = QString("– Боюсь, что нет. Сегодня он не вышел на работу.");
                mr->interactionDialogue[8] = QString("– Любопытно...");
                addItem(mr);
            }
            //отрисовка г-на Огурцова крупным планом
            if (map[row][column] == 'O')
            {
                Cell * mr = new Cell(":/img/ogurtsov", 0, this);
                float scaleFactor = (float)PLAYER_HEIGHT * 3 / mr->boundingRect().height();
                mr->setScale(scaleFactor);
                mr->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * mr->boundingRect().height());
                addItem(mr);
            }
            //отрисовка кухни
            if (map[row][column] == 'k')
            {
                Cell * kitchen = new Cell(":/img/kitchen", 0, this);
                float scaleFactor = game->CELL_SIZE * 9 / kitchen->boundingRect().height();
                kitchen->setScale(scaleFactor);
                kitchen->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * kitchen->boundingRect().height());
                kitchen->addInteraction('k');
                kitchen->setCellActive();
                kitchen->interactionDialogue[0] = QString("Превосходно...");
                kitchen->interactionDialogue[1] = QString("Теперь можно и поспать.");
                addItem(kitchen);;
            }
            //отрисовка ночной кухни
            if (map[row][column] == 'K')
            {
                Cell * kitchen = new Cell(":/img/kitchen_n", 0, this);
                float scaleFactor = game->CELL_SIZE * 9 / kitchen->boundingRect().height();
                kitchen->setScale(scaleFactor);
                kitchen->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * kitchen->boundingRect().height());
                addItem(kitchen);
            }
            //отрисовка кровати
            if (map[row][column] == 'i')
            {
                Cell * bed = new Cell(":/img/bed", 0, this);
                float scaleFactor = game->CELL_SIZE * 9 / bed->boundingRect().width();
                bed->setScale(scaleFactor);
                bed->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * bed->boundingRect().height());
                bed->addInteraction('i');
                bed->setCellActive();
                bed->interactionDialogue[0] = QString("");
                bed->isTarget = true;
                addItem(bed);
            }
            //отрисовка письма
            if (map[row][column] == 'a')
            {
                Cell * letter = new Cell(":/img/letter", 0, this);
                float scaleFactor = game->CELL_SIZE / letter->boundingRect().height();
                letter->setScale(scaleFactor);
                letter->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * letter->boundingRect().height());
                letter->addInteraction('a');
                letter->setCellActive();
                letter->interactionDialogue[0] = QString("Анонимное письмо?");
                letter->interactionDialogue[1] = QString("«Дарья, мне жаль, что я не могу встретиться с вами лично...»");
                letter->interactionDialogue[2] = QString("...терпеть не могу, когда меня называют Дарья...");
                letter->interactionDialogue[3] = QString("«...однако я вынужден держать свою личность в тайне.");
                letter->interactionDialogue[4] = QString("У меня есть информация по делу об исчезновении полосатого тюленя.");
                letter->interactionDialogue[5] = QString("Животное держат на старом складе сталелитейного завода,");
                letter->interactionDialogue[6] = QString("требуется срочное вмешательство сотрудников правопорядка.»");
                addItem(letter);
            }
            //отрисовка ящиков
            if (map[row][column] == 'q')
            {
                Cell * box = new Cell(":/img/box", 0, this);
                float scaleFactor = game->CELL_SIZE * 4 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'Q')
            {
                Cell * box = new Cell(":/img/box_l", 0, this);
                float scaleFactor = game->CELL_SIZE * 8 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'j')
            {
                Cell * box = new Cell(":/img/box", 0, this);
                float scaleFactor = game->CELL_SIZE * 4 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'J')
            {
                Cell * box = new Cell(":/img/box_l", 1, this);
                float scaleFactor = game->CELL_SIZE * 8 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'j')
            {
                Cell * box = new Cell(":/img/box", 1, this);
                float scaleFactor = game->CELL_SIZE * 4 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'Z')
            {
                Cell * box = new Cell(":/img/box_l", 2, this);
                float scaleFactor = game->CELL_SIZE * 8 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка ящиков
            if (map[row][column] == 'z')
            {
                Cell * box = new Cell(":/img/box", 2, this);
                float scaleFactor = game->CELL_SIZE * 4 / box->boundingRect().width();
                box->setScale(scaleFactor);
                box->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*box->boundingRect().height());
                addItem(box);
                box->setZValue(-1);
            }
            //отрисовка документов
            if (map[row][column] == 'd')
            {
                Cell * docs = new Cell(":/img/docs", 0, this);
                float scaleFactor = game->CELL_SIZE* 2 / docs->boundingRect().width();
                docs->setScale(scaleFactor);
                docs->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*docs->boundingRect().height());
                docs->addInteraction('d');
                docs->setCellActive();
                docs->interactionDialogue[0] = QString("Страховые документы...");
                docs->interactionDialogue[1] = QString("Похоже, что зоопарк получит крупную сумму в случае пропажи тюленя.");
                docs->interactionDialogue[2] = QString("И думаю, господин Огурцов прекрасно об этом осведомлён.");
                docs->interactionDialogue[3] = QString("Вопрос лишь в том, как эти документы попали сюда...");
                addItem(docs);
            }
            //отрисовка сигарет
            if (map[row][column] == 'L')
            {
                Cell * cig = new Cell(":/img/cigarettes", 0, this);
                float scaleFactor = game->CELL_SIZE * 3 / cig->boundingRect().width();
                cig->setScale(scaleFactor);
                cig->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*cig->boundingRect().height());
                cig->addInteraction('L');
                cig->setCellActive();
                cig->interactionDialogue[0] = QString("Окурки. Судя по всему, свежие.");
                addItem(cig);
            }
            //отрисовка миски
            if (map[row][column] == 'V')
            {
                Cell * food = new Cell(":/img/food", 0, this);
                float scaleFactor = game->CELL_SIZE* 2 / food->boundingRect().width();
                food->setScale(scaleFactor);
                food->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor*food->boundingRect().height());
                food->addInteraction('V');
                food->setCellActive();
                food->interactionDialogue[0] = QString("Миска с рыбой.");
                food->interactionDialogue[1] = QString("Кто-то держит здесь кота?");
                addItem(food);
            }
            //отрисовка титров
            if (map[row][column] == 'E')
            {
                Cell * end = new Cell(":/img/end", 0, this);
                float scaleFactor = game->CELL_SIZE * 20 / end->boundingRect().width();
                end->setScale(scaleFactor);
                end->setPos(column * game->CELL_SIZE, (row - 3) * game->CELL_SIZE - scaleFactor * end->boundingRect().height());
                end->addInteraction('V');
                end->setCellActive();
                end->interactionDialogue[0] = QString("");
                addItem(end);
            }
        }
    }

    //загружаем список улик
    clues = map[20];
    clues.remove(' ');

    //загружаем начальное и финальное сообщение уровня
    int i;
    for (i = 22; i < 52; i++)
    {
        if (map[i] == QString("---")) break;
        startMessage[i - 22] = map[i];
    }
    startMessage[i - 22] = "";

    i++;
    int j;
    for (j = i; j < i + 30; j++)
    {
        if (map[j] == QString("---")) break;
        endMessage[j - i] = map[j];
    }
    endMessage[j - i] = "";

    //определяем размеры сцены
    setSceneRect(0, 0, sceneLength * game->CELL_SIZE, game->WINDOW_HEIGHT);

    //позиционируем камеру в начальный момент времени
    game->setScene(this);
    game->centerOn(player);

    //создаём диалоговое поле
    dialog = new DialogBox();
    addItem(dialog);
    dialog->setParent(this);
    connect(player, SIGNAL(investigating(Cell*)), dialog, SLOT(setDialog(Cell*)));
    connect(dialog, SIGNAL(ended(Cell*)), player, SLOT(addClue(Cell*)));

    //запускаем таймер, управляющий движением
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(checkRules()));
    connect(updateTimer, SIGNAL(timeout()), dialog, SLOT(move()));
    updateTimer->start(20);

    //загрузка начального диалога
    dialog->setDialog(startMessage);
}

//отображаем в случае провала
void Level::gameOver(QString comment)
{
    updateTimer->stop();
    emit lose();
}

void Level::levelCompleted(QString message[])
{
    updateTimer->stop();
    connect (dialog, SIGNAL(ended()), this, SIGNAL(win()));
    dialog->setDialog(message);
}

//макет проверки правил
void Level::checkRules()
{
}

//отработка нажатий клавиш
void Level::keyPressEvent(QKeyEvent *event)
{
    //режим прокрутки диалога
    if (dialog->isOn == true)
    {
        switch (event->key())
        {
        //прокрутка диалога
        case (Qt::Key_Space):
            dialog->nextLine();
            break;

        //выход из диалога
        case (Qt::Key_Escape):
            dialog->skip();
            break;

        //в противном случае игнорируем нажатие
        default:
            break;
        }

    //обычный режим игры
    } else
    {
        switch (event->key())
        {
        //выход из игры
        case (Qt::Key_Escape):
            game->close();
            break;

        //передаём управление персонажу
        default:
            player->keyPressEvent(event);
            break;
        }
    }
}

//отработка отпускания клавиши
void Level::keyReleaseEvent(QKeyEvent *event)
{
    player->keyReleaseEvent(event);
}
