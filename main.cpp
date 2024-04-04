#include <QApplication>
#include "view.h"
int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    View v;
    v.setFixedSize(QSize(1200, 800));


    v.show();

    a.exec();
}
