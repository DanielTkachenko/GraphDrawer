#ifndef PLOTCONTROLLER_H
#define PLOTCONTROLLER_H

#include <QObject>
#include "plotmodel.h"
#include "plotview.h"

class PlotController : public QObject
{
    Q_OBJECT

public:
    explicit PlotController(PlotView *view, QObject *parent = nullptr);

    void setQmlItem(QObject* item);

    Q_INVOKABLE void buildPlot(const QUrl &fileUrl);

signals:

public slots:


private:
    PlotModel m_model;
    PlotView *m_view;
};

#endif // PLOTCONTROLLER_H
