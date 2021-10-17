#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QDebug>

class MyLabel:public QLabel
{
public:
    MyLabel(QWidget *parent=nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void changeWheelValue(QPoint event,int value);
private:
    double m_scaleValue;      // 图片缩放倍数
    QPointF m_drawPoint;      // 绘图起点
    QPointF m_mousePoint;     // 鼠标当前位置点
    QRect m_rectPixmap;       // 被绘图片的矩形范围
    bool m_isMousePress;      // 鼠标是否按下

    const double EPS = 1e-6;  // 双精度浮点数比较
    const double SCALE_VALUE=0.02;
    const double SCALE_MAX_VALUE=2.0;
    const double SCALE_MIN_VALUE=0.5;
};


#endif // MYLABEL_H
