#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLTexture>
#include <QVector>
#include <QVector2D>
#include <QVector3D>
#include <QMatrix3x3>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTouchEvent>
#include <QTime>
#include <QTimer>
#include <mesh.h>
#include <Interaction/camera.h>
#include <Object/box.h>
#include <Object/sphere.h>
#include <QLabel>
#include <QGridLayout>

class GLWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
private:
    Q_OBJECT
    QMatrix4x4 MVMat, ProjMat;
    QTimer timer;
    QTime time, rotationTime;
    Camera camera;

    int fps;
    QVector2D startPoint, endPoint;

    QOpenGLShaderProgram program;
    QOpenGLTexture *diffuseMap;
    QOpenGLTexture *normalMap;
    QOpenGLTexture *ambientMap;
    QOpenGLTexture *specularMap;

    Box box;
    Sphere sphere;

    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;

    QLabel *label;

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void keyPressEvent(QKeyEvent *e);

private slots:
    void redraw();
};

#endif // GLWIDGET_H





















