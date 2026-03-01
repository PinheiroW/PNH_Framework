class PassiveRadioSystem
{
	static ref array<skaerheim_radioreceiver_base> m_ActiveRadios;
	static float m_LastBroadcastFrequency = -1;
	static string m_LastBroadcastSoundSet = "";
	static string m_LastBroadcastSongName = "";

	static void RegisterRadio(skaerheim_radioreceiver_base radio)
	{
		if (!m_ActiveRadios)
			m_ActiveRadios = new array<skaerheim_radioreceiver_base>();

		if (m_ActiveRadios.Find(radio) == -1)
			m_ActiveRadios.Insert(radio);
	}

	static void UnregisterRadio(skaerheim_radioreceiver_base radio)
	{
		if (m_ActiveRadios)
			m_ActiveRadios.RemoveItem(radio);
	}

	static void HandleIncomingBroadcast(float frequency, string soundSet, string songName)
	{
		if (!m_ActiveRadios || m_ActiveRadios.Count() == 0)
			return;

		m_LastBroadcastFrequency = frequency;
		m_LastBroadcastSoundSet = soundSet;
		m_LastBroadcastSongName = songName;

		foreach (skaerheim_radioreceiver_base radio : m_ActiveRadios)
		{
			if (!radio || !radio.IsFMReceiverListening())
				continue;

			// Only apply updates if frequencies match and something is being broadcasted
			if (radio.GetTunedFrequency() == frequency && soundSet != "")
			{
				bool shouldPlay = false;

				// Check if a new song should be played
				if (radio.GetCurrentlyPlayingSoundSet() != soundSet)
				{
					shouldPlay = true;
				}

				if (shouldPlay)
				{
					radio.PlayPublicRadioSound(soundSet);
					radio.SetCurrentSongName(songName);
				}
			}
		}
	}
}
