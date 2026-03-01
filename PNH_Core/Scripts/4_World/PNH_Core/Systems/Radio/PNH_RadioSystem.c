/**
 * MOD: PNH_Core
 * FILE: PNH_RadioSystem.c
 * DESC: Distribui as músicas para todos os Tablets que estejam ligados na frequência certa.
 */

class PNH_RadioSystem
{
    static ref array<PNH_Tablet_ColorBase> m_ActiveRadios;
    static float m_LastBroadcastFrequency = -1;
    static string m_LastBroadcastSoundSet = "";
    static string m_LastBroadcastSongName = "";

    static void RegisterRadio(PNH_Tablet_ColorBase radio)
    {
        if (!m_ActiveRadios) m_ActiveRadios = new array<PNH_Tablet_ColorBase>();
        if (m_ActiveRadios.Find(radio) == -1) m_ActiveRadios.Insert(radio);
    }

    static void UnregisterRadio(PNH_Tablet_ColorBase radio)
    {
        if (m_ActiveRadios) m_ActiveRadios.RemoveItem(radio);
    }

    static void HandleIncomingBroadcast(float frequency, string soundSet, string songName)
    {
        if (!m_ActiveRadios || m_ActiveRadios.Count() == 0) return;

        m_LastBroadcastFrequency = frequency;
        m_LastBroadcastSoundSet = soundSet;
        m_LastBroadcastSongName = songName;

        foreach (PNH_Tablet_ColorBase radio : m_ActiveRadios)
        {
            if (!radio || !radio.IsFMReceiverListening()) continue;

            if (radio.GetTunedFrequency() == frequency && soundSet != "")
            {
                bool shouldPlay = false;
                if (radio.GetCurrentlyPlayingSoundSet() != soundSet) shouldPlay = true;

                if (shouldPlay)
                {
                    radio.PlayPublicRadioSound(soundSet);
                    radio.SetCurrentSongName(songName);
                }
            }
        }
    }
}