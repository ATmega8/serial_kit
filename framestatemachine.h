#ifndef FRAMESTATEMACHINE_H
#define FRAMESTATEMACHINE_H

#include <stdint.h>

#include <QByteArray>
#include <QString>
#include <QTextCharFormat>
#include <QTextCodec>

#include "framedialog.h"
#include "frameconfigure.h"

class FrameStateMachine
{
public:
    typedef enum
    {
        disable,
        wait,
        receiveHead,
        receiveData,
        receiveTail,
        done
    } FrameState;

    typedef struct
    {
        uint8_t* headData;
        uint8_t len;
    } FrameHeadTypeDef;

    typedef struct
    {
        uint8_t* tailData;
        uint8_t len;
    } FrameTailTypeDef;

    typedef struct
    {
       FrameState state;

       char sp;
       uint8_t count;
       uint8_t frameLen;
       uint8_t lineLen;

       QByteArray frameBuff;
       QString res;

       FrameHeadTypeDef head;
       FrameTailTypeDef tail;
       FrameConfigure::FrameDataTypeDef dataType;
       FrameConfigure::FrameDataLenTypeDef dataLen;
    }  FrameStateTypeDef;

    FrameStateMachine();

    void FrameStateMachineDispatch(FrameStateTypeDef* m_state, uint8_t data);
    void FrameStateMachineUpdateInfo(FrameStateTypeDef* m_state);

    FrameDialog frameDialog;
};

#endif // FRAMESTATEMACHINE_H
