#include "gamescene.h"
#include "zombieday.h"
#include "player.h"
#include "bullet.h"
#include "helper.h"
#include <QDebug>
#include <QKeyEvent>
#include <QDir>
#include <QPainter>
#include <list>
#include <iostream>
#include <QInputDialog>
#include <QMessageBox>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene{parent}, m_game(), m_deltaTime(0.0f), m_loopTime(0.0f), m_loopSpeed(20.0f),
    m_spacePressed(false), m_leftPressed(false), m_rightPressed(false), m_upPressed(false),m_downPressed(false),
      m_p(new Player())
{
    loadPixmap();
    setSceneRect(0, 0, Game::RESOLUTION.width(), Game::RESOLUTION.height());
    connect(&m_timer, &QTimer::timeout, this, &GameScene::loop);
    m_timer.start(Game::ITERATION_VALUE);
    m_elapsedTimer.start();

    m_sExplosion = Animation(m_explosionAPixmap, 0,0,48,46, 4, 0.5);
    m_sExplosionB = Animation(m_explosionCPixmap, 0,0,48,46, 4, 0.75);
    m_sRock = Animation(m_rockPixmap, 0,0,64,64, 16, 0.2);
    m_sRock_small = Animation(m_rockSmallPixmap, 0,0,64,64, 16, 0.2);
    m_sBullet = Animation(m_fireBluePixmap, 0,0,13,32, 1, 0);
    m_sPlayer = Animation(m_spaceShipPixmap, 0,0,99,75, 1, 0);

    m_sPlayer_helper = Animation(m_spaceShipHelperPixmap, 0,0,64,64, 16, 0.002);

    m_p->pickUpObject(new Weaponn());// => attribuer une arme au joueur

    m_sPlayer_go = Animation(m_spaceShipGoPixmap, 0,0,99,75, 1, 0);
    m_sExplosion_ship = Animation(m_explosionBPixmap, 0,0,96,92,4, 0.5);

    for(int i=0;i<3;i++)
    {
        Zombieday *a = new Zombieday();
        a->createRandomCharacter(*a);
        a->settings(m_sRock, rand()%Game::RESOLUTION.width(), rand()%Game::RESOLUTION.height(), rand()%360, 25);
        entities.push_back(a);
    }

    m_p->settings(m_sPlayer,Game::RESOLUTION.width()/2,Game::RESOLUTION.height()/2,0,20);
    m_p->m_dx = 0;
    m_p->m_dy = 0;
    entities.push_back(m_p);

    QGraphicsPixmapItem* bgItem = new QGraphicsPixmapItem(m_bgPixmap.scaled(Game::RESOLUTION.width(), Game::RESOLUTION.height()));
    addItem(bgItem);

}

void GameScene::loop()
{
    m_deltaTime = m_elapsedTimer.elapsed();
    m_elapsedTimer.restart();

    m_loopTime += m_deltaTime;
    if( m_loopTime > m_loopSpeed )
    {
        m_loopTime -= m_loopSpeed;

        // lancer de la balle avec espace
        if(m_spacePressed)
        {
            Bullet *b = new Bullet();
            b->settings(m_sBullet, m_p->m_x, m_p->m_y+30, m_p->m_angle-90,10);

            entities.push_back(b);
            m_spacePressed = false;
        }

        //
        if(m_rightPressed)
        {
            m_p->m_angle += 3;
        }
        if(m_leftPressed)
        {
            m_p->m_angle -= 3;
        }
        if(m_upPressed)
        {
            m_p->m_thrust = true;
        }
        else
        {
            m_p->m_thrust = false;
        }

        for(auto a:entities)
            for(auto b:entities)
            {
                // colision entre enemie et balles
                if (a->m_name=="enemie" && b->m_name=="bullet")
                    if ( Game::isCollide(a,b) )
                    {

                        m_p->attack +=1; // Attack du player
                        a->m_life = false;
                        b->m_life = false;

                        Entity *e = new Entity();
                        if(rand()%2)
                        {
                            e->settings(m_sExplosion,a->m_x,a->m_y);
                        }
                        else
                        {
                            e->settings(m_sExplosionB,a->m_x,a->m_y);
                        }


                        e->m_name="explosion";
                        entities.push_back(e);

                        // faire choisir un objet au joueur
                        Zombieday* enemie = dynamic_cast<Zombieday*>(a);
                        if(enemie->getInventory() != "") pauseGame(enemie->getInventory());
                        m_p->health +=100; // ajout de vie
                      for(int i=0;i<2;i++)
                        {
                            if (a->m_R==15) continue;
                            Zombieday *e = new Zombieday();
                            e->createRandomCharacter(*e);
                            e->settings(m_sRock_small,a->m_x,a->m_y,rand()%360,15);
                            entities.push_back(e);
                        }

                    }

                // colision entre joueur et allie
                if (a->m_name=="player" && b->m_name=="helper")
                    if ( Game::isCollide(a,b) )
                    {
                        m_p->health +=10;
                        std::cout <<" life : " << m_p->health << std::endl;
                        // faire choisir un objet au joueur
                        Helper* h = dynamic_cast<Helper*>(b);
                        if(h->getInventory() != "") pauseGame(h->getInventory());
                    }



                // calcule de defense
                for(auto c:entities)
                {
                    // colision entre enemy, joueur et balle
                    if (a->m_name=="player" && b->m_name=="enemie" && c->m_name=="bullet") {
                      //  std::cout <<" dist : " << a->distanceTo(*b) << std::endl;
                        if ( a->distanceTo(*b) < 200.0 ) {
                            m_p->defense +=1;
                        }
                    }
                }

                // colision entre joueur et enemies
                if (a->m_name=="player" && b->m_name=="enemie")
                    if ( Game::isCollide(a,b) )
                    {
                        //helper
                        cp++;
                        Player* pl = dynamic_cast<Player*>(a);
                        pl->health -=1;

                       // std::cout << "L'allié vous offre un objet.\n" << pl->health;

                        // envoyer un allié à 55 attack reçu
                        if(cp%55==0){
                            Helper *he = new Helper();
                            he ->createRandomCharacter(*he);

                            he->settings(m_sPlayer_helper, rand()%Game::RESOLUTION.width(), rand()%Game::RESOLUTION.height(),rand()%360,10);


                            entities.push_back(he );
                        }


                        // Creer une explosion
                        Entity *e = new Entity();
                        e->settings(m_sExplosion_ship,a->m_x,a->m_y);
                        e->m_name="explosion";
                        entities.push_back(e);

                        // 150 atrack reçu on  est mort
                        if(cp%150==0){
                            std:: cout << " tueeeer " << std::endl;
                            b->m_life=false;


                            m_p->settings(m_sPlayer,Game::RESOLUTION.width()/2,Game::RESOLUTION.height()/2,0,20);
                            m_p->m_dx=0;
                            m_p->m_dy=0;
                        }

                    }
            }





        if (m_p->m_thrust)
        {
            m_p->m_anim = m_sPlayer_go;
        }
        else
        {
            m_p->m_anim = m_sPlayer;
        }


        for(auto e:entities)
        {
            if (e->m_name=="explosion")
            {
                if (e->m_anim.isEnd())
                {
                    e->m_life=0;
                }
            }

        }

        if (rand()%150==0)
        {
            Zombieday *a = new Zombieday();
            a->settings(m_sRock, 0,rand()%Game::RESOLUTION.height(), rand()%360, 25);
            entities.push_back(a);
        }

        for(auto i=entities.begin();i!=entities.end();)
        {
            Entity *e = *i;

            e->update();
            e->m_anim.update();

            if (e->m_life == false)
            {
                i=entities.erase(i);
                delete e;
            }
            else i++;
        }


        clear();
        QGraphicsPixmapItem* bgItem = new QGraphicsPixmapItem(m_bgPixmap.scaled(Game::RESOLUTION.width(), Game::RESOLUTION.height()));
        addItem(bgItem);

        // panneau
        drawString(0,2, "Dégats: " + QString::number(cp, 'f', 2) + "");
        drawString(0,1, "Vie: " + QString::number(m_p->health, 'f', 2) + "");
        drawString(0,0, "Acttack: " + QString::number(m_p->attack, 'f', 2) + "");
        drawString(0,3, "Défense: " + QString::number(m_p->defense, 'f', 2) + "");
        drawString(0,4, "Inventaire:\n " + QString::fromStdString(m_p->toString())+" ");

        for(auto i:entities)
        {
            if(i->m_life) {

                QPixmap pixmap;
                QPoint pos;
                qreal angle;
                QSize size;
                qreal R = 0.0;
                i->draw(pixmap, pos, angle, size, R);
                QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem();
                pItem->setPixmap(pixmap.scaled(size.width(), size.height()));
                pItem->setPos(pos);
                pItem->setRotation(angle + 90);

                if(i->m_name == "player")
                {
                   pItem->setZValue(10);
                }

                pItem->setTransformOriginPoint(size.width()/2, size.height()/2);
                addItem(pItem);
            }

        }

    }
}


void GameScene::pauseGame(std::string donnees)
{
    // Mettre le jeu en pause
    // Vous pouvez ajouter du code ici pour arrêter le mouvement des entités, etc.

    std::cout << donnees;
    // Afficher un panneau pour demander à l'utilisateur d'entrer un chiffre
    bool ok;
    int userNumber = QInputDialog::getInt(nullptr, "Game Over", "Le joueur est mort.\nVeuillez entrer un chiffre :"+QString::fromStdString(donnees), 1, 0, 999, 1, &ok);

    if (ok) {
        if(userNumber <= 2 && userNumber>=0){
            switch (static_cast<ObjectType>(userNumber)) {
            case ObjectType::Potion:
                m_p->pickUpObject(new Potion());
                break;
            case ObjectType::Weaponn:
               m_p->pickUpObject(new Weaponn());
                break;
            case ObjectType::Armor:
                m_p->pickUpObject(new Armor());
                break;
            }

        }
    } else {
        // L'utilisateur a annulé l'entrée, vous pouvez gérer cela en conséquence
        // ...
    }

    // Reprendre le jeu après que l'utilisateur a entré un chiffre
    // Vous pouvez ajouter du code ici pour reprendre le mouvement des entités, etc.
}

void GameScene::loadPixmap()
{
    if(m_bgPixmap.load(Game::PATH_TO_BG_PIXMAP))
    {
        qDebug() << "BgPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "BgPixmap is not loaded successfully";
    }

    if(m_fireBluePixmap.load(Game::PATH_TO_FIRE_BLUE_PIXMAP))
    {
        qDebug() << "FireBluePixmap is loaded successfully";
    }
    else
    {
        qDebug() << "FireBluePixmap is not loaded successfully";
    }

    if(m_fireRedPixmap.load(Game::PATH_TO_FIRE_RED_PIXMAP))
    {
        qDebug() << "FireRedPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "FireRedPixmap is not loaded successfully";
    }

    if(m_rockPixmap.load(Game::PATH_TO_ROCK_PIXMAP))
    {
        qDebug() << "RockPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "RockPixmap is not loaded successfully";
    }

    if(m_rockSmallPixmap.load(Game::PATH_TO_ROCK_SMALL_PIXMAP))
    {
        qDebug() << "RockSmallPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "RockSmallPixmap is not loaded successfully";
    }

    if(m_spaceShipPixmap.load(Game::PATH_TO_SPACESHIP_PIXMAP))
    {
        qDebug() << "SpaceShipPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "SpaceShipPixmap is not loaded successfully";
    }


    if(m_spaceShipHelperPixmap.load(Game::PATH_TO_SPACESHIP_HELPER_PIXMAP))
    {
        qDebug() << "SpaceShipPixmapHelper is loaded successfully";
    }
    else
    {
        qDebug() << "SpaceShipPixmap is not loaded successfully";
    }

    if(m_spaceShipGoPixmap.load(Game::PATH_TO_SPACESHIP_GO_PIXMAP))
    {
        qDebug() << "SpaceShipGoPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "SpaceShipGoPixmap is not loaded successfully";
    }

    if(m_explosionAPixmap.load(Game::PATH_TO_EXPLOSION_A_PIXMAP))
    {
        qDebug() << "ExplosionAPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "ExplosionAPixmap is not loaded successfully";
    }

    if(m_explosionBPixmap.load(Game::PATH_TO_EXPLOSION_B_PIXMAP))
    {
        qDebug() << "ExplosionBPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "ExplosionBPixmap is not loaded successfully";
    }

    if(m_explosionCPixmap.load(Game::PATH_TO_EXPLOSION_C_PIXMAP))
    {
        qDebug() << "ExplosionCPixmap is loaded successfully";
    }
    else
    {
        qDebug() << "ExplosionCPixmap is not loaded successfully";
    }
}

void GameScene::renderScene()
{
    QString fileName = QDir::currentPath() + QDir::separator() + "game_scene.png";
    QRect rect = sceneRect().toAlignedRect();
    QImage image(rect.size(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);
    QPainter painter(&image);
    render(&painter);
    image.save(fileName);
    qDebug() << "saved " << fileName;
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {

        break;
    case Qt::Key_Up:
    {
        m_upPressed = true;
    }
        break;
    case Qt::Key_Right:
    {
        m_rightPressed = true;
    }
        break;
    case Qt::Key_Left:
    {
        m_leftPressed = true;
    }
        break;

    case Qt::Key_Down:
    {
        m_downPressed = true;
    }
    break;
    }

    if( !event->isAutoRepeat() )
    {
        if( event->key() == Qt::Key_Space )
        {
            m_spacePressed = true;
        }
    }
    QGraphicsScene::keyPressEvent(event);
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
    {
        m_spacePressed = false;
    }
        break;
    case Qt::Key_Up:
    {
        m_upPressed = false;
    }
        break;
    case Qt::Key_Right:
    {
        m_rightPressed = false;
    }
    break;
    case Qt::Key_Down:
    {
        m_downPressed = false;
    }
        break;
    case Qt::Key_Left:
    {
        m_leftPressed = false;
    }
        break;
    case Qt::Key_Z:
        //renderScene();
        break;
    }
    QGraphicsScene::keyReleaseEvent(event);
}


void GameScene::drawString(int x, int y, QString text)
{
  //  std::cout << text.toStdString() << std::endl;
    QGraphicsSimpleTextItem* tItem = new QGraphicsSimpleTextItem();
    QFont tFont = tItem->font();

    tFont.setPointSize(SCREEN::CELL_SIZE.height()*3);
    tItem->setFont(tFont);
    tItem->setPos(x*SCREEN::CELL_SIZE.width(), 3*y*SCREEN::CELL_SIZE.height());
    tItem->setBrush(QColor(Qt::red));

    tItem->setPen(QColor(Qt::white));
    tItem->setText(text);
    addItem(tItem);
}
