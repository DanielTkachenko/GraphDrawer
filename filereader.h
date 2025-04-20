#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <qurl.h>

struct ReadResult {
    QVector<QPointF> data;
    bool success;
    QString errorMessage;
};

class FileReader : public QObject
{
    Q_OBJECT
public:
    explicit FileReader(const QUrl &fileUrl, QObject* parent = nullptr);

public slots:
    void load();
signals:
    void finished(ReadResult result);

private:
    QUrl m_path;
};

#endif // FILEREADER_H
