#include "audio_thread.h"

audio_thread::audio_thread(QObject *parent)
    :QThread(parent)
{

}

audio_thread::~audio_thread()
{
    wait();
}
