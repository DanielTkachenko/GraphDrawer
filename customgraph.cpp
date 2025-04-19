#include "customgraph.h"

#include <QPainter>
#include <QPainterPath>

CustomGraph::CustomGraph(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    m_points << QPointF(0, 6)
    << QPointF(2, 4)
    << QPointF(3, 8)
    << QPointF(7, 4)
    << QPointF(10, 5);
}

void CustomGraph::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(Qt::blue, 2));

    if (m_points.size() < 2)
        return;

    QSizeF sz = size();
    QPainterPath path;

    auto scaleX = sz.width() / 10.0;
    auto scaleY = sz.height() / 10.0;

    QPointF start(m_points[0].x() * scaleX, sz.height() - m_points[0].y() * scaleY);
    path.moveTo(start);

    for (int i = 1; i < m_points.size(); ++i) {
        QPointF p(m_points[i].x() * scaleX, sz.height() - m_points[i].y() * scaleY);
        path.lineTo(p);
    }

    painter->drawPath(path);

    painter->setPen(QPen(Qt::black, 1));

    // Ось X
    painter->drawLine(0, sz.height(), sz.width(), sz.height());
    // Ось Y
    painter->drawLine(0, 0, 0, sz.height());

    // Подписи по X и Y
    QFont font = painter->font();
    font.setPointSize(10);
    painter->setFont(font);

    for (int i = 0; i <= 10; ++i) {
        int x = i * sz.width() / 10.0;
        int y = sz.height() - i * sz.height() / 10.0;

        // Подписи X
        painter->drawText(x - 5, sz.height() + 15, QString::number(i));

        // Подписи Y
        if (i != 0)
            painter->drawText(25, y + 5, QString::number(i));
    }

    // Названия осей
    painter->drawText(sz.width() / 2 - 20, sz.height() + 30, "X");
    painter->drawText(-10, 10, "Y");
}
