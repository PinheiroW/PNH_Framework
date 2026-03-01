modded class MissionServer
{
    ref PassiveRadioStationManager m_RadioStationManager;

    override void OnInit()
    {
        super.OnInit();

        m_RadioStationManager = new PassiveRadioStationManager();
        Print("[PublicRadio] Radio Station Manager initialized.");
    }

    PassiveRadioStationManager GetRadioStationManager()
    {
        return m_RadioStationManager;
    }
}