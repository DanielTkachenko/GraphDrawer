#ifndef CUSTOMGRAPH_H
#define CUSTOMGRAPH_H

#include <QQuickPaintedItem>
#include <QVector>
#include <QPointF>

class CustomGraph : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CustomGraph(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

private:
    QVector<QPointF> m_points;
};

#endif // CUSTOMGRAPH_H
