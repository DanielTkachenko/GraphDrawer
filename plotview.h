#ifndef PLOTVIEW_H
#define PLOTVIEW_H

#include <QQuickPaintedItem>
#include <QVector>
#include <QPointF>

struct PlotBounds
{
    double minX;
    double maxX;
    double minY;
    double maxY;
};

class PlotView : public QQuickPaintedItem
{
    Q_OBJECT

public:
    PlotView(QQuickItem *parent = nullptr);

    inline QSizeF getSize() { return m_size; }

    void paint(QPainter *painter) override;

    Q_INVOKABLE void updatePlot(const QVector<QPointF> &points);

private:
    QVector<QPointF> m_points;
    QSizeF m_size;
    PlotBounds m_bounds;

    void paintGraph(QPainter *painter);
    void paintLine(QPainter *painter);
    QPointF toScreenSize(const QPointF& point);
};

#endif // PLOTVIEW_H
