modded class MissionGameplay
{
    protected ref TabletMenu m_TabletMenu;

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player)
            return;

       
        EntityAI item = player.GetHumanInventory().GetEntityInHands();
        GPS_Tablet_ColorBase tablet = GPS_Tablet_ColorBase.Cast(item);

        bool isWorking = tablet && tablet.GetCompEM() && tablet.GetCompEM().IsWorking();

        if (isWorking)
        {
            if (!m_TabletMenu)
            {
                m_TabletMenu = new TabletMenu();
                GetGame().GetUIManager().ShowScriptedMenu(m_TabletMenu, null);
            }
        }
        else
        {
            if (m_TabletMenu)
            {
                GetGame().GetUIManager().HideScriptedMenu(m_TabletMenu);
                m_TabletMenu = null;
            }
        }
    }
};
