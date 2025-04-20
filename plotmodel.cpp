#include "plotmodel.h"
#include <QPointF>

PlotModel::PlotModel() {}

void PlotModel::updateData(const QVector<QPointF>& data)
{
    m_data = data;
}

const QVector<QPointF>& PlotModel::getData()
{
    return m_data;
}

const QVector<QPointF>& PlotModel::getDownsampledData(int step)
{
    m_downsampledData.clear();

    for(int i = 0; i < m_data.size(); i+=step)
    {

        QPointF minPoint, maxPoint;
        for(int j = i; j < std::min((int)m_data.size() , i+step); j++)
        {
            double minY = std::numeric_limits<double>().max();
            double maxY = std::numeric_limits<double>().lowest();
            if(m_data[j].y() < minY)
            {
                minY = m_data[j].y();
                minPoint = m_data[j];
            }

            if(m_data[j].y() > maxY)
            {
                maxY = m_data[j].y();
                maxPoint = m_data[j];
            }
        }
        m_downsampledData.append(minPoint);
        m_downsampledData.append(maxPoint);
    }

    return m_downsampledData;
}
