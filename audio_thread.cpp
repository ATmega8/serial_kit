#include "audio_thread.h"

audio_thread::audio_thread(QObject *parent)
    :QThread(parent)
{
    qDebug("construct audio_thread class\n");
}

audio_thread::~audio_thread()
{
    wait();
}

void audio_thread::startAudioOutput(QBuffer* buffer)
{
    /*Audio Device Init*/
    audio.init();
    buf = buffer;

    start(QThread::LowPriority);

    qDebug("audio output thread started\n");
}

void audio_thread::run()
{
    qDebug("audio output is running\n");


    audio.play(buf);
}
