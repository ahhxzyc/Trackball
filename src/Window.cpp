#include "Window.h"
#include "Vertex.h"
#include <QDebug>
#include <cmath>
#include <QMatrix4x4>
#include "Transform.h"
#include "Trackball.h"

// Front Verticies
#define VERTEX_FTR Vertex( QVector3D( 0.5f,  0.5f,  0.5f), QVector3D( 1.0f, 0.0f, 0.0f ) )
#define VERTEX_FTL Vertex( QVector3D(-0.5f,  0.5f,  0.5f), QVector3D( 0.0f, 1.0f, 0.0f ) )
#define VERTEX_FBL Vertex( QVector3D(-0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 1.0f ) )
#define VERTEX_FBR Vertex( QVector3D( 0.5f, -0.5f,  0.5f), QVector3D( 0.0f, 0.0f, 0.0f ) )

// Back Verticies
#define VERTEX_BTR Vertex( QVector3D( 0.5f,  0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 0.0f ) )
#define VERTEX_BTL Vertex( QVector3D(-0.5f,  0.5f, -0.5f), QVector3D( 0.0f, 1.0f, 1.0f ) )
#define VERTEX_BBL Vertex( QVector3D(-0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 0.0f, 1.0f ) )
#define VERTEX_BBR Vertex( QVector3D( 0.5f, -0.5f, -0.5f), QVector3D( 1.0f, 1.0f, 1.0f ) )

// Create a colored cube
static const Vertex data[] = {
  // Face 1 (Front)
    VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
    VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
  // Face 2 (Back)
    VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
    VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
  // Face 3 (Top)
    VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
    VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
  // Face 4 (Bottom)
    VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
    VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
  // Face 5 (Left)
    VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
    VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
  // Face 6 (Right)
    VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
    VERTEX_BBR, VERTEX_BTR, VERTEX_FTR
};

Transform trans;
Trackball trackball;

bool busy = false;

Window::~Window() {
    mVertices->destroy();
    mVao->destroy();
    delete mProgram;
    delete mVertices;
    delete mVao;
}

void Window::initializeGL() {
    setMouseTracking(true);
    initializeOpenGLFunctions();
    // Create program
    mProgram = new QOpenGLShaderProgram;
    mProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "../../src/shader_src/vertexShader.glsl");
    mProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "../../src/shader_src/fragmentShader.glsl");
    mProgram->link();
    // Create vbo
    mVertices = new QOpenGLBuffer;
    mVertices->create();
    mVertices->bind();
    mVertices->setUsagePattern(QOpenGLBuffer::StaticDraw);
    mVertices->allocate(::data, sizeof(::data));
    // Create vao
    mVao = new QOpenGLVertexArrayObject;
    mVao->create();
    mVao->bind();
    mProgram->setAttributeBuffer(0, GL_FLOAT, Vertex::POS_OFFSET, Vertex::POS_TUPLE_SIZE, Vertex::STRIDE);
    mProgram->enableAttributeArray(0);
    mProgram->setAttributeBuffer(1, GL_FLOAT, Vertex::COLOR_OFFSET, Vertex::COLOR_TUPLE_SIZE, Vertex::STRIDE);
    mProgram->enableAttributeArray(1);
    // Unbind
    mVertices->release();
    mVao->release();
    // Initialize transformation
    trans.translate(QVector3D(0, 0, -5.f));
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Start timer, 100 frames per second
    startTimer(10);
}

void Window::paintGL() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Bind program and vao
    mProgram->bind();
    mVao->bind();
    // Set model matrix
    QMatrix4x4 model = trans.getMatrix();
    if (mousePressed) {
        trans.rotate(trackball.getRotation());
        model = trans.getMatrix();
        trans.rotate(trackball.getReverseRotation());
    }
    mProgram->setUniformValue(mProgram->uniformLocation("model"), model);
    // Set projection matrix
    QMatrix4x4 projection;
    projection.setToIdentity();
    projection.perspective(45.f, (float) width / height, 0.1f, 100.f);
    mProgram->setUniformValue(mProgram->uniformLocation("projection"), projection);
    // Draw
    glDrawArrays(GL_TRIANGLES, 0, sizeof(::data) / sizeof(Vertex));
    // Unbind
    mProgram->release();
    mVao->release();
}

void Window::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    width = w;
    height = h;
}

void Window::timerEvent(QTimerEvent *event) {
    // Update display
    update();
}

void Window::mouseMoveEvent(QMouseEvent *event) {
    float x = (float)event->x() / width * 2 - 1;
    float y = 1 - (float)event->y() / height * 2;
    trackball.update(QVector2D(x, y));
    mouseValid = true;
}

void Window::mousePressEvent(QMouseEvent *event) {
    trackball.set();
    mousePressed = true;
}
void Window::mouseReleaseEvent(QMouseEvent *event) {
    mousePressed = false;
    trans.rotate(trackball.getRotation());
}