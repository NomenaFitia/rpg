#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <vector>
#include <QVector3D>
#include <QString>

class ObjectLoader {
public:
    std::vector<QVector3D> vertices;

    bool loadObj(const QString& path);
};

#endif
