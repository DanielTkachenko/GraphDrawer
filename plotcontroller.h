#ifndef PLOTCONTROLLER_H
#define PLOTCONTROLLER_H

#include <QObject>
#include "filereader.h"
#include "plotmodel.h"
#include "plotview.h"

class PlotController : public QObject
{
    Q_OBJECT

public:
    explicit PlotController(PlotView *view, QObject *errorMessageDialog, QObject *parent = nullptr);

    void setQmlItem(QObject* item);

    Q_INVOKABLE void buildPlot(const QUrl &fileUrl);

signals:

public slots:


private:
    PlotModel m_model;
    PlotView *m_view;
    QObject *m_errorMessageDialog;
};

#endif // PLOTCONTROLLER_H
