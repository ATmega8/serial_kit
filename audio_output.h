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
    void play(QString fileName);

signals:

public slots:

private:
    QFile sourcerFile;
    QAudioOutput* audio;

private slots:
    void stateChangedHandler(QAudio::State newState);
};

#endif // AUDIO_OUTPUT_H
