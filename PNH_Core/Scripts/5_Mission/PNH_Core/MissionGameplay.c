/**
 * MOD: PNH_Core
 * FILE: MissionGameplay.c
 */

modded class MissionGameplay
{
    // 1. ENSINA O MOTOR DO JOGO A CRIAR O NOSSO MENU
    override UIScriptedMenu CreateScriptedMenu(int id)
    {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu(id); // Deixa o jogo carregar os menus nativos (Inventário, etc)
        
        if (menu) return menu; 

        // Se for o nosso ID 9996, cria a interface do Tablet
        if (id == PNH_UI_TABLET_OS)
        {
            menu = new PNH_TabletOS;
            menu.SetID(id);
        }
        
        return menu;
    }

    // 2. DETETA A TECLA 'M' PARA ABRIR O TABLET
    override void OnKeyPress(int key)
    {
        super.OnKeyPress(key);
        
        // Verifica se o jogador apertou 'M' e se não tem o Inventário/Menu aberto
        if (key == KeyCode.KC_M)
        {
            if (!GetGame().GetUIManager().GetMenu())
            {
                PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
                if (player)
                {
                    PNH_Tablet_Black tablet = PNH_Tablet_Black.Cast(player.GetHumanInventory().GetEntityInHands());
                    
                    // Se o tablet estiver nas mãos, com bateria e ligado...
                    if (tablet && tablet.GetCompEM() && tablet.GetCompEM().IsWorking())
                    {
                        // Abre a nossa interface!
                        GetGame().GetUIManager().EnterScriptedMenu(PNH_UI_TABLET_OS, null);
                    }
                }
            }
        }
    }
}