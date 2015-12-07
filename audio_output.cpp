#include "audio_output.h"

audio_output::audio_output(QObject *parent) : QObject(parent)
{

}

void audio_output::init(QBuffer* buffer)
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
    connect(audio, SIGNAL(stateChanged(QAudio::State)), this, SLOT(stateChangedHandler(QAudio::State)));
}

int audio_output::play(int bufferIsHalf)
{
    source->open(QIODevice::ReadWrite);

    if(bufferIsHalf == 0)
    {
        source->seek(0);
        audio->start(source);

        return 1;
    }
    else if(bufferIsHalf == 1)
    {
        source->seek(16384);
        audio->start(source);

        return 0;
    }

}

void audio_output::stateChangedHandler(QAudio::State newState)
{
    switch (newState)
    {
        case QAudio::IdleState:
            audio->stop();
            audio_output::source->close();
            //delete audio;
            break;

        case QAudio::StoppedState:
            if(audio->error() != QAudio::NoError)
            {
                qWarning() << "ERROR!";
            }
            break;

        default:
            break;
    }
}
