/**
 * MOD: PNH_Core
 * FILE: PNH_RadioMenu.c
 * DESC: Menu visual do Rádio com envio de RPC para o Servidor.
 */

class PNH_RadioMenu extends UIScriptedMenu
{
    private ButtonWidget m_BtnMute;
    private ButtonWidget m_BtnClose;

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("PNH_Core/GUI/Layouts/PNH_Radio.layout");
        
        m_BtnMute = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnMute"));
        m_BtnClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClose"));
        
        return layoutRoot;
    }

    override void OnShow()
    {
        super.OnShow();
        GetGame().GetInput().ChangeGameFocus(1); 
        GetGame().GetUIManager().ShowCursor(true);
    }

    override void OnHide()
    {
        super.OnHide();
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowCursor(false);
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_BtnMute)
        {
            // DEBUG CLIENTE: Verificável no script.log do seu PC (Documentos/DayZ)
            Print("[PNH DEBUG] Clique detectado. Enviando RPC 9994 ao servidor...");
            
            // Envia o sinal para o servidor
            PNH_RpcManager.Get().SendRPC(9994, new Param1<bool>(true));
            
            GetGame().ChatPlayer("[PNH] Enviando comando de rádio...");
            return true;
        }
        
        if (w == m_BtnClose)
        {
            Close();
            return true;
        }

        return super.OnClick(w, x, y, button);
    }
}