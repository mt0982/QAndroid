#include "camera.h"

Camera::Camera()
{
    viewDirection = QVector3D(0.0f, 0.0f, -1.0f);
    UP = QVector3D(0.0f, 1.0f, 0.0f);
    position = QVector3D(0.0f, 0.0f, 4.0f);
    movementSpeed = 0.1f;
}

void Camera::mouseUpdate(const QVector2D &newMousePosition)
{
    float rotatnionSpeed = 0.15f;

    /* Set Matrix */
    QMatrix4x4 rotationAxisX, rotationAxisY;

    /* Calculate Delta, Jump Problem Reduce */
    QVector2D mouseDelta = newMousePosition - oldMousePosition;
    if(mouseDelta.length() > 50.0f) {
        oldMousePosition = newMousePosition;
        return;
    }

    /* Calculate Angle Rotation */
    QVector3D toRotateAround = QVector3D::crossProduct(viewDirection, UP);
    rotationAxisX.rotate(-mouseDelta.x() * rotatnionSpeed, UP);
    rotationAxisY.rotate(-mouseDelta.y() * rotatnionSpeed, toRotateAround);
    QMatrix4x4 rotator = rotationAxisX * rotationAxisY;
    viewDirection = rotator * viewDirection;

    oldMousePosition = newMousePosition;
}

void Camera::setPosition(const QVector3D &value)
{
    position = value;
}

QVector3D Camera::getPosition() const
{
    return position;
}

QMatrix4x4 Camera::getWorldToViewMatrix() const
{
    QMatrix4x4 mat;
    mat.setToIdentity();
    mat.lookAt(position, position + viewDirection, UP);
    return mat;
}

void Camera::moveForward()
{
    position += movementSpeed * viewDirection;
}

void Camera::moveBackward()
{
    position -= movementSpeed * viewDirection;
}

void Camera::moveLeft()
{
    QVector3D moveDirection = QVector3D::crossProduct(viewDirection, UP);
    position -= movementSpeed * moveDirection;
}

void Camera::moveRight()
{
    QVector3D moveDirection = QVector3D::crossProduct(viewDirection, UP);
    position += movementSpeed * moveDirection;
}

void Camera::moveUp()
{
    position += movementSpeed * UP;
}

void Camera::moveDown()
{
    position -= movementSpeed * UP;
}










