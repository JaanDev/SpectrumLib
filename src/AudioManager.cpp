#define MINIAUDIO_IMPLEMENTATION

#include "AudioManager.hpp"
#include "logger.hpp"
#include "FileManager.hpp"

#include <memory>
#include <filesystem>
#include <fstream>
#include <algorithm>

NS_SPECTRUM_BEGIN

AudioManager* AudioManager::get() {
    static auto instance = AudioManager();
    return &instance;
}

AudioManager::AudioManager() {
    m_deviceConfig = ma_device_config_init(ma_device_type_playback);
    m_deviceConfig.playback.format = ma_format_f32;
    m_deviceConfig.playback.channels = 2;
    m_deviceConfig.sampleRate = 44100;
    m_deviceConfig.dataCallback = &data_callback;

    m_decoderConfig = ma_decoder_config_init(ma_format_f32, 2, 44100);

    ma_result result;

    result = ma_device_init(NULL, &m_deviceConfig, &m_device);
    if (result != MA_SUCCESS) {
        logE("Failed to init audio device config: {}", ma_result_description(result));
        return;
    }

    result = ma_device_start(&m_device);
    if (result != MA_SUCCESS) {
        logE("Failed to start audio device: {}", ma_result_description(result));
        return;
    }

    m_device.pUserData = this;

    logD("Successfully initialized audio device {}", m_device.playback.name);
    logD("Device format: {}", ma_get_format_name(m_deviceConfig.playback.format));
    logD("Device channels: {}", m_deviceConfig.playback.channels);
    logD("Device rate: {}", m_deviceConfig.sampleRate);
}

AudioManager::~AudioManager() {
    ma_device_uninit(&m_device);
}

void AudioManager::data_callback(ma_device* pDevice, void* pOutput, const void* pInput, uint32_t frameCount) {
    auto self = (AudioManager*)pDevice->pUserData;

    for (auto& sample : self->m_loadedSamples) {
        if (!sample.second.paused) {
            self->setGeneralVolume(sample.second.volume * self->getGeneralVolume());

            ma_uint64 frameRemain;
            ma_decoder_read_pcm_frames(&sample.second.decoder, pOutput, frameCount, &frameRemain);
            if (frameCount < frameRemain && (sample.second.repeats == 0 || sample.second.alreadyRepeaten < sample.second.repeats)) {
                ma_decoder_seek_to_pcm_frame(&sample.second.decoder, 0);
                sample.second.alreadyRepeaten++;
            }
        }
    }
}

void AudioManager::playSample(const std::string& sample, uint32_t repeats) {
    if (m_loadedSamples.find(sample) == m_loadedSamples.end()) {
        logE("Sample {} does not exists", sample);
        return;
    }

    ma_result result;
    result =
        ma_decoder_init_memory((void*)m_loadedSamples[sample].data, m_loadedSamples[sample].size, &m_decoderConfig, &m_loadedSamples[sample].decoder);

    if (result != MA_SUCCESS) {
        logE("Failed to init sample file: {}", ma_result_description(result));
        return;
    }

    logD("Loaded sample {}", sample);
    logD("Sample format: {}", ma_get_format_name(m_loadedSamples[sample].decoder.outputFormat));
    logD("Sample channels: {}", m_loadedSamples[sample].decoder.outputChannels);
    logD("Sample rate: {}", m_loadedSamples[sample].decoder.outputSampleRate);
}

void AudioManager::playSample(const std::string& sample, uint8_t channel, uint32_t repeats) {
    if (m_loadedSamples.find(sample) == m_loadedSamples.end()) {
        logE("Sample {} does not exists", sample);
        return;
    }

    ma_result result;
    result = ma_decoder_init_memory(m_loadedSamples[sample].data, m_loadedSamples[sample].size, NULL, &m_channels[channel].decoder);

    if (result != MA_SUCCESS) {
        logE("Failed to init sample file: {}", ma_result_description(result));
        return;
    }

    m_channels[channel].sampleKey = sample.c_str();

    logD("Loaded sample {}", sample);
    logD("Sample format: {}", ma_get_format_name(m_channels[channel].decoder.outputFormat));
    logD("Sample channels: {}", m_channels[channel].decoder.outputChannels);
    logD("Sample rate: {}", m_channels[channel].decoder.outputSampleRate);
}

void AudioManager::playSampleFile(const std::string& samplePath, uint8_t channel, uint32_t repeats) {
    ma_result result;
    result = ma_decoder_init_file(samplePath.c_str(), NULL, &m_channels[channel].decoder);

    if (result != MA_SUCCESS) {
        logE("Failed to init sample file: {}", ma_result_description(result));
        return;
    }

    m_channels[channel].sampleKey = std::filesystem::path(samplePath).filename().string().c_str();

    logD("Loaded sample {}", samplePath);
    logD("Sample format: {}", ma_get_format_name(m_channels[channel].decoder.outputFormat));
    logD("Sample channels: {}", m_channels[channel].decoder.outputChannels);
    logD("Sample rate: {}", m_channels[channel].decoder.outputSampleRate);
}

void AudioManager::preloadSampleFile(const std::string& samplePath) {
    auto fullPath = FileManager::get()->fullPathForFile(samplePath);
    auto filename = fullPath.filename().string();

    std::fstream infile(fullPath, std::ios::in | std::ios::binary);
    if (!infile) {
        logE("Failed to open file {}", fullPath.string());
        return;
    }

    infile.seekg(0, infile.end);
    size_t length = infile.tellg();
    infile.seekg(0, infile.beg);

    if (length > 0) {
        m_loadedSamples.insert(std::make_pair(filename, Sample {.size = length, .data = new unsigned char[length]}));

        infile.read((char*)m_loadedSamples[filename].data, length);
        // infile.write((char*)m_loadedSamples[filename].data, length);
    }

    infile.close();
}

void AudioManager::unloadSampleFile(const std::string& sample) {
    m_loadedSamples.erase(sample);
}

void AudioManager::pauseSample(const std::string& sample) {
    m_loadedSamples[sample].paused = true;
}

void AudioManager::pauseChannel(uint8_t channel) {
    m_channels[channel].paused = true;
}

void AudioManager::pauseAllChannels() {
    for (auto& channel : m_channels) {
        channel.paused = true;
    }
}

void AudioManager::resumeSample(const std::string& sample) {
    m_loadedSamples[sample].paused = false;
}

void AudioManager::resumeChannel(uint8_t channel) {
    m_channels[channel].paused = false;
}

void AudioManager::resumeAllChannels() {
    for (auto& channel : m_channels) {
        channel.paused = false;
    }
}

void AudioManager::stopSample(const std::string& sample) {
    ma_decoder_uninit(&m_loadedSamples[sample].decoder);
}

void AudioManager::stopChannel(uint8_t channel) {
    ma_decoder_uninit(&m_channels[channel].decoder);
}

void AudioManager::stopAllChannels() {
    for (auto& channel : m_channels) {
        ma_decoder_uninit(&channel.decoder);
    }
}

void AudioManager::setGeneralVolume(float volume) {
    ma_device_set_master_volume(&m_device, volume);
}

void AudioManager::setSampleVolume(const std::string& sample, float volume) {
    m_loadedSamples[sample].volume = std::clamp(volume, 0.0f, 1.0f);
}

void AudioManager::setChannelVolume(uint8_t channel, float volume) {
    if (!m_channels[channel].locked) {
        m_channels[channel].volume = std::clamp(volume, 0.0f, 1.0f);
    }
}

float AudioManager::getGeneralVolume() {
    float ret;
    ma_device_get_master_volume(&m_device, &ret);
    return ret;
}

float AudioManager::getSampleVolume(const std::string& sample) {
    return m_loadedSamples[sample].volume;
}

float AudioManager::getChannelVolume(uint8_t channel) {
    return m_channels[channel].volume;
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

void AudioManager::setSamplePosition(const std::string& sample, float seconds) {
    ma_decoder_seek_to_pcm_frame(&m_loadedSamples[sample].decoder, (uint64_t)(seconds * m_loadedSamples[sample].decoder.outputSampleRate / 1000));
}

void AudioManager::setChannelPosition(uint8_t channel, float seconds) {
    if (!m_channels[channel].locked) {
        ma_decoder_seek_to_pcm_frame(&m_channels[channel].decoder, (uint64_t)(seconds * m_channels[channel].decoder.outputSampleRate / 1000));
    }
}

float AudioManager::getSamplePosition(const std::string& sample) {
    ma_uint64 cursor;
    ma_decoder_get_cursor_in_pcm_frames(&m_loadedSamples[sample].decoder, &cursor);

    return (float)cursor * 1000 / m_loadedSamples[sample].decoder.outputSampleRate;
}

float AudioManager::getChannelPosition(uint8_t channel) {
    ma_uint64 cursor;
    ma_decoder_get_cursor_in_pcm_frames(&m_channels[channel].decoder, &cursor);

    return (float)cursor * 1000 / m_channels[channel].decoder.outputSampleRate;
}

float AudioManager::getSampleLength(const std::string& sample) {
    ma_uint64 length;
    ma_decoder_get_length_in_pcm_frames(&m_loadedSamples[sample].decoder, &length);
    return (float)length * 1000 / m_loadedSamples[sample].decoder.outputSampleRate;
}

float AudioManager::getChannelLength(uint8_t channel) {
    ma_uint64 length;
    ma_decoder_get_length_in_pcm_frames(&m_channels[channel].decoder, &length);
    return (float)length * 1000 / m_channels[channel].decoder.outputSampleRate;
}

void AudioManager::setSampleFrequency(const std::string& sample, uint32_t freq) {}

void AudioManager::setChannelFrequency(uint8_t channel, uint32_t freq) {}

float AudioManager::getSampleFrequency(const std::string& sample) {
    return 0.0f;
}

float AudioManager::getChannelFrequency(uint8_t channel) {
    return 0.0f;
}

void AudioManager::lockChannel(uint8_t channel) {
    m_channels[channel].locked = true;
}

void AudioManager::unlockChannel(uint8_t channel) {
    m_channels[channel].locked = false;
}

NS_SPECTRUM_END
