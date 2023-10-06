#ifndef VIEW_H
#define VIEW_H

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

    b2Body* createEntity(int pos_x,int pos_y, int size_x,int size_y, uintptr_t type);
    void displayWorld();
private slots:
    void updateScene();
private:
    void makeScreenShot();
    uintptr_t m_horizontalWall = 0, m_verticalWall = 1, m_box = 2,  m_circle =4 ;
    b2World m_world;
    QGraphicsScene* m_scene;

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // VIEW_H
