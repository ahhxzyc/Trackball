#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QWidget>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QVector2D>


class Window : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core {
Q_OBJECT

private:
    QOpenGLShaderProgram *mProgram;
    QOpenGLVertexArrayObject *mVao;
    QOpenGLBuffer *mVertices;
    int width;
    int height;
    bool mouseValid = false;
    bool mousePressed = false;

public:
    Window() {}
    ~Window();

protected:
    // inherited opengl functions
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    // inherited timer function
    void timerEvent(QTimerEvent *event) override;

    // inherited event handlers
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};