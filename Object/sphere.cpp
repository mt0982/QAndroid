#include "sphere.h"

Sphere::Sphere()
{
    qsrand(QTime::currentTime().msec());
}

void Sphere::init(QOpenGLShaderProgram &program)
{
    vector<GLfloat> vertices, normals, texcoords;

    float radius = 1;
    int rings = 36;
    int sectors = 36;

    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);
    int r, s;

    vertices.resize(rings * sectors * 3);
    normals.resize(rings * sectors * 3);
    texcoords.resize(rings * sectors * 2);
    vector<GLfloat>::iterator v = vertices.begin();
    vector<GLfloat>::iterator n = normals.begin();
    vector<GLfloat>::iterator t = texcoords.begin();

    for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
        float const y = sin( -M_PI_2 + M_PI * r * R );
        float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
        float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

        *t++ = s*S;
        *t++ = r*R;

        *v++ = x * radius;
        *v++ = y * radius;
        *v++ = z * radius;

        *n++ = x;
        *n++ = y;
        *n++ = z;
    }

    /* Send To QVectors */
    QVector<QVector3D> verticesQ, colorsQ;
    for(unsigned int i = 0; i < vertices.size(); i += 3) {
        verticesQ.push_back(QVector3D(vertices[i], vertices[i+1], vertices[i+2]));
        colorsQ.push_back(QVector3D(0.3, 0.3, 0.3));
    }

    /* Indices */
    QVector<uint> indicesQ;
    for(int z = 0; z < rings - 1; z++) {
        for(int x = 0; x < sectors - 1; x++) {

            int dataW = sectors;
            int shz = z*dataW;

            indicesQ.push_back(x + shz);
            indicesQ.push_back(x + shz + dataW);
            indicesQ.push_back(x + shz + 1);

            indicesQ.push_back(x + shz + dataW);
            indicesQ.push_back(x + shz + 1 + dataW);
            indicesQ.push_back(x + shz + 1);
        }
    }

    /* UV */
    QVector<QVector2D> UV;
    for(unsigned int i = 0; i < texcoords.size(); i += 2) {
        UV.push_back(QVector2D(texcoords[i] * 8, texcoords[i+1] * 5));
    }

    /* Normals */
    QVector<QVector3D> normalsQ;
    normalsQ.resize(verticesQ.size());
    sphere.calculateNormals(verticesQ, normalsQ, indicesQ);

    /* Tangents */
    QVector<QVector3D> tangentsQ;
    sphere.calculateTangents(verticesQ, indicesQ, UV, tangentsQ);

    /* Set Attributes */
    sphere.init();
    sphere.setAttribute("VertexPosition", verticesQ, program);
    sphere.setAttribute("VertexColor", colorsQ, program);
    sphere.setAttribute("VertexNormal", normalsQ, program);
    sphere.setAttribute("TextureCoordinate", UV, program);
    sphere.setAttribute("VertexTangents", tangentsQ, program);
    sphere.setIndices(indicesQ);
}

void Sphere::render()
{
    sphere.render();
}















