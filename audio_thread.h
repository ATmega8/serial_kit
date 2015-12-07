#ifndef AUDIO_THREAD_H
#define AUDIO_THREAD_H

#include <QObject>

class audio_thread : public QThread
{
public:
    audio_thread();
};

#endif // AUDIO_THREAD_H
