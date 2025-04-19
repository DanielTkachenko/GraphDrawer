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

    Q_INVOKABLE void readFile(const QUrl &fileUrl);

private:
    QVector<QPointF> m_points;
    QSizeF m_size;
    double m_scaleX;
    double m_scaleY;

    void paintGraph(QPainter *painter);
    void paintLine(QPainter *painter);
};

#endif // CUSTOMGRAPH_H
