#include "animation.h"

Animation::Animation()
{

}

Animation::Animation(QPixmap &t, int x, int y, int w, int h, int count, float speed)
    : m_frame(0.f), m_speed(speed)
{
    for (int i=0;i<count;i++)
    {
        m_frames.push_back( QRect(x+i*w, y, w, h)  );
        qDebug() << "rect " << QRect(x+i*w, y, w, h) << " count " << count;
    }
    m_texture = t;
}

void Animation::update()
{
    m_frame += m_speed;
    int n = m_frames.size();
    if ( m_frame >= n)
    {
        m_frame -= n;
    }
}

bool Animation::isEnd()
{
    return m_frame + m_speed >= m_frames.size();
}
