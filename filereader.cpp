#include "filereader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include <qpoint.h>
#include <qurl.h>

FileReader::FileReader(QObject *parent): QObject{parent} {}


void FileReader::load(const QUrl &fileUrl) {
    QString localPath = fileUrl.toLocalFile();
    QFile file(localPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл:" << localPath;
        return;
    }
    std::cout << "file opened" << std::endl;
    QTextStream in(&file);
    QVector<QPointF> points;

    QString header1 = in.readLine();
    QString header2 = in.readLine();
    QString header3 = in.readLine();
    if(header1[0] != '#' || header2[0] != '!' || header3[0] != '!'){
        qWarning() << "Не верный формат файла!";
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);
        if (parts.size() >= 2)
        {
            bool okX, okY, okZ;
            double freq = parts[0].toDouble(&okX);
            double s11_real = parts[1].toDouble(&okY);
            double s11_img = parts[2].toDouble(&okZ);
            double s11 = 20*std::log10(std::sqrt((s11_real * s11_real) + (s11_img)));
            if (okX && okY && okZ)
            {
                points.append(QPointF(freq, s11));
            }
        }
    }

    file.close();
    emit dataLoaded(points);
}
