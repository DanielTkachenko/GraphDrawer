#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>

class FileReader
{
public:
    FileReader();

    static QVector<QPointF> load(const QUrl &fileUrl);
};

#endif // FILEREADER_H
