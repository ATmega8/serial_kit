#ifndef FRAMECONFIGURE_H
#define FRAMECONFIGURE_H

#include <stdint.h>

class FrameConfigure
{
public:
    typedef enum
    {
        FrameFloatData,
        FrameFixData,
        FrameIntData,
        FrameUintData,
        FrameCharData,
        FrameRawDate
    } FrameDataTypeDef;

    typedef enum
    {
       FrameDataLen_OneByte,
       FrameDataLen_TwoBytes,
       FrameDataLen_ThreeBytes,
       FrameDataLen_FourByte
    } FrameDataLenTypeDef;

    FrameConfigure();
    void setFrameHead(uint8_t* headlist, uint8_t len);
    void setFrameTail(uint8_t* tail, uint8_t len);
    void setFrameDataType(FrameDataTypeDef type);
    void setFrameDataLen(FrameDataLenTypeDef len);
    void setFrameOther(char sep, uint8_t len);
    void setFrameLen(uint8_t len);

    uint8_t  getFrameHeadLen();
    uint8_t* getFrameHead();
    uint8_t  getFrameTailLen();
    uint8_t* getFrameTail();
    FrameDataTypeDef getFrameDataType();
    FrameDataLenTypeDef getFrameDataLen();
    char getFrameSeparator();
    uint8_t getFrameLineLen();
    uint8_t getFrameLen();


private:
    uint8_t frameHead[4];
    uint8_t frameHeadLen;

    uint8_t frameTail[2];
    uint8_t frameTailLen;

    FrameDataTypeDef frameDataType;
    FrameDataLenTypeDef frameDataLen;

    char separator;

    uint8_t lineLen;

    uint8_t frameLen;
};

#endif // FRAMECONFIGURE_H
