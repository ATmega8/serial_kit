#include "audio_output.h"
#include "mainwindow.h"

audio_output::audio_output(QObject *parent) : QObject(parent)
{

}

void audio_output::init()
{
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
    audio->setBufferSize(28*1024);
}

void audio_output::play(QBuffer* buffer)
{
    source = buffer;
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
            //audio_output::source->close();
            //delete audio;
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
