#include "plotcontroller.h"
#include "filereader.h"
#include <iostream>
#include <QVector>
#include <QPointF>
#include <QString>

PlotController::PlotController(PlotView *view, QObject *parent)
    : QObject{parent}, m_view(view){ }

void PlotController::buildPlot(const QUrl &fileUrl)
{
    ReadResult result = FileReader::load(fileUrl);

    if(result.success)
    {
        m_model.updateData(result.data);
        if((m_model.getLength() / m_view->getSize().width()) > 2)
        {
            int step = m_model.getLength() / m_view->getSize().width();
            m_view->updatePlot(m_model.getDownsampledData(step));
        }
        else
        {
            m_view->updatePlot(m_model.getData());
        }
    }
}
