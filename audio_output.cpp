#include "audio_output.h"
#include "mainwindow.h"

audio_output::audio_output()
{

}

void audio_output::init(QBuffer *buffer)
{
    source = buffer;

    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::BigEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());

    if(!info.isFormatSupported(format))
    {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    audio = new QAudioOutput(format, this);
    audio->setBufferSize(BUFFER_SIZE);

    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(stateChangedHandler(QAudio::State)));

    qDebug() << "audio output init ok";

    qDebug() << "start play audio buffer";

    qDebug() << "current thread id:" << QThread::currentThreadId();


    source->open(QIODevice::ReadWrite);
    audio->start(source);
}

void audio_output::stateChangedHandler(QAudio::State newState)
{
    switch (newState)
    {
        case QAudio::ActiveState:
            qDebug() << "audio output active state";
            break;

        case QAudio::SuspendedState:
            qDebug() << "audio output suspend state";

        case QAudio::IdleState:
            audio->stop();
            qDebug() << "audio output idle state";
            audio_output::source->seek(0);
            emit finished();
            delete audio;
            break;

        case QAudio::StoppedState:
            qDebug() << "audio output stopped state";
            if(audio->error() != QAudio::NoError)
            {
                qWarning() << "ERROR!";
            }
            break;

        default:
            break;
    }
}
