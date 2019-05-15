//
// Created by FLXR on 2/12/2019.
//

#include <xe/core/vfs.hpp>
#include <xe/utils/logger.hpp>
#include <xe/loaders/audioloader.hpp>

namespace xe {

  struct WavHeader {
    int8 riff[4];//'RIFF'
    uint riffSize;
    int8 wave[4];//'WAVE'
    int8 fmt[4];//'fmt '
    uint fmtSize;
    uint16 format;
    uint16 channels;
    uint samplesPerSec;
    uint bytesPerSec;
    uint16 blockAlign;
    uint16 bitsPerSample;
    int8 data[4];//'data'
    uint dataSize;
  };

  byte *AudioLoader::load(const string &file, Sound *sound) {
    return load(file.c_str(), sound);
  }

  byte *AudioLoader::load(const char *file, Sound *sound) {
    string path(basePath);
    path += file;

    int64 memorySize;
    byte *memory = VFS::readFile(path, &memorySize);

    if (!memory) {
      XE_CORE_ERROR("[AudioLoader]: unable to load audio: '", path, "'");
      return nullptr;
    }

    byte *data = nullptr;

    string ext = getFileExt(file);
    if (ext == "wav") {
      data = loadWav(memory, sound);
    } else {
      XE_CORE_ERROR("[AudioLoader]: unsupported audio format: '", ext, "'");
    }

    delete[] memory;

    return data;
  }

  byte *AudioLoader::loadWav(const byte *memory, Sound *sound) {
    WavHeader header;
    memcpy(&header, memory, sizeof(WavHeader));

    sound->size = header.dataSize;
    sound->freq = header.samplesPerSec;
    sound->channels = header.channels;
    sound->bps = header.bitsPerSample;

    if (header.bitsPerSample == 8) {
      sound->format = header.channels == 1 ? Sound::Format::Mono8 : Sound::Format::Stereo8;
    } else if (header.bitsPerSample == 16) {
      sound->format = header.channels == 1 ? Sound::Format::Mono16 : Sound::Format::Stereo16;
    } else {
      XE_CORE_ERROR("[AudioLoader]: unsupported audio format (bps): ", header.bitsPerSample);
      sound->format = Sound::Format::Invalid;
    }

    byte *data = new byte[header.dataSize];
    memcpy(data, memory + sizeof(WavHeader), header.dataSize);
    return data;
  }

}
