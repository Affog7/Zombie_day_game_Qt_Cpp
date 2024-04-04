#include "entity.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

Entity::Entity()
{
    m_life = true;
}

void Entity::settings(Animation &a, int x, int y, float angle, int radius)
{
    m_anim = a;
    m_x=x;
    m_y=y;
    m_angle = angle;
    m_R = radius;
}

void Entity::update()
{

}

void Entity::draw(QGraphicsScene *scene)
{

    //    m_anim.m_sprite.setPos(m_x, m_y);
    //    m_anim.m_sprite.setRotation(m_angle + 90);
    //    if(m_anim.m_sprite.scene() == nullptr)
    //    {
    //        scene->addItem(&m_anim.m_sprite);
    //    }
    QPixmap p = m_anim.m_texture.copy(
                m_anim.frames()[(int)m_anim.framesIndex()].x(),
            m_anim.frames()[(int)m_anim.framesIndex()].y(),
            m_anim.frames()[(int)m_anim.framesIndex()].width(),
            m_anim.frames()[(int)m_anim.framesIndex()].height());
    m_pixmapItem.setPixmap(p);

    qDebug() << m_name << " " << m_anim.frames()[(int)m_anim.framesIndex()];
    m_pixmapItem.setPos(m_x, m_y );
    qDebug() << m_pixmapItem.pos();
    m_pixmapItem.setRotation(m_angle + 90);
    scene->addItem(&m_pixmapItem);
    m_pixmapItem.setTransformOriginPoint(m_anim.frames()[(int)m_anim.framesIndex()].width()/2,
            m_anim.frames()[(int)m_anim.framesIndex()].height()/2);

    QGraphicsEllipseItem circle(0, 0, m_R, m_R);
    circle.setBrush(QColor(255,0,0,170));
    circle.setPen(QColor(255,0,0,170));
    circle.setPos(m_x, m_y);
    circle.setTransformOriginPoint(m_R, m_R);
    if(circle.scene() == nullptr)
    {
        scene->addItem(&circle);
    }
}

double Entity::distanceTo( Entity &other)
{
 return std::sqrt(std::pow(m_x - other.m_x, 2) + std::pow(m_y - other.m_y, 2) );
}

void Entity::draw(QPixmap &pixmap, QPoint &pos, qreal &angle, QSize &size, qreal &R)
{
    pixmap = m_anim.m_texture.copy(
                m_anim.frames()[(int)m_anim.framesIndex()].x(),
            m_anim.frames()[(int)m_anim.framesIndex()].y(),
            m_anim.frames()[(int)m_anim.framesIndex()].width(),
            m_anim.frames()[(int)m_anim.framesIndex()].height());
    pos.setX(m_x);
    pos.setY(m_y);
    angle = m_angle;
    size = QSize(            m_anim.frames()[(int)m_anim.framesIndex()].width(),
            m_anim.frames()[(int)m_anim.framesIndex()].height());
    R = m_R;
}

Entity::~Entity()
{

}
