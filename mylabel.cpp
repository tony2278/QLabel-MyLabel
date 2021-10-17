#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent):QLabel(parent)
  ,m_scaleValue(1.0)
  ,m_drawPoint(0,0)
  ,m_mousePoint(0,0)
  ,m_rectPixmap(0,0,0,0)
  ,m_isMousePress(0)
{

}

void MyLabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pixmap(":/image/1.jpg");
    double width=this->width()*m_scaleValue;
    double height=this->height()*m_scaleValue;
    QPixmap scalePixmap=pixmap.scaled(width,height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // 饱满缩放
    m_rectPixmap=QRect(m_drawPoint.x(),m_drawPoint.y(),width,height);  // 图片区域
    painter.drawPixmap(m_rectPixmap,scalePixmap);
}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isMousePress)
    {
        int x=event->pos().x()-m_mousePoint.x();
        int y=event->pos().y()-m_mousePoint.y();
        m_mousePoint=event->pos();
        m_drawPoint=QPointF(m_drawPoint.x()+x,m_drawPoint.y()+y);
        update();
    }
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_isMousePress=true;
        m_mousePoint=event->pos();
    }
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        m_drawPoint=QPointF(0,0);
        m_scaleValue=1.0;
        update();
    }
    if(event->button() == Qt::LeftButton) m_isMousePress=false;
}

void MyLabel::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta()/ 8; // 滚动角度 - *8就是鼠标滚动的距离
    int numSteps = numDegrees / 15;     // 滚动步数 - *15就是鼠标滚动的角度
    changeWheelValue(event->pos(),numSteps);
    event->accept();
}

void MyLabel::resizeEvent(QResizeEvent *event)
{
    m_drawPoint=QPointF(0,0);
    m_scaleValue=1.0;
    update();
}

void MyLabel::changeWheelValue(QPoint event, int numSteps)
{
    m_scaleValue+=numSteps*SCALE_VALUE;
    if(m_scaleValue>(SCALE_MAX_VALUE+EPS))
    {
        m_scaleValue=SCALE_MAX_VALUE;
        return ;
    }
    if(m_scaleValue<(SCALE_MIN_VALUE-EPS))
    {
        m_scaleValue=SCALE_MIN_VALUE;
        return ;
    }

    if(m_rectPixmap.contains(event))
    {
        double x=m_drawPoint.x()-(event.x()-m_drawPoint.x())/m_rectPixmap.width()*(this->width()*SCALE_VALUE)*numSteps;
        double y=m_drawPoint.y()-(event.y()-m_drawPoint.y())/m_rectPixmap.height()*(this->height()*SCALE_VALUE)*numSteps;
        m_drawPoint=QPointF(x,y);
    }
    else
    {
        double x=m_drawPoint.x()-(this->width()*SCALE_VALUE)*numSteps/2;
        double y=m_drawPoint.y()-(this->height()*SCALE_VALUE)*numSteps/2;
        m_drawPoint=QPointF(x,y);
    }
    update();
}

