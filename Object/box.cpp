#include "box.h"

Box::Box()
{

}

void Box::init(QOpenGLShaderProgram &program)
{
    /* Vertices */
    vertices = {{-1, -1, -1}, {1, -1, -1},  {1, 1, -1},  {-1, 1, -1},   //front
                {1, -1, -1},  {1, -1, 1},   {1, 1, 1},   {1, 1, -1},    //right
                {-1, -1, 1},  {-1, -1, -1}, {-1, 1, -1}, {-1, 1, 1},    //left
                {1, -1, 1}, {-1, -1, 1}, {-1, 1, 1}, {1, 1, 1},         //back
                {-1, 1, -1}, {1, 1, -1}, {1, 1, 1}, {-1, 1, 1},         //top
                {-1, -1, -1}, {1, -1, -1}, {1, -1, 1}, {-1, -1, 1}};    //bottom

    /* Indices */
    QVector<uint> indices = {0, 1, 2, 0, 2, 3,
                             4, 5, 6, 4, 6, 7,
                             8, 9, 10, 8, 10, 11,
                             12, 13, 14, 12, 14, 15,
                             16, 17, 18, 16, 18, 19,
                             20, 21, 22, 20, 22, 23};

    /* Normals */
    QVector<QVector3D> normals = {{0, 0, -1}, {0, 0, -1}, {0, 0, -1}, {0, 0, -1},
                                  {1, 0, 0},  {1, 0, 0},  {1, 0, 0},  {1, 0, 0},
                                  {-1, 0, 0},  {-1, 0, 0},  {-1, 0, 0},  {-1, 0, 0},
                                  {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1},
                                  {0, 1, 0}, {0, 1, 0}, {0, 1, 0}, {0, 1, 0},
                                  {0, -1, 0}, {0, -1, 0}, {0, -1, 0}, {0, -1, 0}};

    /* Colors */
    QVector<QVector3D> colors;
    for(int i = 0; i < vertices.size(); i++) colors.push_back(QVector3D(0.5, 0.5, 0.5));

    /* UV */
    float t = 1;
    QVector<QVector2D> UV;
    for(int i = 0; i < vertices.size(); i+= 4) {
        UV.push_back(QVector2D(0,0));
        UV.push_back(QVector2D(0,t));
        UV.push_back(QVector2D(t,t));
        UV.push_back(QVector2D(t,0));
    }

    /* Tangents */
    QVector<QVector3D> tangents;
    box.calculateTangents(vertices, indices, UV, tangents);

    /* Set Attributes */
    box.init();
    box.setAttribute("VertexPosition", vertices, program);
    box.setAttribute("VertexColor", colors, program);
    box.setAttribute("VertexNormal", normals, program);
    box.setAttribute("TextureCoordinate", UV, program);
    box.setAttribute("VertexTangents", tangents, program);
    box.setIndices(indices);
}

void Box::render()
{
    box.render();
}





















