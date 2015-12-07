#ifndef AUDIO_OUTPUT_H
#define AUDIO_OUTPUT_H

#include <QObject>
#include <QFile>
#include <QBuffer>
#include <QAudioOutput>
#include <QDebug>

class audio_output : public QObject
{
    Q_OBJECT
public:
    explicit audio_output(QObject *parent = 0);
    int play(int bufferIsHalf);
    void init(QBuffer* buffer);

signals:

public slots:

private:
    QAudioOutput* audio;
    QBuffer* source;

private slots:
    void stateChangedHandler(QAudio::State newState);
};

#endif // AUDIO_OUTPUT_H
