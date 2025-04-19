#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>

class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = nullptr);

    Q_INVOKABLE void load(const QUrl &fileUrl);

signals:

    void dataLoaded(QVector<QPointF> &points);
};

#endif // FILEREADER_H
