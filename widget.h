#ifndef WIDGET_H
#define WIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <box2d/box2d.h>

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View();
    ~View();

    static float pixel_to_meters(const float& x);
    static float meters_to_pixels(const float& x);
    static float deg_to_rad(const float& x);
    static float rad_to_deg(const float& x);

    b2Body* create_box(int pos_x,int pos_y, int size_x,int size_y,b2BodyType type = b2_dynamicBody);
    void displayWorld();
private slots:
    void updateScene();
private:
    uintptr_t staticBoddy = 0x00, dynamicBody = 0x01 ;
    b2World m_world;
    QGraphicsScene* m_scene;

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
};
#endif // WIDGET_H
