#include "pomodoromain.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PomodoroMain w;
    w.show();
    return a.exec();
}
