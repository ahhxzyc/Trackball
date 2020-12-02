#pragma once

#include <QVector3D>

class Vertex {

private:
    QVector3D pos;
    QVector3D color;

public:
    Vertex(QVector3D p, QVector3D c): pos(p), color(c) {}

    // Constants for use
    static const int POS_OFFSET = 0;
    static const int COLOR_OFFSET = 12;
    static const int POS_TUPLE_SIZE = 3;
    static const int COLOR_TUPLE_SIZE = 3;
    static const int STRIDE = 24;
};