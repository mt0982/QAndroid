#ifndef CAMERA_H
#define CAMERA_H

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <QDebug>

class Camera {
private:
    QVector3D position;
    QVector3D viewDirection;
    QVector3D UP;
    QVector2D oldMousePosition;
    float movementSpeed;

public:
    Camera();
    QMatrix4x4 getWorldToViewMatrix() const;
    void mouseUpdate(const QVector2D &newMousePosition);
    QVector3D getPosition() const;
    void setPosition(const QVector3D &value);

    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
};

#endif // CAMERA_H

















