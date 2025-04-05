#ifndef POMODOROMAIN_H
#define POMODOROMAIN_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class PomodoroMain;
}
QT_END_NAMESPACE

class PomodoroMain : public QMainWindow
{
    Q_OBJECT

public:
    PomodoroMain(QWidget *parent = nullptr);
    ~PomodoroMain();


public slots:
    void timerStart();


private:
    Ui::PomodoroMain *ui;
    QTimer *pomoTimer;
    int inMinutes;
    int inBreakMinutes;

    int timerMinutes;
    int timerSeconds;
    int breakQty;
    bool darkMode;
    bool timerStopped;
    bool onBreak;

private slots:
    void on_startButton_clicked();
    void updateTimer();


    void on_exitPomoButton_clicked();
    void on_darklightButton_clicked();
};
#endif // POMODOROMAIN_H
