#include "plotcontroller.h"
#include "filereader.h"
#include <iostream>
#include <QVector>
#include <QPointF>
#include <QString>
#include <QThread>
//#include <QMessageBox>

PlotController::PlotController(PlotView *view, QObject *errorMessageDialog, QObject *parent)
    : QObject{parent}, m_view(view), m_errorMessageDialog(errorMessageDialog){ }

void PlotController::buildPlot(const QUrl &fileUrl)
{
    QThread* thread = new QThread();
    FileReader *fileReader = new FileReader(fileUrl);
    fileReader->moveToThread(thread);

    //connect( worker, &Worker::error, this, &MyClass::errorString);
    connect( thread, &QThread::started, fileReader, &FileReader::load);

    connect(fileReader, &FileReader::finished, this, [=](ReadResult result) {
        thread->quit();
        thread->wait();
        fileReader->deleteLater();
        thread->deleteLater();

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
        else {
            m_errorMessageDialog->setProperty("visible", "true");
            m_errorMessageDialog->findChild<QObject*>("errorText")->setProperty("text", result.errorMessage);
        }
    });

    thread->start();
}
