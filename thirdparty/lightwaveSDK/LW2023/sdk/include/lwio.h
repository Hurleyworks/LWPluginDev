/*
 * LWSDK Header File
 *
 * LWIO.H -- LightWave Save and Load State
 *
 * This header contains the definition of the structures needed to
 * perform I/O from a LightWave server.
 *
 *Copyright © 2024 LightWave Digital, Ltd. and its licensors. All rights reserved.
 *
 *This file contains confidential and proprietary information of LightWave Digital, Ltd.,
 *and is subject to the terms of the LightWave End User License Agreement (EULA).
 */
#ifndef LWSDK_IO_H
#define LWSDK_IO_H

#include <lwtypes.h>

/*
 * Data may be loaded and saved in binary or text files.  Text files
 * are often scene files, and binary files are often object files.
 *
 * In BINARY mode, the external form contains raw bytes having any
 * value from 0 to 255.  Reads and writes are entirely based on the
 * number of bytes requested.
 *
 * In ASCII mode, all data bytes must be in the extended ASCII range
 * of 32 to 255.  Values outside this range are ignored or undefined.
 */
#define LWIO_BINARY  0
#define LWIO_ASCII   1
#define LWIO_OBJECT  LWIO_BINARY
#define LWIO_SCENE   LWIO_ASCII


/*
 * Blocks of data can be marked with identifiers.  In BINARY mode the
 * four-byte ID code is used, and in ASCII mode the string token (which
 * should not contain spaces) is used.
 */
typedef struct st_LWBlockIdent {
    LWID         id;
    LWCStringASCII token;
} LWBlockIdent;


/*
 * This structure is used when the server is writing its state to
 * the external store.  The 'writeData' is the first argument to all
 * the callback functions.
 *
 * write    execute a raw write to the store.  In BINARY mode, the
 *      number of bytes indicated by 'len' is written directly to
 *      the output.  In ASCII mode the input buffer is treated as
 *      a null-terminated string and the length is computed from
 *      that.  The string is written with a newline at the end.
 *
 * writeI1  write an array of different sized and typed integers to
 * writeI2  the store.  In BINARY mode the 'n' numbers are written as
 * writeI4  1, 2 or 4 btype elements in "big-endian" (Motorola)
 * writeU1  format.  In ASCII mode, all 'n' numbers are written to a
 * writeU2  single line, the signed values in decimal and the unsigned
 * writeU4  values in hexadecimal.  A newline is written after the
 *      list of numbers unless the writing is done inside a leaf
 *      block.
 *
 * writeStr write a null-terminated string to the store.  In ASCII
 *      mode the string may be contained in double quotes.
 *
 * writeID  write an identifier token to the store.  In BINARY mode
 *      this is the four-byte ID code, while in ASCII mode this
 *      is the string token.
 *
 * beginBlk start a nested data block.  The block is identified by
 *      the ID codes defined in the LWBlockIdent, and the 'leaf'
 *      flag is true if this block will not contain other blocks.
 *
 * endBlk   end the current data block.
 *
 * depth    return the current block nesting level, where zero means
 *      we've entered no blocks.
 */


typedef struct st_LWSaveState {
    int           ioMode;
    void         *writeData;
    void        (*write)    (void *state, const char  *data, int length);

    void        (*writeI1)  (void *state, const char  *data, int n);
    void        (*writeI2)  (void *state, const short *data, int n);
    void        (*writeI4)  (void *state, const int   *data, int n);
    void        (*writeU1)  (void *state, const unsigned char  *data, int n);
    void        (*writeU2)  (void *state, const unsigned short *data, int n);
    void        (*writeU4)  (void *state, const unsigned int   *data, int n);
    void        (*writeFP)  (void *state, const float *data, int n);
    void        (*writeStr) (void *state, const char  *data /* client encoded */);
    void        (*writeID)  (void *state, const LWBlockIdent *);

    void        (*beginBlk) (void *state, const LWBlockIdent *, int leaf);
    void        (*endBlk)   (void *state);
    int         (*depth)    (void *state);
    void        (*writeDP)  (void *state, const double *data, int n);
} LWSaveState;


/*
 * This structure is used when the server is reading its state from
 * the external store.  The 'readData' is the first argument to all
 * the callback functions.
 *
 * read     execute a raw read of the store.  In binary mode, 'len'
 *      bytes are read directly from the store.  In ASCII mode, up
 *      to 'len' bytes of the current line are read from the
 *      store, perhaps leaving more bytes to be read later.  The
 *      return value is the number of bytes read on the current
 *      line (which may be zero), or -1 for end of data.
 *
 * readI1   read an array of integers of various types and formats,
 * readI2   returning the number of integers successfully read.  In
 * readI4   BINARY mode a sequence of 'n' single, double or quad bytes
 * readU1   are read from the stream and interpreted as "big-endian"
 * readU2   (Motorola) format words.  In ASCII mode, the numbers are
 * readU4   read from the current line, in decimal for signed values
 *      and in hexadecimal for unsigned values.
 *
 * readFP   read an array of floating point numbers from the store.
 *      The return value is the number of values read.
 *
 * readStr  read a string from the store.  In ASCII mode double quotes
 *      will be removed.
 *
 * readID   read an identifier token from the store.  In BINARY this is
 *      just a four-byte code value, but in ASCII this in the string
 *      token which will be matched with its longword code.
 *
 * findBlk  read ahead looking for the next block.  The array of block
 *      identifiers includes all the blocks that could be expected
 *      and is terminated with a null ID code.  If a reconginized
 *      block is found in the file, it's ID code is returned.  A
 *      zero return indicates no more valid blocks.
 *
 * endBlk   complete reading the current open block.
 *
 * depth    return the current block nesting level, where zero means
 *      we've entered no blocks.
 */


typedef struct st_LWLoadState {
    int       ioMode;
    void     *readData;
    int     (*read)    (void *state, char  *data, int length);

    int     (*readI1)  (void *state, char  *data, int n);
    int     (*readI2)  (void *state, short *data, int n);
    int     (*readI4)  (void *state, int  *data, int n);
    int     (*readU1)  (void *state, unsigned char  *data, int n);
    int     (*readU2)  (void *state, unsigned short *data, int n);
    int     (*readU4)  (void *state, unsigned int   *data, int n);
    int     (*readFP)  (void *state, float *data, int n);
    int     (*readStr) (void *state, char  *data /* client encoded */, int max);
    LWID    (*readID)  (void *state, const LWBlockIdent *);

    LWID    (*findBlk) (void *state, const LWBlockIdent *);
    void    (*endBlk)  (void *state);
    int     (*depth)   (void *state);
    int     (*readDP)  (void *state, double *data, int n);
} LWLoadState;


/*
 * Macros make the call format easier to write.
 */
#define LWSAVE_I1(lwss,p,n) (*(lwss)->writeI1)((lwss)->writeData,p,n)
#define LWSAVE_I2(lwss,p,n) (*(lwss)->writeI2)((lwss)->writeData,p,n)
#define LWSAVE_I4(lwss,p,n) (*(lwss)->writeI4)((lwss)->writeData,p,n)
#define LWSAVE_U1(lwss,p,n) (*(lwss)->writeU1)((lwss)->writeData,p,n)
#define LWSAVE_U2(lwss,p,n) (*(lwss)->writeU2)((lwss)->writeData,p,n)
#define LWSAVE_U4(lwss,p,n) (*(lwss)->writeU4)((lwss)->writeData,p,n)
#define LWSAVE_FP(lwss,p,n) (*(lwss)->writeFP)((lwss)->writeData,p,n)
#define LWSAVE_STR(lwss,p)  (*(lwss)->writeStr)((lwss)->writeData,p)
#define LWSAVE_ID(lwss,b)   (*(lwss)->writeID)((lwss)->writeData,b)
#define LWSAVE_BEGIN(lwss,b,l)  (*(lwss)->beginBlk)((lwss)->writeData,b,l)
#define LWSAVE_END(lwss)    (*(lwss)->endBlk)((lwss)->writeData)
#define LWSAVE_DEPTH(lwss)  (*(lwss)->depth)((lwss)->writeData)
#define LWSAVE_DP(lwss,p,n) (*(lwss)->writeDP)((lwss)->writeData,p,n)

#define LWLOAD_I1(lwls,p,n) (*(lwls)->readI1)((lwls)->readData,p,n)
#define LWLOAD_I2(lwls,p,n) (*(lwls)->readI2)((lwls)->readData,p,n)
#define LWLOAD_I4(lwls,p,n) (*(lwls)->readI4)((lwls)->readData,p,n)
#define LWLOAD_U1(lwls,p,n) (*(lwls)->readU1)((lwls)->readData,p,n)
#define LWLOAD_U2(lwls,p,n) (*(lwls)->readU2)((lwls)->readData,p,n)
#define LWLOAD_U4(lwls,p,n) (*(lwls)->readU4)((lwls)->readData,p,n)
#define LWLOAD_FP(lwls,p,n) (*(lwls)->readFP)((lwls)->readData,p,n)
#define LWLOAD_STR(lwls,p,n)    (*(lwls)->readStr)((lwls)->readData,p,n)
#define LWLOAD_ID(lwls,b)   (*(lwls)->readID)((lwls)->readData,b)
#define LWLOAD_FIND(lwls,b) (*(lwls)->findBlk)((lwls)->readData,b)
#define LWLOAD_END(lwls)    (*(lwls)->endBlk)((lwls)->readData)
#define LWLOAD_DEPTH(lwls)  (*(lwls)->depth)((lwls)->readData)
#define LWLOAD_DP(lwls,p,n) (*(lwls)->readDP)((lwls)->readData,p,n)


#define LWFILEIOFUNCS_GLOBAL    "File IO 5"

#define LWIO_BINARY_IFF             0x8C0000
#define LWIO_BINARY_IFF32           0x8D0000
#define LWIO_BINARY_IFF32_STRICT    0x8E0000
#define LWIO_BINARY_IFF64           0x8F0000

typedef struct st_LWFileIOFuncs {
    LWSaveState *       (*openSave) (LWCStringUTF8 filename, int ioMode);
    void                (*closeSave)(LWSaveState *save);
    LWLoadState *       (*openLoad) (LWCStringUTF8 filename, int ioMode);
    void                (*closeLoad)(LWLoadState *load);
} LWFileIOFuncs;

#endif
