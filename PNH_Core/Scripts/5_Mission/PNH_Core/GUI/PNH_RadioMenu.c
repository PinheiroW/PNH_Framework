/**
 * MOD: PNH_Core
 * FILE: PNH_RadioMenu.c
 * DESC: Menu visual do Rádio integrado com o receptor FM.
 */

class PNH_RadioMenu extends UIScriptedMenu
{
    // Textos do Visor
    private TextWidget m_TxtFreq;
    private TextWidget m_TxtInfo;
    private TextWidget m_TxtStatus;

    // Botões
    private ButtonWidget m_BtnTuneDown;
    private ButtonWidget m_BtnTuneUp;
    private ButtonWidget m_BtnVolDown;
    private ButtonWidget m_BtnVolUp;
    private ButtonWidget m_BtnPower;
    private ButtonWidget m_BtnSOS;
    private ButtonWidget m_BtnClose;

    // O Rádio que estamos a controlar
    private skaerheim_radioreceiver_base m_TargetRadio;

    override Widget Init()
    {
        layoutRoot = GetGame().GetWorkspace().CreateWidgets("PNH_Core/GUI/Layouts/PNH_Radio.layout");
        
        // Mapear Textos
        m_TxtFreq = TextWidget.Cast(layoutRoot.FindAnyWidget("TxtFreq"));
        m_TxtInfo = TextWidget.Cast(layoutRoot.FindAnyWidget("TxtInfo"));
        m_TxtStatus = TextWidget.Cast(layoutRoot.FindAnyWidget("TxtStatus"));
        
        // Mapear Botões
        m_BtnTuneDown = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTuneDown"));
        m_BtnTuneUp = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnTuneUp"));
        m_BtnVolDown = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnVolDown"));
        m_BtnVolUp = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnVolUp"));
        m_BtnPower = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnPower"));
        m_BtnSOS = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnSOS"));
        m_BtnClose = ButtonWidget.Cast(layoutRoot.FindAnyWidget("BtnClose"));
        
        return layoutRoot;
    }

    override void OnShow()
    {
        super.OnShow();
        GetGame().GetInput().ChangeGameFocus(1); 
        GetGame().GetUIManager().ShowCursor(true);
        
        FindRadioInHands();
        UpdateVisor();
    }

    override void OnHide()
    {
        super.OnHide();
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowCursor(false);
    }

    // Procura se o jogador tem o rádio nas mãos
    void FindRadioInHands()
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (player)
        {
            EntityAI itemInHands = player.GetHumanInventory().GetEntityInHands();
            if (itemInHands && itemInHands.IsInherited(skaerheim_radioreceiver_base))
            {
                m_TargetRadio = skaerheim_radioreceiver_base.Cast(itemInHands);
            }
        }
    }

    // Atualiza o painel digital
    void UpdateVisor()
    {
        if (!m_TargetRadio)
        {
            m_TxtFreq.SetText("ERRO: NENHUM RÁDIO NAS MÃOS");
            m_TxtInfo.SetText("INFO: ---");
            m_TxtStatus.SetText("ESTADO: INDISPONÍVEL");
            return;
        }

        // Frequência
        float freq = m_TargetRadio.GetTunedFrequency();
        m_TxtFreq.SetText("FREQ: " + freq.ToString() + " MHz");

        // Info da Música/Transmissão
        string song = m_TargetRadio.GetCurrentSongName();
        if (song == "") song = "Aguardando Transmissão...";
        m_TxtInfo.SetText("INFO: " + song);

        // Estado e Volume
        string estado = "DESLIGADO";
        if (m_TargetRadio.IsFMReceiverListening()) estado = "LIGADO";
        
        float vol = m_TargetRadio.GetCurrentMediaVolume();
        int volPercent = Math.Round((vol / m_TargetRadio.GetMediaVolumeMax()) * 100);
        
        m_TxtStatus.SetText("ESTADO: " + estado + " | VOL: " + volPercent.ToString() + "%");
    }

    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (w == m_BtnClose)
        {
            Close();
            return true;
        }

        // Se o botão SOS for clicado (Vamos construir a lógica do chat depois)
        if (w == m_BtnSOS)
        {
            GetGame().ChatPlayer("[SOS] Pedido de resgate enviado!");
            PNH_RpcManager.Get().SendRPC(9992, new Param1<string>("[ALERTA SOS] Preciso de ajuda na minha posição!"));
            return true;
        }

        // Os botões abaixo só funcionam se tivermos um rádio nas mãos
        if (!m_TargetRadio) return super.OnClick(w, x, y, button);

        if (w == m_BtnPower)
        {
            if (m_TargetRadio.IsFMReceiverListening())
                m_TargetRadio.TurnFMReceiving_MediaOff();
            else
                m_TargetRadio.TurnFMReceiving_MediaOn();
        }
        else if (w == m_BtnTuneUp)
        {
            m_TargetRadio.IncreaseFMReceiving_MediaHz();
        }
        else if (w == m_BtnTuneDown)
        {
            m_TargetRadio.DecreaseFMReceiving_MediaHz();
        }
        else if (w == m_BtnVolUp)
        {
            m_TargetRadio.IncreaseMediaVolume();
            m_TargetRadio.UpdateMediaVolume(); // Atualiza o áudio instantaneamente
        }
        else if (w == m_BtnVolDown)
        {
            m_TargetRadio.DecreaseMediaVolume();
            m_TargetRadio.UpdateMediaVolume(); // Atualiza o áudio instantaneamente
        }

        // Atualiza os textos da tela após qualquer clique
        UpdateVisor();

        return super.OnClick(w, x, y, button);
    }
}