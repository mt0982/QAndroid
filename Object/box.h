#ifndef BOX_H
#define BOX_H

#include <QVector3D>
#include <QVector2D>
#include <QOpenGLShaderProgram>
#include <mesh.h>

class Box {
private:
    Mesh box;
    QVector<QVector3D> vertices;

public:
    Box();
    void init(QOpenGLShaderProgram &program);
    void render();
};

#endif // BOX_H
