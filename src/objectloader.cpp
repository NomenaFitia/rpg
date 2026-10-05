#include "objectloader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

bool ObjectLoader::loadObj(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Impossible d'ouvrir le fichier .obj : " << path;
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("v ")) {
            QStringList parts = line.split(" ", Qt::SkipEmptyParts);
            if (parts.size() >= 4) {
                float x = parts[1].toFloat();
                float y = parts[2].toFloat();
                float z = parts[3].toFloat();
                vertices.push_back(QVector3D(x, y, z));
            }
        }
    }
    return true;
}
