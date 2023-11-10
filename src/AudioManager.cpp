#include "AudioManager.hpp"

#include <memory>

NS_SPECTRUM_BEGIN

AudioManager* AudioManager::instance() {
    static auto instance = std::make_unique<AudioManager>();
    return instance.get();
}

void AudioManager::playSample(const std::string& sample, uint32_t repeats) {}

void AudioManager::playSample(const std::string& sample, uint8_t channel, uint32_t repeats) {}

void AudioManager::playSampleFile(const std::string& samplePath, uint8_t channel, uint32_t repeats) {}

void AudioManager::preloadSampleFile(const std::string& samplePath) {}

void AudioManager::unloadSampleFile(const std::string& sample) {}

void AudioManager::pauseSample(const std::string& sample) {}

void AudioManager::pauseChannel(uint8_t channel) {}

void AudioManager::pauseAllChannels() {}

void AudioManager::resumeSample(const std::string& sample) {}

void AudioManager::resumeChannel(uint8_t channel) {}

void AudioManager::resumeAllChannels() {}

void AudioManager::stopSample(const std::string& sample) {}

void AudioManager::stopChannel(uint8_t channel) {}

void AudioManager::stopAllChannels() {}

void AudioManager::setGeneralVolume(float volume) {}

void AudioManager::setSampleVolume(const std::string& sample, float volume) {}

void AudioManager::setChannelVolume(uint8_t channel, float volume) {}

float AudioManager::getGeneralVolume() {
    return 0.0f;
}

float AudioManager::getSampleVolume(const std::string& sample) {
    return 0.0f;
}

float AudioManager::getChannelVolume(uint8_t channel) {
    return 0.0f;
}

void AudioManager::setGeneralBalance(float balance) {}

void AudioManager::setSampleBalance(const std::string& sample, float balance) {}

void AudioManager::setChannelBalance(uint8_t channel, float balance) {}

float AudioManager::getGeneralBalance() {
    return 0.0f;
}

float AudioManager::getSampleBalance(const std::string& sample) {
    return 0.0f;
}

float AudioManager::getChannelBalance(uint8_t channel) {
    return 0.0f;
}

void AudioManager::setSamplePosition(const std::string& sample, float seconds) {}

void AudioManager::setChannelPosition(uint8_t channel, float seconds) {}

float AudioManager::getSamplePosition(const std::string& sample) {
    return 0.0f;
}

float AudioManager::getChannelPosition(uint8_t channel) {
    return 0.0f;
}

float AudioManager::getSampleLength(const std::string& sample) {
    return 0.0f;
}

float AudioManager::getChannelLength(uint8_t channel) {
    return 0.0f;
}

void AudioManager::setSampleFrequency(const std::string& sample, uint32_t freq) {}

void AudioManager::setChannelFrequency(uint8_t channel, uint32_t freq) {}

float AudioManager::getSampleFrequency(const std::string& sample) {
    return 0.0f;
}

float AudioManager::getChannelFrequency(uint8_t channel) {
    return 0.0f;
}

void AudioManager::lockChannel(uint8_t channel) {}

void AudioManager::unlockChannel(uint8_t channel) {}

NS_SPECTRUM_END
