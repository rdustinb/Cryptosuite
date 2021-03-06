#ifndef __sha1_h
#define __sha1_h

#include <inttypes.h>
#include "Print.h"

#define HASH_LENGTH 20
#define BLOCK_LENGTH 64

class SHA1 : public Print
{
  union _buffer {
    uint8_t b[BLOCK_LENGTH];
    uint32_t w[BLOCK_LENGTH/4];
  };
  union _state {
    uint8_t b[HASH_LENGTH];
    uint32_t w[HASH_LENGTH/4];
  };

  public:
    SHA1(void);
    uint8_t* result(void);
    uint8_t resultLen(void);
    uint8_t* resultHmac(void);
    virtual size_t write(uint8_t);
    using Print::write;
  private:
    void reset(void);
    void resetHmac(const uint8_t* secret, int secretLength);
    void pad();
    void addUncounted(uint8_t data);
    void hashBlock();
    uint32_t rol32(uint32_t number, uint8_t bits);
    _buffer buffer;
    uint8_t bufferOffset;
    _state state;
    uint8_t _digestBytes;
    uint32_t byteCount;
    uint8_t keyBuffer[BLOCK_LENGTH];
    uint8_t innerHash[HASH_LENGTH];
    
};

#endif
