#include "pomodoromain.h"
#include "./ui_pomodoromain.h"

#include <iostream>
#include <QMessageBox>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; //nanoseconds, system_clock, seconds

PomodoroMain::PomodoroMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PomodoroMain)
    , darkMode(true)
    , timerStopped(false)
{
    ui->setupUi(this);

    // Timer setup
    pomoTimer = new QTimer(this);
    connect(pomoTimer, &QTimer::timeout, this, &PomodoroMain::updateTimer);

    setWindowTitle("");

    setFixedSize(500, 280); // set a fixed size for the window

}

PomodoroMain::~PomodoroMain()
{
    delete ui;
}


void PomodoroMain::updateTimer() {

        if (timerMinutes == 0 && timerSeconds == 0 || timerStopped) {

            pomoTimer->stop();
            ui->timer->setText("00:00");
            ui->startButton->setText("Start");

            if(timerStopped){
                std::cout << "[Debug] Timer finished, manually stopped by user" << std::endl;
            } else {
                std::cout << "[Debug] Timer finished" << std::endl;
            }

            return;
        }

        QString timeStr = QString("%1:%2")
                              .arg(timerMinutes, 2, 10, QChar('0'))
                              .arg(timerSeconds, 2, 10, QChar('0'));
        ui->timer->setText(timeStr);

        if (timerSeconds == 0) {
            timerMinutes--;
            timerSeconds = 59;
        } else {
            timerSeconds--;
        }

}

void PomodoroMain::timerStart(){

    int minutes = ui->timeWork->value();
    breakQty = ui->timeQty->value();

    timerMinutes = minutes;
    timerSeconds = 0;

    if(timerMinutes == 0){ // 20 minutes by default
        timerMinutes = 20;
    }

    updateTimer();
    pomoTimer->start(1000);

}

void PomodoroMain::on_startButton_clicked()
{
    if(ui->startButton->text() == "Start"){
        timerStart();
        timerStopped = false;
        ui->startButton->setText("Stop");

    } else {
        timerStopped = true;
        ui->startButton->setText("Start");
    }

}


void PomodoroMain::on_exitPomoButton_clicked()
{
    PomodoroMain::close();
}


void PomodoroMain::on_darklightButton_clicked()
{
    if (!darkMode) {
        // Switch to dark mode
        ui->darklightButton->setText("☾");
        setStyleSheet("QMainWindow {"
                      "background-color: #1C1C1E;"
                      "}"
                      "QLabel {"
                      "color: #dcdcdc;"   // Labels' text color in dark mode
                      "}"
                      "QPushButton {"
                      "color: #dcdcdc;"    // Button text color in dark mode
                      "}"
                      "QSpinBox {"
                      "background-color: #1C1C1E;"    // Button text color in dark mode
                      "color: #dcdcdc;"
                      "}"
                      );
        darkMode = true;

    } else {
        // Switch to light mode
        ui->darklightButton->setText("☀︎");
        setStyleSheet("QMainWindow {"
                      "background-color: #dcdcdc;"
                      "}"
                      "QLabel {"
                      "color: #1C1C1E;"    // Labels' text color in light mode
                      "}"
                      "QPushButton {"
                      "color: #1C1C1E;"    // Button text color in light mode
                      "}"
                      "QSpinBox {"
                      "background-color: #dcdcdc;"    // Button text color in dark
                      "color: #1C1C1E;"
                      "}"
                      );
        darkMode = false;
    }
}
