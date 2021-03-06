// license:BSD-3-Clause
// copyright-holders:Takahiro Nogi, David Haywood
#ifndef MAME_AUDIO_GOMOKU_H
#define MAME_AUDIO_GOMOKU_H

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> gomoku_sound_device

class gomoku_sound_device : public device_t,
							public device_sound_interface
{
public:
	gomoku_sound_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock = 48'000);

	void sound1_w(offs_t offset, uint8_t data);
	void sound2_w(offs_t offset, uint8_t data);

protected:
	// device-level overrides
	virtual void device_start() override;

	// sound stream update overrides
	virtual void sound_stream_update_legacy(sound_stream &stream, stream_sample_t const * const *inputs, stream_sample_t * const *outputs, int samples) override;

private:
	void make_mixer_table(int voices, int gain);

	// 4 voices max
	static constexpr unsigned MAX_VOICES = 4;

	struct sound_channel
	{
		sound_channel() { }

		int channel = 0;
		int frequency = 0;
		int counter = 0;
		int volume = 0;
		int oneshotplaying = 0;
	};


	// data about the sound system
	sound_channel m_channel_list[MAX_VOICES];

	// global sound parameters
	required_region_ptr<uint8_t> m_sound_rom;
	bool m_sound_enable;
	sound_stream *m_stream;

	// mixer tables and internal buffers
	std::unique_ptr<int16_t[]> m_mixer_table;
	int16_t *m_mixer_lookup;
	std::unique_ptr<short[]> m_mixer_buffer;
	short *m_mixer_buffer_2;

	uint8_t m_soundregs1[0x20];
	uint8_t m_soundregs2[0x20];
};

DECLARE_DEVICE_TYPE(GOMOKU_SOUND, gomoku_sound_device)

#endif // MAME_AUDIO_GOMOKU_H
