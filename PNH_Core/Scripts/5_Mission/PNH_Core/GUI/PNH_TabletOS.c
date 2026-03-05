class PNH_TabletOS extends UIScriptedMenu
{
    private PanelWidget m_PanelHome, m_PanelMap, m_PanelRadio;
    private MapWidget m_MapWidget;

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("PNH_Core/GUI/Layouts/PNH_TabletOS.layout");
        
        m_PanelHome  = PanelWidget.Cast(layoutRoot.FindAnyWidget("PanelHome"));
        m_PanelMap   = PanelWidget.Cast(layoutRoot.FindAnyWidget("PanelMap"));
        m_PanelRadio = PanelWidget.Cast(layoutRoot.FindAnyWidget("PanelRadio"));
        m_MapWidget  = MapWidget.Cast(layoutRoot.FindAnyWidget("TabletMap"));
        
        return layoutRoot;
    }

    void ShowApp(string appName)
    {
        m_PanelHome.Show(false);
        m_PanelMap.Show(false);
        m_PanelRadio.Show(false);

        if (appName == "home")  m_PanelHome.Show(true);
        if (appName == "map")   m_PanelMap.Show(true);
        if (appName == "radio") m_PanelRadio.Show(true);
        
        // Feedback sonoro de clique
        GetGame().GetPlayer().PlaySound("Battery_Insert_SoundSet", 0, false);
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        string name = w.GetName();

        if (name == "BtnF1") { ShowApp("home");  return true; }
        if (name == "BtnF2") { ShowApp("map");   return true; }
        if (name == "BtnF3") { ShowApp("radio"); return true; }
        if (name == "BtnPower") { Close(); return true; }
        
        if (name == "BtnF4") {
            PNH_RpcManager.Get().SendRPC(9992, new Param1<string>("[ALERTA SOS]"));
            return true;
        }

        return super.OnClick(w, x, y, button);
    }
}