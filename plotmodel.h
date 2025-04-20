#ifndef PLOTMODEL_H
#define PLOTMODEL_H

#include <QVector>
#include <QPointF>

class PlotModel
{
public:
    PlotModel();

    void updateData(const QVector<QPointF>& data);

    inline int getLength() { return m_data.size(); }

    const QVector<QPointF>& getData();

    const QVector<QPointF>& getDownsampledData(int step);

private:

    QVector<QPointF> m_data;

    QVector<QPointF> m_downsampledData;
};

#endif // PLOTMODEL_H
