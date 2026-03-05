/**
 * MOD: PNH_Core
 * FILE: PNH_TabletOS.c
 */

class PNH_TabletOS extends UIScriptedMenu
{
    private Widget m_PanelHome, m_PanelMap, m_PanelRadio;
    private TextWidget m_RadioFreq, m_RadioInfo;
    private MapWidget m_MapWidget;
    private PNH_Tablet_Black m_TabletItem;

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("PNH_Core/GUI/Layouts/PNH_TabletOS.layout");
        
        m_PanelHome  = layoutRoot.FindAnyWidget("PanelHome");
        m_PanelMap   = layoutRoot.FindAnyWidget("PanelMap");
        m_PanelRadio = layoutRoot.FindAnyWidget("PanelRadio");
        
        m_RadioFreq  = TextWidget.Cast(layoutRoot.FindAnyWidget("RadioFreq"));
        m_RadioInfo  = TextWidget.Cast(layoutRoot.FindAnyWidget("RadioInfo"));
        m_MapWidget  = MapWidget.Cast(layoutRoot.FindAnyWidget("TabletMap"));
        
        return layoutRoot;
    }

    override void OnShow()
    {
        super.OnShow();
        GetGame().GetInput().ChangeGameFocus(1);
        GetGame().GetUIManager().ShowCursor(true);
        FindTablet();
        UpdateRadioDisplay();
        ShowApp("home");
    }

    override void OnHide()
    {
        super.OnHide();
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowCursor(false);
    }

    void FindTablet()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player)
        {
            EntityAI item = player.GetHumanInventory().GetEntityInHands();
            Class.CastTo(m_TabletItem, item);
        }
    }

    void ShowApp(string appName)
    {
        m_PanelHome.Show(false);
        m_PanelMap.Show(false);
        m_PanelRadio.Show(false);

        if (appName == "home")  m_PanelHome.Show(true);
        if (appName == "map")   m_PanelMap.Show(true);
        if (appName == "radio") m_PanelRadio.Show(true);
        
        GetGame().GetPlayer().PlaySound("Battery_Insert_SoundSet", 0, false);
    }

    void UpdateRadioDisplay()
    {
        if (m_TabletItem && m_RadioFreq && m_RadioInfo)
        {
            m_RadioFreq.SetText("FREQ: " + m_TabletItem.GetTunedFrequency().ToString() + " MHz");
            string song = m_TabletItem.GetCurrentSongName();
            if (song == "") song = "SINTONIZANDO...";
            m_RadioInfo.SetText("INFO: " + song);
        }
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        string name = w.GetName();

        if (name == "BtnF1") { ShowApp("home");  return true; }
        if (name == "BtnF2") { ShowApp("map");   return true; }
        if (name == "BtnF3") { ShowApp("radio"); return true; }
        if (name == "BtnPower") { Close(); return true; }
        
        if (name == "BtnF4") {
            PNH_RpcManager.Get().SendRPC(9992, new Param1<string>("[SOS]"));
            return true;
        }
        return super.OnClick(w, x, y, button);
    }
}