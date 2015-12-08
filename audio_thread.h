#ifndef AUDIO_THREAD_H
#define AUDIO_THREAD_H

#include <QObject>
#include <QThread>
#include <QBuffer>

#include "audio_output.h"

class audio_thread : public QThread
{
    Q_OBJECT

public:
    audio_thread(QObject* parent = 0);
    ~audio_thread();

    void startAudioOutput(QBuffer *buffer);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    audio_output audio;
    QBuffer* buf;

signals:

};

#endif // AUDIO_THREAD_H
