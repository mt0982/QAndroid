#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>
#include <glwidget.h>

//#ifndef QT_NO_OPENGL
//#include "mainwidget.h"
//#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

#ifndef QT_NO_OPENGL
    GLWidget w;
    w.show();
#else
    QLabel note("OpenGL Support required");
    note.show();
#endif
    return app.exec();
}
