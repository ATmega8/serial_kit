#include "frameconfigure.h"

FrameConfigure::FrameConfigure()
{

}

 void FrameConfigure::setFrameHead(uint8_t* headlist, uint8_t len)
 {
     int i;

     for(i = 0; i < len; i++)
         frameHead[i] = *(headlist + i);

     frameHeadLen = len;
 }

 void FrameConfigure::setFrameTail(uint8_t* tail,  uint8_t len)
 {
     int i;

     for(i = 0; i < len; i++)
         frameTail[i] = *(tail + i);

     frameTailLen = len;
 }

 void FrameConfigure::setFrameDataType(FrameDataTypeDef type)
 {
     frameDataType = type;
 }

 void FrameConfigure::setFrameDataLen(FrameDataLenTypeDef len)
 {
     frameDataLen = len;
 }

 void FrameConfigure::setFrameOther(char sep, uint8_t len)
 {
      separator = sep;
      lineLen = len;
 }

 void FrameConfigure::setFrameLen(uint8_t len)
 {
     frameLen = len;
 }

 uint8_t FrameConfigure:: getFrameHeadLen()
 {
    return frameHeadLen;
 }

 uint8_t* FrameConfigure::getFrameHead()
 {
    return (uint8_t*)&frameHead;
 }

 uint8_t  FrameConfigure::getFrameTailLen()
 {
    return frameTailLen;
 }

 uint8_t* FrameConfigure::getFrameTail()
 {
     return (uint8_t*)&frameTail;
 }

 FrameConfigure::FrameDataTypeDef FrameConfigure::getFrameDataType()
 {
     return frameDataType;
 }

 FrameConfigure::FrameDataLenTypeDef FrameConfigure::getFrameDataLen()
 {
     return frameDataLen;
 }

 char FrameConfigure::getFrameSeparator()
 {
     return separator;
 }

 uint8_t FrameConfigure::getFrameLineLen()
 {
     return lineLen;
 }

 uint8_t FrameConfigure::getFrameLen()
 {
     return frameLen;
 }
