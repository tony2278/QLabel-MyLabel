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
    double m_scaleValue;      // ͼƬ���ű���
    QPointF m_drawPoint;      // ��ͼ���
    QPointF m_mousePoint;     // ��굱ǰλ�õ�
    QRect m_rectPixmap;       // ����ͼƬ�ľ��η�Χ
    bool m_isMousePress;      // ����Ƿ���

    const double EPS = 1e-6;  // ˫���ȸ������Ƚ�
    const double SCALE_VALUE=0.02;
    const double SCALE_MAX_VALUE=2.0;
    const double SCALE_MIN_VALUE=0.5;
};


#endif // MYLABEL_H
