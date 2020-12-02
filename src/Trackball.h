#pragma once


#include <QVector3D>
#include <QQuaternion>
#include <QVector2D>


class Trackball {
private:
    float radius = 1.f;
    const float PI = acosf(-1.f);
    QVector2D prev;
    QVector2D cur;

public:
    QQuaternion getRotation() {
        // Return 0 retation if prev == cur
        if (qFuzzyCompare(prev, cur)) {
            return QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), 0);
        }
        // Find the angle between two vectors using dot product
        QVector3D prev3 = toVectorOnBall(prev);
        QVector3D cur3 = toVectorOnBall(cur);
        float angle = acosf(QVector3D::dotProduct(prev3, cur3) / (prev3.length() * cur3.length())) * 180.f / PI;
        // Return the quaternion representing the rotation
        return QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(prev3, cur3), angle);
    }
    QQuaternion getReverseRotation() {
        QQuaternion q = getRotation();
        q.setVector(-q.vector());
        return q;
    }
    QVector3D toVectorOnBall(QVector2D v) {
        QVector3D retVector;
        float arc = v.length();
        float a = arc / radius;     // angle between retVector and vertical direction(the direction that points outward through the screen)
        float b = atan2f(v[1], v[0]);
        retVector[0] = radius * sinf(a) * cosf(b);
        retVector[1] = radius * sinf(a) * sinf(b);
        retVector[2] = radius * cosf(a);
        return retVector;
    }
    void update(QVector2D pos) {
        cur = pos;
    }
    void set() {
        prev = cur;
    }
    
};