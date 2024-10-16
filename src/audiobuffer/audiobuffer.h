#ifndef _AUDIOBUFFER_H
#define _AUDIOBUFFER_H

#include <stdio.h>
#include <chrono>
#include "soloud.h"
#include "buffer.h"

struct stb_vorbis;
#ifndef dr_flac_h
struct drflac;
#endif
#ifndef dr_mp3_h
struct drmp3;
#endif
#ifndef dr_wav_h
struct drwav;
#endif

namespace SoLoud
{
  class BufferStream;
  class File;

  class BufferStreamInstance : public AudioSourceInstance
  {
    BufferStream *mParent;
    unsigned int mOffset;
    File *mFile;
    union codec
    {
      stb_vorbis *mOgg;
      drflac *mFlac;
      drmp3 *mMp3;
      drwav *mWav;
    } mCodec;
    unsigned int mOggFrameSize;
    unsigned int mOggFrameOffset;
    float **mOggOutputs;

  public:
    BufferStreamInstance(BufferStream *aParent);
    virtual unsigned int getAudio(float *aBuffer, unsigned int aSamplesToRead, unsigned int aBufferSize);
    virtual result seek(double aSeconds, float *mScratch, unsigned int mScratchSize);
    virtual result rewind();
    virtual bool hasEnded();
    virtual ~BufferStreamInstance();
  };

  enum BUFFERSTREAM_FILETYPE
  {
    BUFFERSTREAM_WAV = 0,
    BUFFERSTREAM_OGG = 1,
    BUFFERSTREAM_FLAC = 2,
    BUFFERSTREAM_MP3 = 3,
    BUFFERSTREAM_PCM = 4
  };

  enum PCM_TYPE
  {
    PCM_FLOAT32 = 0,
    PCM_S8 = 1,
    PCM_S16LE = 2,
    PCM_S32LE = 3,
  };

  struct PCMformat
  {
    int sampleRate;
    int channels;
    int bytesPerSample;
    PCM_TYPE dataType;
  };

  class BufferStream : public AudioSource
  {
    result loadwav(File *fp);
    result loadogg(File *fp);
    result loadflac(File *fp);
    result loadmp3(File *fp);
    result loadpcm(File *fp, const PCMformat pcmFormat);

  public:
    int mFiletype;
    File *mMemFile;
    File *mStreamFile;
    unsigned int mSampleCount;
    PCMformat mPCMformat;
    Buffer mBuffer;

    BufferStream();
    virtual ~BufferStream();
    result loadMem(
        const unsigned char *aData,
        unsigned int aDataLen,
        bool aCopy = false,
        bool aTakeOwnership = true,
        PCMformat format = {44100, 2, 4, PCM_FLOAT32});
    void addData(const void *data, unsigned int numSamples);
    virtual AudioSourceInstance *createInstance();
    time getLength();

  public:
    result parse(File *aFile);
  };
};

#endif // _AUDIOBUFFER_H