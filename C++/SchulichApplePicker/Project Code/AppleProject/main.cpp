#include <QApplication>
#include <memory>

#include "View/view.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*MainWindow *w = new MainWindow();
    w->show();*/

    shared_ptr<View> v = shared_ptr<View>(new View());

    return a.exec();
}
