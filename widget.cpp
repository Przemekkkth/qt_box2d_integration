#include "widget.h"
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>
#include <QMouseEvent>

constexpr float PIXELS_PER_METERS = 32.0f;
constexpr float PI = 3.14159f;

float View::pixel_to_meters(const float &x)
{
    return x/PIXELS_PER_METERS;
}

float View::meters_to_pixels(const float &x)
{
    return x*PIXELS_PER_METERS;
}

float View::deg_to_rad(const float &x)
{
    return PI*x/180.0;
}

float View::rad_to_deg(const float &x)
{
    return 180.0*x/PI;
}

View::View()
    : m_world(b2Vec2(0.f, 9.8f)), m_scene(new QGraphicsScene(this))
{
    resize(800, 600);
    m_scene->setSceneRect(0,0,800,600);
    //top
    createEntity(400,590,800, 20,m_horizontalWall);
    //left
    createEntity(10, 300, 20,600,m_verticalWall);
    //right
    createEntity(790,300, 20,600,m_verticalWall);
    //bottom
    createEntity(400, 10, 800, 20,m_horizontalWall);
    setScene(m_scene);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &View::updateScene);
    timer->start(1000/60);
}

View::~View()
{
}

b2Body *View::createEntity(int pos_x, int pos_y, int size_x, int size_y, uintptr_t type)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(pixel_to_meters(pos_x), pixel_to_meters(pos_y));
    if(type == m_box || type == m_circle)
    {
        bodyDef.type = b2_dynamicBody;
    }
    else
    {
        bodyDef.type = b2_staticBody;
    }




    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0;
    if(type != m_circle)
    {
        fixtureDef.friction = 0.4;
        fixtureDef.restitution= 0.5;
        b2PolygonShape b2shape;
        b2shape.SetAsBox(pixel_to_meters(size_x/2.0),pixel_to_meters(size_y/2.0));
        fixtureDef.shape = &b2shape;
    }
    else
    {
        fixtureDef.friction = 0.6;
        fixtureDef.restitution= 0.8;
        b2CircleShape b2shape;
        b2shape.m_radius = pixel_to_meters(size_x/2.0);
        fixtureDef.shape = &b2shape;
    }

    b2Body* res = m_world.CreateBody(&bodyDef);
    res->CreateFixture(&fixtureDef);
    res->GetUserData().pointer = type;

    return res;
}

void View::displayWorld()
{
    m_world.Step(1.0/60,int32(8),int32(3));


    for (b2Body* body= m_world.GetBodyList(); body!=nullptr; body=body->GetNext())
    {
        if(body->GetUserData().pointer == m_horizontalWall)
        {
            int w = 800;
            int h = 20;
            QGraphicsRectItem* rectItem = new QGraphicsRectItem(-w/2.0f, -h/2.0f, w, h);
            rectItem->setTransformOriginPoint(QPointF(w/2.0f, h/2.0f));
            rectItem->setPos(meters_to_pixels(body->GetPosition().x), meters_to_pixels(body->GetPosition().y));
            rectItem->setRotation(rad_to_deg(body->GetAngle()));
            rectItem->setBrush(QBrush(Qt::white));
            rectItem->setPen(QPen(Qt::white));
            m_scene->addItem(rectItem);
        }
        else if(body->GetUserData().pointer == m_verticalWall)
        {
            int w = 20;
            int h = 600;
            QGraphicsRectItem* rectItem = new QGraphicsRectItem(-w/2.0f, -h/2.0f, w, h);
            rectItem->setTransformOriginPoint(QPointF(w/2.0f, h/2.0f));
            rectItem->setPos(meters_to_pixels(body->GetPosition().x), meters_to_pixels(body->GetPosition().y));
            rectItem->setRotation(rad_to_deg(body->GetAngle()));
            rectItem->setBrush(QBrush(Qt::white));
            rectItem->setPen(QPen(Qt::white));
            m_scene->addItem(rectItem);
        }
        else if(body->GetUserData().pointer == m_box){
            int w = 25;
            int h = 25;
            QGraphicsRectItem* rectItem = new QGraphicsRectItem(-w/2.0f, -h/2.0f, w, h);
            rectItem->setTransformOriginPoint(QPointF(0.0f, 0.0f));
            rectItem->setPos(meters_to_pixels(body->GetPosition().x), meters_to_pixels(body->GetPosition().y));
            rectItem->setRotation(rad_to_deg(body->GetAngle()));
            rectItem->setBrush(QBrush(Qt::blue));
            rectItem->setPen(QPen(Qt::blue));
            m_scene->addItem(rectItem);
        }
        else if(body->GetUserData().pointer == m_circle){
            int w = 25;
            int h = 25;
            QGraphicsEllipseItem* rectItem = new QGraphicsEllipseItem(-w/2.0f, -h/2.0f, w, h);
            rectItem->setTransformOriginPoint(QPointF(0.0f, 0.0f));
            rectItem->setPos(meters_to_pixels(body->GetPosition().x), meters_to_pixels(body->GetPosition().y));
            //rectItem->setRotation(rad_to_deg(body->GetAngle()));
            rectItem->setBrush(QBrush(Qt::red));
            rectItem->setPen(QPen(Qt::red));
            m_scene->addItem(rectItem);
        }
    }
}

void View::updateScene()
{
    m_scene->clear();
    displayWorld();
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        createEntity(event->position().x(), event->position().y(), 25, 25, m_box);
    }
    if(event->button() == Qt::RightButton)
    {
        createEntity(event->position().x(), event->position().y(), 25, 25, m_circle);
    }
}
