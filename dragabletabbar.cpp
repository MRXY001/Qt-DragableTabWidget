#include "dragabletabbar.h"

DragableTabBar::DragableTabBar(QWidget *parent) : QTabBar(parent), dragging(false)
{
    setMovable(true);
    setMouseTracking(true);
}

void DragableTabBar::mousePressEvent(QMouseEvent *e)
{
    QTabBar::mousePressEvent(e);

    if (e->button() == Qt::LeftButton)
    {
        dragging = true;
        press_pos = e->pos();
    }
}

void DragableTabBar::mouseMoveEvent(QMouseEvent *e)
{
    QTabBar::mouseMoveEvent(e);

    // 高度超过
    if (dragging && (e->buttons() & Qt::LeftButton) && qAbs(e->pos().y()-press_pos.y()) > this->height())
    {
        int index = this->currentIndex();
        if (index == -1)
            return ;

        // 拖拽到外面来了
        if (!tabRect(index).contains(e->pos()))
        {
            emit signalStartDrag(index);
        }
    }
}

void DragableTabBar::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "mouse release";
    if (dragging && e->button() == Qt::LeftButton && !contentsRect().contains(e->pos()))
    {
        dragging = false;
        // emit signalEndDrag();
    }
    return QTabBar::mouseReleaseEvent(e);
}

void DragableTabBar::focusOutEvent(QFocusEvent *e)
{
    if (dragging)
    {
        dragging = false;
    }

    return QTabBar::focusOutEvent(e);
}
