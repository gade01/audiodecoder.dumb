/*
 *  Copyright (C) 2014-2022 Arne Morten Kvarving
 *  Copyright (C) 2016-2022 Team Kodi (https://kodi.tv)
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <kodi/addon-instance/AudioDecoder.h>

extern "C"
{
#include <dumb.h>
} /* extern "C" */

class ATTR_DLL_LOCAL CDumbCodec : public kodi::addon::CInstanceAudioDecoder
{
public:
  CDumbCodec(const kodi::addon::IInstanceInfo& instance);
  virtual ~CDumbCodec();

  bool Init(const std::string& filename,
            unsigned int filecache,
            int& channels,
            int& samplerate,
            int& bitspersample,
            int64_t& totaltime,
            int& bitrate,
            AudioEngineDataFormat& format,
            std::vector<AudioEngineChannel>& channellist) override;
  int ReadPCM(uint8_t* buffer, size_t size, size_t& actualsize) override;
  int64_t Seek(int64_t time) override;

private:
  DUH* m_module = nullptr;
  DUH_SIGRENDERER* m_renderer = nullptr;

  sample_t** m_sigSamples = nullptr;
  long m_sigSamplesSize = 0;

  int m_samplerate = 48000;
  int64_t m_position; // Samples read
  int64_t m_totaltime; // Total samples available
};
