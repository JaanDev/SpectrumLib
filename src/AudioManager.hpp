#pragma once
#include <vector>
#include <string>
#include <array>
#include "utils.hpp"

NS_SPECTRUM_BEGIN

struct Sample {
    const char* sampleKey;
    uint8_t volume;
    uint8_t balance;
    uint32_t freq;
    uint32_t position;
    uint32_t length;
    uint32_t repeats;
};

struct Channel {
    const char* sampleKey;
    uint8_t volume;
    uint8_t balance;
    uint32_t freq;
    uint32_t position;
    uint32_t length;
    uint32_t repeats;
};

class SPL_API AudioManager {
  public:
    static AudioManager* get();

    void playSample(const std::string& sample, uint32_t repeats);
    void playSample(const std::string& sample, uint8_t channel, uint32_t repeats);
    void playSampleFile(const std::string& samplePath, uint8_t channel, uint32_t repeats);

    void preloadSampleFile(const std::string& samplePath);
    void unloadSampleFile(const std::string& sample);

    void pauseSample(const std::string& sample);
    void pauseChannel(uint8_t channel);
    void pauseAllChannels();

    void resumeSample(const std::string& sample);
    void resumeChannel(uint8_t channel);
    void resumeAllChannels();

    void stopSample(const std::string& sample);
    void stopChannel(uint8_t channel);
    void stopAllChannels();

    void setGeneralVolume(float volume);
    void setSampleVolume(const std::string& sample, float volume);
    void setChannelVolume(uint8_t channel, float volume);

    float getGeneralVolume();
    float getSampleVolume(const std::string& sample);
    float getChannelVolume(uint8_t channel);

    void setGeneralBalance(float balance);
    void setSampleBalance(const std::string& sample, float balance);
    void setChannelBalance(uint8_t channel, float balance);

    float getGeneralBalance();
    float getSampleBalance(const std::string& sample);
    float getChannelBalance(uint8_t channel);

    void setSamplePosition(const std::string& sample, float seconds);
    void setChannelPosition(uint8_t channel, float seconds);

    float getSamplePosition(const std::string& sample);
    float getChannelPosition(uint8_t channel);

    float getSampleLength(const std::string& sample);
    float getChannelLength(uint8_t channel);

    void setSampleFrequency(const std::string& sample, uint32_t freq);
    void setChannelFrequency(uint8_t channel, uint32_t freq);

    float getSampleFrequency(const std::string& sample);
    float getChannelFrequency(uint8_t channel);

    void lockChannel(uint8_t channel);
    void unlockChannel(uint8_t channel);

  private:
    std::array<Channel, 48> m_channels;
    std::vector<Sample> m_loadedSamples;
    float m_generalVolume;
    float m_generalBalance;
};

NS_SPECTRUM_END