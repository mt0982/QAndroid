#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent): QOpenGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(redraw()));
    timer.start(1.0f);
    time.start();
    rotationTime.start();

    /* Set FPS Label */
    QFont font;
    font.setPointSize(16);
    font.setBold(true);

    label = new QLabel(parent);
    label->setText("AAA");
    label->setStyleSheet("QLabel {background-color : black; color : white;}");
    label->setFont(font);
    label->setMinimumWidth(100);

    QGridLayout grid;
    grid.addWidget(label);

    this->setLayout(&grid);
}

GLWidget::~GLWidget()
{
    makeCurrent();
    doneCurrent();
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);

    /* Shader Program */
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/s/shader.vsh");
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/s/shader.fsh");
    program.link();////

    /* Textures */
    diffuseMap = new QOpenGLTexture(QImage(":/t/Texture/metal.jpg"));
    normalMap = new QOpenGLTexture(QImage(":/t/Texture/metal_n.jpg"));
    ambientMap = new QOpenGLTexture(QImage(":/t/Texture/metal_ao.jpg"));
    specularMap = new QOpenGLTexture(QImage(":/t/Texture/metal_s.jpg"));

    diffuseMap->setMinificationFilter(QOpenGLTexture::Linear);
    diffuseMap->setMagnificationFilter(QOpenGLTexture::Linear);

    /* Init Objects */
    box.init(program);
    sphere.init(program);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    MVMat = camera.getWorldToViewMatrix();

    /* Rotate Matrix */
    QMatrix4x4 matrix;
    //matrix.translate(-camera.getPosition());
    matrix.rotate(rotation);

    /* Bind Textures */
    diffuseMap->bind(0);
    normalMap->bind(1);
    ambientMap->bind(2);
    specularMap->bind(3);

    /* Program */
    program.bind();
    program.setUniformValue("MVMat", MVMat * matrix);
    program.setUniformValue("ProjMat", ProjMat);
    program.setUniformValue("cameraPosition", camera.getPosition() * matrix);
    program.setUniformValue("lightPosition", QVector3D(0, 1, 4) * matrix);
    program.setUniformValue("diffuseMap", 0);
    program.setUniformValue("normalMap", 1);
    program.setUniformValue("ambientMap", 2);
    program.setUniformValue("specularMap", 3);
    program.setUniformValue("time", rotationTime.elapsed() / 1000.0f);
    //sphere.render();
    box.render();
    program.release();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    ProjMat.setToIdentity();
    ProjMat.perspective(60, (float)w/h, 0.01f, 100.0f);
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    //camera.mouseUpdate(QVector2D(e->x(), e->y()));

    QVector2D diff = QVector2D(e->localPos()) - startPoint;

    /* Mouse Position Diff */
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    /* Acceleration */
    qreal acc = diff.length() / 250.0;

    /* Rotation */
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    /* Angular Speed */
    angularSpeed = acc;
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
    startPoint = QVector2D(e->x(), e->y());
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QVector2D diff = QVector2D(e->localPos()) - startPoint;

    /* Mouse Position Diff */
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    /* Acceleration */
    qreal acc = diff.length() / 100.0;

    /* Rotation */
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    /* Angular Speed */
    angularSpeed += acc;
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_W:
        camera.moveForward();
        break;
    case Qt::Key_A:
        camera.moveLeft();
        break;
    case Qt::Key_S:
        camera.moveBackward();
        break;
    case Qt::Key_D:
        camera.moveRight();
        break;
    case Qt::Key_Space:
        camera.moveUp();
        break;
    case Qt::Key_X:
        camera.moveDown();
        break;
    default:
        break;
    }
}

void GLWidget::redraw()
{
    update();
    if((fps % 100) == 0) {
        setWindowTitle("FPS: " + QString::number(100 /*klatek*/ * 1000 /*milisekund*/ / time.elapsed()));
        label->setText("FPS: " + QString::number(100 * 1000 / time.elapsed()));
        time.restart();
    }
    fps++;

    /* Decrease Speed */
    angularSpeed *= 0.99;

    if (angularSpeed < 0.01) {
        angularSpeed = 0.0;
    } else {
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    }
}













