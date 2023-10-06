#include "view.h"
#include <box2d/box2d.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    View w;
    w.setWindowTitle("Qt Box2d integratiion");
    w.show();
    b2World wa(b2Vec2(1.0f, 1.0f));
    return a.exec();
}
