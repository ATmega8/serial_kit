#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTimer>
#include <QByteArray>

#include "framedialog.h"
#include "framestatemachine.h"
#include "audio_output.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void serialInfoUpdate(void);


private slots:
    //void on_portnum_clicked(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void serialReader(void);

    void serialErrorHandler(QSerialPort::SerialPortError error);

    void serialTimeHandler(void);

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_portnum_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSerialPort serialPort;
    QFile receiveFile;
    QTimer serial_timer;
    QByteArray serialReadData;

    int readCount;

    FrameStateMachine* frameSM;
    FrameStateMachine::FrameStateTypeDef m_state;
    audio_output w;
};

#endif // MAINWINDOW_H
