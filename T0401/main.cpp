#include "widget_user_notes.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget_user_notes w;
    w.show();
    return a.exec();
}
