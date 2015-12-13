#ifndef AUDIO_OUTPUT_H
#define AUDIO_OUTPUT_H

#include <QObject>
#include <QFile>
#include <QBuffer>
#include <QAudioOutput>
#include <QDebug>
#include <QMutex>

class audio_output : public QObject
{
    Q_OBJECT

#define BUFFER_SIZE 28*100

public:

    typedef enum
    {
        IdleState,
        StoppedState,
        PlayState
    } OutputStateTypeDef;

    explicit audio_output();

    QAudioOutput* audio;

signals:
    void finished();
    void play(QBuffer *buffer);

public slots:
    void init(QBuffer *buffer);

private:
    QBuffer* source;
    OutputStateTypeDef state;
    QMutex mutex;

private slots:
    void stateChangedHandler(QAudio::State newState);
};

#endif // AUDIO_OUTPUT_H
