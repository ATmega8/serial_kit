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

protected:

private:

private slots:

public slots:

signals:

};

#endif // AUDIO_THREAD_H
