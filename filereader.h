#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>

struct ReadResult {
    QVector<QPointF> data;
    bool success;
    QString errorMessage;
};

class FileReader
{
public:
    FileReader();

    static ReadResult load(const QUrl &fileUrl);
};

#endif // FILEREADER_H
