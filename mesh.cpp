#include "mesh.h"

Mesh::Mesh(): ibo(QOpenGLBuffer::IndexBuffer)
{
    n_instance = 0;
}

void Mesh::init()
{
    initializeOpenGLFunctions();

    vao.create();   //Vertex Array Object
    ibo.create();   //Index Buffer

    ibo.setUsagePattern(QOpenGLBuffer::StaticDraw);
}

void Mesh::setAttribute(int index, QVector<float> &data, QOpenGLShaderProgram &program)
{
    /* Attributes Container */
    if(!vbo.contains(index)) {
        QOpenGLBuffer t;
        t.create();
        t.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vbo.insert(index, t);
    }

    vao.bind();
    vbo[index].bind();
    vbo[index].allocate(&data[0], data.size() * sizeof(float));
    program.enableAttributeArray(index);
    program.setAttributeBuffer(index, GL_FLOAT, 0, 1);
    vbo[index].release();
    vao.release();
}

void Mesh::setAttribute(int index, QVector<QVector2D> &data, QOpenGLShaderProgram &program)
{
    /* Attributes Container */
    if(!vbo.contains(index)) {
        QOpenGLBuffer t;
        t.create();
        t.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vbo.insert(index, t);
    }

    vao.bind();
    vbo[index].bind();
    vbo[index].allocate(&data[0], data.size() * sizeof(QVector2D));
    program.enableAttributeArray(index);
    program.setAttributeBuffer(index, GL_FLOAT, 0, 2);
    vbo[index].release();
    vao.release();
}

void Mesh::setAttribute(int index, QVector<QVector3D> &data, QOpenGLShaderProgram &program)
{
    /* Attributes Container */
    if(!vbo.contains(index)) {
        QOpenGLBuffer t;
        t.create();
        t.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vbo.insert(index, t);
    }

    vao.bind();
    vbo[index].bind();
    vbo[index].allocate(&data[0], data.size() * sizeof(QVector3D));
    program.enableAttributeArray(index);
    program.setAttributeBuffer(index, GL_FLOAT, 0, 3);
    //if(index == 2) glVertexAttribDivisor(index, 1);
    vbo[index].release();
    vao.release();
}

void Mesh::setAttribute(QString name, QVector<QVector2D> &data, QOpenGLShaderProgram &program)
{
    /* Get attribute location OpenGL ES */
    int location = program.attributeLocation(name);

    /* Attributes Container */
    if(!vbo.contains(location)) {
        QOpenGLBuffer t;
        t.create();
        t.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vbo.insert(location, t);
    }

    vao.bind();
    vbo[location].bind();
    vbo[location].allocate(&data[0], data.size() * sizeof(QVector3D));
    program.enableAttributeArray(location);
    program.setAttributeBuffer(location, GL_FLOAT, 0, 2);
    vbo[location].release();
    vao.release();
}

void Mesh::setAttribute(QString name, QVector<QVector3D> &data, QOpenGLShaderProgram &program)
{
    /* Get attribute location OpenGL ES */
    int location = program.attributeLocation(name);

    /* Attributes Container */
    if(!vbo.contains(location)) {
        QOpenGLBuffer t;
        t.create();
        t.setUsagePattern(QOpenGLBuffer::StaticDraw);
        vbo.insert(location, t);
    }

    vao.bind();
    vbo[location].bind();
    vbo[location].allocate(&data[0], data.size() * sizeof(QVector3D));
    program.enableAttributeArray(location);
    program.setAttributeBuffer(location, GL_FLOAT, 0, 3);
    vbo[location].release();
    vao.release();
}

void Mesh::setIndices(QVector<GLuint> &data)
{
    n_indices = data.size();
    ibo.bind();
    ibo.allocate(&data[0], data.size() * sizeof(GLuint));
}

void Mesh::render()
{
    vao.bind();
    ibo.bind();
    glDrawElements(primitive_mode, n_indices, GL_UNSIGNED_INT, 0);
    vao.release();
}

void Mesh::calculateNormals(QVector<QVector3D> &vert, QVector<QVector3D> &norm, QVector<uint> &inds)
{
    for(int i = 0; i < inds.size()/3; ++i) {
        int i0 = inds[i*3];
        int i1 = inds[i*3+1];
        int i2 = inds[i*3+2];

        QVector3D v10, v21;
        v10 = vert[i1] - vert[i0];
        v21 = vert[i2] - vert[i1];

        QVector3D n = QVector3D::crossProduct(v10, v21);
        n.normalize();

        norm[i0] = n;
        norm[i1] = n;
        norm[i2] = n;
    }

    for(int i = 0; i < vert.size(); i++) {
        norm[i].normalize();
    }
}

void Mesh::parseOBJ(QVector<QVector3D> &vertices, QVector<uint> &indices)
{
    ifstream in("/home/asus/Programy/Qt/Projekty/LowPolyGame/OBJ/tree01.obj", ios::in);
    if (!in) {
        qDebug() << "Cannot open OBJ file";
    }

    string line;
    while(getline(in, line)) {

        /* Vertices */
        if (line.substr(0,2) == "v ") {
            istringstream s(line.substr(2));
            QVector3D v; s >> v[0]; s >> v[1]; s >> v[2];
            vertices.push_back(v);
        }

        /* Indices */
        else if (line.substr(0,2) == "f ") {
            istringstream s(line.substr(2));
            GLushort a,b,c;
            s >> a; s >> b; s >> c;
            a--; b--; c--;

            indices.push_back(a);
            indices.push_back(b);
            indices.push_back(c);
        }
    }
}

void Mesh::calculateTangents(QVector<QVector3D> &vertices, QVector<uint> &indices, QVector<QVector2D> &UV,
                             QVector<QVector3D> &tangents)
{
    /* Calculate tangents */
    QVector3D tan[vertices.size()];

    for(int i = 0; i < indices.size(); i += 3) {
        QVector3D v0 = vertices[indices[i]];
        QVector3D v1 = vertices[indices[i+1]];
        QVector3D v2 = vertices[indices[i+2]];

        // Shortcuts for UV
        QVector2D uv0 = UV[indices[i]];
        QVector2D uv1 = UV[indices[i+1]];
        QVector2D uv2 = UV[indices[i+2]];

        // Edges of the triangle : postion delta
        QVector3D deltaPos1 = v1-v0;
        QVector3D deltaPos2 = v2-v0;

        // UV delta
        QVector2D deltaUV1 = uv1-uv0;
        QVector2D deltaUV2 = uv2-uv0;

        float r = 1.0f / (deltaUV1.x() * deltaUV2.y() - deltaUV1.y() * deltaUV2.x());
        QVector3D tangent = (deltaPos1 * deltaUV2.y()   - deltaPos2 * deltaUV1.y())*r;

        tan[indices[i]] += tangent;
        tan[indices[i+1]] += tangent;
        tan[indices[i+2]] += tangent;
    }

    for(int i = 0; i < vertices.size(); i++) {
        tan[i].normalize();
        //qDebug() << tan[i];
        tangents.push_back(tan[i]);
    }
}















