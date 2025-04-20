#include "filereader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <qpoint.h>
#include <qurl.h>

FileReader::FileReader(const QUrl &fileUrl, QObject* parent) : QObject(parent), m_path(fileUrl) {}


void FileReader::load() {
    QString localPath = m_path.toLocalFile();
    QFile file(localPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл:" << localPath;
        emit finished({{}, false, "Failed to open file"});
        return;
    }
    std::cout << "file opened" << std::endl;
    QTextStream in(&file);
    QVector<QPointF> points;
    int index = 3;
    QString header1 = in.readLine();
    QString header2 = in.readLine();
    QString header3 = in.readLine();
    if(header1[0] != '#' || header2[0] != '!' || header3[0] != '!'){
        qWarning() << "Не верный формат файла!";
        emit finished({{}, false, "Wrong file format"});
        return;
    }

    while (!in.atEnd()) {

        QString line = in.readLine();
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);
        if (parts.size() >= 2)
        {
            index++;
            bool okX, okY, okZ;
            double freq = parts[0].toDouble(&okX);
            double s11_real = parts[1].toDouble(&okY);
            double s11_img = parts[2].toDouble(&okZ);
            double s11 = 20*std::log10(std::sqrt((s11_real * s11_real) + (s11_img * s11_img)));
            if (okX && okY && okZ)
            {
                points.append(QPointF(freq, s11));
            }
            else {
                emit finished({{}, false, &"Error while reading data at line " [index]});
                return ;
            }
        }
        else {
            emit finished({{}, false, &"Error while reading data at line " [index]});
            return ;
        }
    }

    file.close();

    emit finished({points, true, ""});
}
