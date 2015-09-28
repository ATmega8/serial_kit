#include "framestatemachine.h"

FrameStateMachine::FrameStateMachine()
{

}

void FrameStateMachine::FrameStateMachineUpdateInfo(FrameStateTypeDef* m_state)
{
    m_state->state = wait;
    m_state->count = 0;
    m_state->dataLen = frameDialog.frameConfig.getFrameDataLen();
    m_state->dataType = frameDialog.frameConfig.getFrameDataType();
    m_state->frameLen = frameDialog.frameConfig.getFrameLen();
    m_state->sp = frameDialog.frameConfig.getFrameSeparator();
    m_state->lineLen = frameDialog.frameConfig.getFrameLineLen();
    m_state->head.headData = frameDialog.frameConfig.getFrameHead();
    m_state->head.len = frameDialog.frameConfig.getFrameHeadLen();
    m_state->tail.tailData = frameDialog.frameConfig.getFrameTail();
    m_state->tail.len = frameDialog.frameConfig.getFrameTailLen();
    m_state->frameBuff.clear();
    m_state->res.clear();
}

void FrameStateMachine::FrameStateMachineDispatch(FrameStateTypeDef* m_state, uint8_t data)
{
   int i, num ;

   switch(m_state->state)
   {
        case wait:
            if(data == *(m_state->head.headData))
            {
                if(m_state->head.len > 1)
                    m_state->state = receiveHead;
                else if(m_state->head.len == 1)
                    m_state->state = receiveData;
                else
                    m_state->state = wait;
            }
            else
                m_state->state = wait;
            break;

        case receiveHead:

            switch(m_state->head.len)
            {
                case 2:
                    if(data == *(m_state->head.headData +1))
                        m_state->state = receiveData;
                    else
                        m_state->state = wait;
                    break;

                case 3:
                    if(m_state->count < 2)
                    {
                        if(data == *(m_state->head.headData +1 + m_state->count))
                        {
                            m_state->state = receiveHead;
                            m_state->count++;
                        }
                        else
                        {
                            m_state->state = wait;
                        }
                    }

                    if(m_state->count == 2)
                    {
                        m_state->count = 0;
                        m_state->state = receiveData;
                    }

                    break;

                case 4:
                    if(m_state->count < 3)
                    {
                        if(data == *(m_state->head.headData +1 + m_state->count))
                        {
                            m_state->state = receiveHead;
                            m_state->count++;
                        }

                    }

                    if(m_state->count == 3)
                    {
                        m_state->count = 0;
                        m_state->state = receiveData;
                    }

                    break;
            }

            break;

        case receiveData:

                if(m_state->count < m_state->frameLen)
                {
                    m_state->frameBuff.append(data);
                    m_state->state = receiveData;
                    m_state->count++;
                }

                if(m_state->count == m_state->frameLen)
                {
                    m_state->state = receiveTail;
                    m_state->count = 0;
                }

            break;

        case receiveTail:

            switch(m_state->tail.len)
            {
                case 1:
                    if(data == *(m_state->tail.tailData))
                        m_state->state = done;
                    else
                        m_state->state = wait;
                    break;

                case 2:
                    if(m_state->count < 2)
                    {
                        if(data == *(m_state->tail.tailData + m_state->count))
                        {
                            m_state->state = receiveHead;
                            m_state->count++;
                        }
                        else
                        {
                            m_state->state = wait;
                        }
                    }

                    if(m_state->count == 2)
                    {
                        m_state->count = 0;
                        m_state->state = done;
                    }

                    break;
            }
            break;

        case done:
            switch (m_state->dataType)
            {
                case FrameConfigure::FrameFloatData:

                    break;

                case FrameConfigure::FrameIntData:

                    switch(m_state->dataLen)
                    {
                        case FrameConfigure::FrameDataLen_OneByte:
                            for(i = 0; i < m_state->frameBuff.length(); i++)
                                m_state->res.append(QString::number(m_state->frameBuff[i]));

                           break;

                        case FrameConfigure::FrameDataLen_TwoBytes:
                            for(i = 0; i < m_state->frameBuff.length()/2; i++)
                            {
                                num = ((int16_t)m_state->frameBuff[2*i] << 8);
                                num |= (uint8_t)m_state->frameBuff[2*i+1];

                                m_state->res.append(QString::number(num));
                                m_state->res.append('\n');
                            }

                           break;

                        case FrameConfigure::FrameDataLen_ThreeBytes:
                            for(i = 0; i < m_state->frameBuff.length()/3; i++)
                            {
                                num =  ((int32_t)m_state->frameBuff[3*i] << 16);
                                num += ((uint8_t)m_state->frameBuff[3*i+1])*256;
                                num += (uint8_t)m_state->frameBuff[3*i+2];

                                m_state->res.append(QString::number(num));
                            }

                           break;

                       case FrameConfigure::FrameDataLen_FourByte:
                            for(i = 0; i < m_state->frameBuff.length()/4; i++)
                            {
                                num =  ((int32_t)m_state->frameBuff[4*i] << 24);
                                num += ((uint8_t)m_state->frameBuff[4*i+1])*65536;
                                num += ((uint8_t)m_state->frameBuff[4*i+2])*256;
                                num += (uint8_t)m_state->frameBuff[4*i+3];

                                m_state->res.append(QString::number(num));
                            }

                            break;
                    }

                    break;

                case FrameConfigure::FrameUintData:
                    switch(m_state->dataLen)
                    {
                        case FrameConfigure::FrameDataLen_OneByte:

                           break;

                        case FrameConfigure::FrameDataLen_TwoBytes:

                           break;

                        case FrameConfigure::FrameDataLen_ThreeBytes:

                           break;

                       case FrameConfigure::FrameDataLen_FourByte:

                           break;
                    }

                    break;

                 case FrameConfigure::FrameRawDate:
                    switch(m_state->dataLen)
                    {
                        case FrameConfigure::FrameDataLen_OneByte:
                            for(i = 0; i < m_state->frameBuff.length(); i++)
                                m_state->res.append(char(m_state->frameBuff[i]));

                           break;

                        case FrameConfigure::FrameDataLen_TwoBytes:
                            for(i = 0; i < m_state->frameBuff.length()/2; i++)
                            {
                                num = ((int16_t)m_state->frameBuff[2*i] << 8);
                                num |= (uint8_t)m_state->frameBuff[2*i+1];

                                m_state->res.append(num);
                            }

                           break;

                        case FrameConfigure::FrameDataLen_ThreeBytes:
                            for(i = 0; i < m_state->frameBuff.length()/3; i++)
                            {
                                num =  ((int32_t)m_state->frameBuff[3*i] << 16);
                                num += ((uint8_t)m_state->frameBuff[3*i+1])*256;
                                num += (uint8_t)m_state->frameBuff[3*i+2];

                                m_state->res.append(num);
                            }

                           break;

                       case FrameConfigure::FrameDataLen_FourByte:
                            for(i = 0; i < m_state->frameBuff.length()/4; i++)
                            {
                                num =  ((int32_t)m_state->frameBuff[4*i] << 24);
                                num += ((uint8_t)m_state->frameBuff[4*i+1])*65536;
                                num += ((uint8_t)m_state->frameBuff[4*i+2])*256;
                                num += (uint8_t)m_state->frameBuff[4*i+3];

                                m_state->res.append(num);
                            }

                            break;
                    }

                    break;

                case FrameConfigure::FrameCharData:

                    break;

                default:
                    break;
            }

            break;

        default:
            break;
   }
}

