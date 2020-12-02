#include <QApplication>

#include "Window.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    // Setup opengl format
    // QSurfaceFormat format;
    // format.setRenderableType(QSurfaceFormat::OpenGL);
    // format.setProfile(QSurfaceFormat::CoreProfile);
    // format.setVersion(4, 3);
    // Create window
    Window *window = new Window;
    window->resize(800, 800);
    // window->setFormat(format);
    window->show();
    // Enter execution loop
    return app.exec();
}