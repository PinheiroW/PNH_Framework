/**
 * MOD: PNH_Core
 * FILE: PNH_RadioClasses.c
 * DESC: Estrutura de dados para as estações e músicas do rádio.
 */

class RadioSong
{
    string SoundSet;
    int Length;       // Duração em segundos
    string SongName;  // Nome da música que vai aparecer no visor do tablet
}

class RadioStation
{
    float Frequency;
    ref array<ref RadioSong> Playlist;
    int m_CurrentIndex;

    ref RadioSong m_CurrentSong;
    float m_CurrentSongTimeRemaining;

    void RadioStation()
    {
        Playlist = new array<ref RadioSong>();
        m_CurrentIndex = 0;
        m_CurrentSong = null;
        m_CurrentSongTimeRemaining = 0;
    }

    void Tick(float deltaTime)
    {
        if (!m_CurrentSong && Playlist.Count() > 0)
        {
            GetNextSong();
            return;
        }

        m_CurrentSongTimeRemaining -= deltaTime;
        if (m_CurrentSongTimeRemaining <= 0 && Playlist.Count() > 0)
        {
            GetNextSong();
        }
    }

    RadioSong GetNextSong()
    {
        if (Playlist.Count() == 0)
            return null;

        m_CurrentSong = Playlist.Get(m_CurrentIndex);
        m_CurrentSongTimeRemaining = m_CurrentSong.Length;
        m_CurrentIndex = (m_CurrentIndex + 1) % Playlist.Count();
        return m_CurrentSong;
    }

    RadioSong GetCurrentSong()
    {
        return m_CurrentSong;
    }
}