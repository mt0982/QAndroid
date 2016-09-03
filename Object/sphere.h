#ifndef SPHERE_H
#define SPHERE_H

#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <mesh.h>
#include <vector>
#include <QTime>
using namespace std;

class Sphere {
private:
    Mesh sphere;

public:
    Sphere();
    void init(QOpenGLShaderProgram &program);
    void render();
};

#endif // SPHERE_H
