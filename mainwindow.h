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
#include <QStyle>
#include <QDesktopWidget>

#include "framedialog.h"
#include "framestatemachine.h"
#include "audio_output.h"
#include "audio_thread.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

typedef enum
{
    AudioBuffer_Play,
    AudioBuffer_ReceiveData,
    AudioBuffer_Idle
} AudioBufferStateTypeDef;

typedef struct
{
    QBuffer buffer;
    int     bufferIndex;
    AudioBufferStateTypeDef state;
} AudioBufferTypeDef;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void serialInfoUpdate(void);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void serialReader(void);

    void serialErrorHandler(QSerialPort::SerialPortError error);

    void serialTimeHandler(void);

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_portnum_activated(const QString &arg1);

    void playAudioData(QAudio::State newState);

private:
    Ui::MainWindow *ui;
    QSerialPort serialPort;
    QFile receiveFile;
    QTimer serial_timer;
    QByteArray serialReadData;

    int readCount;
    int bufferIsHalf;
    int audioIndex;

    FrameStateMachine* frameSM;
    FrameStateMachine::FrameStateTypeDef m_state;

    audio_output w;

    AudioBufferTypeDef audioBuffer1;
    AudioBufferTypeDef audioBuffer2;
    AudioBufferTypeDef audioBuffer3;

    int initBuffer;
    int currentBuffer;

    audio_output audioOutput;
    audio_thread audioThread;


    void AudioBufferInit(void);
};

#endif // MAINWINDOW_H
