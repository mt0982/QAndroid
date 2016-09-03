#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include <QVector2D>
#include <QVector>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QMap>
#include <QDebug>
#include <fstream>
#include <sstream>
using namespace std;

class Mesh: protected QOpenGLFunctions
{
private:
    QMap<uint, QOpenGLBuffer> vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer ibo;
    QOpenGLShaderProgram program;
    //QVector<QOpenGLBuffer> vbo;

    int n_indices;

public:
    Mesh();
    void init();
    void setAttribute(int index, QVector<QVector2D> &data, QOpenGLShaderProgram &program);
    void setAttribute(int index, QVector<QVector3D> &data, QOpenGLShaderProgram &program);
    void setAttribute(QString name, QVector<QVector2D> &data, QOpenGLShaderProgram &program);
    void setAttribute(QString name, QVector<QVector3D> &data, QOpenGLShaderProgram &program);
    void setAttribute(int index, QVector<float> &data, QOpenGLShaderProgram &program);
    void setIndices(QVector<GLuint> &data);
    void render();

    GLenum primitive_mode = GL_TRIANGLES;
    void calculateNormals(QVector<QVector3D> &vert, QVector<QVector3D> &norm, QVector<uint> &inds);
    void calculateTangents(QVector<QVector3D> &vertices, QVector<uint> &indices, QVector<QVector2D> &UV,
                           QVector<QVector3D> &tangents);
    void parseOBJ(QVector<QVector3D> &vertices, QVector<uint> &indices);

    int n_instance;
};

#endif // MESH_H
















