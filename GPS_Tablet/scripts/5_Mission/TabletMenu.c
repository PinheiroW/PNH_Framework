class TabletMenu : UIScriptedMenu
{
    protected Widget m_Root;
    protected MapWidget m_Map;

    protected ButtonWidget m_ZoomIn;
    protected ButtonWidget m_ZoomOut;
    protected ButtonWidget m_Back;
    protected ButtonWidget m_Power;

    override Widget Init()
    {
        m_Root = GetGame().GetWorkspace().CreateWidgets("GPS_Tablet\gui\Layouts\tab2.layout");

        m_Map = MapWidget.Cast(m_Root.FindAnyWidget("TabletMap"));

        m_ZoomIn = ButtonWidget.Cast(m_Root.FindAnyWidget("zoomin"));
        m_ZoomOut = ButtonWidget.Cast(m_Root.FindAnyWidget("zoomout"));
        m_Back = ButtonWidget.Cast(m_Root.FindAnyWidget("back"));
        m_Power = ButtonWidget.Cast(m_Root.FindAnyWidget("power"));

        return m_Root;
    }

    override void OnShow()
    {
        super.OnShow();
        GetGame().GetInput().ChangeGameFocus(1);
        GetGame().GetMission().GetHud().Show(false);
    }

    override void OnHide()
    {
        super.OnHide();
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().GetHud().Show(true);
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_ZoomIn && m_Map)
        {
            m_Map.SetScale(m_Map.GetScale() * 0.8);
            return true;
        }

        if (w == m_ZoomOut && m_Map)
        {
            m_Map.SetScale(m_Map.GetScale() * 1.25);
            return true;
        }

        if (w == m_Back)
        {
            Close();
            return true;
        }

        if (w == m_Power)
        {
            Close();
            return true;
        }

        return false;
    }
};