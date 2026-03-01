/**
 * MOD: PNH_Core
 * FILE: PNH_Tablet.c
 * DESC: Item físico do Tablet. Consome bateria e atua como recetor de Rádio FM.
 */

class PNH_Tablet_ColorBase : ItemBase
{
    // ==========================================
    // VARIÁVEIS DO RECETOR DE RÁDIO
    // ==========================================
    protected float m_TunedFrequencyServerSide = 85;
    protected float m_TunedFrequencyClientSide = 85;
    protected bool m_IsFMReceiverListeningServerSide = false;
    protected bool m_IsFMReceiverListeningClientSide = false;
    protected string m_CurrentSongName = "";
    protected string m_CurrentlyPlayingSoundSet = "";
    protected float m_Volume = 1.0;

    protected EffectSound m_SoundPlaying;
    protected EffectSound m_FMStaticSoundPlaying;

    const string FM_RADIO_TURNON_SOUNDSET = "turnOnRadio_SoundSet";
    const string FM_RADIO_TURNOFF_SOUNDSET = "turnOffRadioNoise_SoundSet";
    const string FM_RADIO_STATIC_SOUNDSET = "baseradio_staticnoise_SoundSet";
    
    float PR_VOLUME_STEP = 0.25;
    float PR_VOLUME_MIN = 0.00;
    float PR_VOLUME_MAX = 2.00;

    void PNH_Tablet_ColorBase()
    {
        // Sincroniza o rádio entre o Servidor e o Cliente
        RegisterNetSyncVariableFloat("m_TunedFrequencyServerSide");
        RegisterNetSyncVariableBool("m_IsFMReceiverListeningServerSide");
        RegisterNetSyncVariableFloat("m_Volume");
        SetEventMask(EntityEvent.FRAME);
    }

    // ==========================================
    // SISTEMA DE ENERGIA (BATERIA E ECRÃ)
    // ==========================================
    override void OnWorkStart()
    {
        super.OnWorkStart();
        if (GetGame().IsServer() || !GetGame().IsMultiplayer())
        {
            // O jogador ligou o tablet com bateria: Acende o ecrã
            SetObjectTexture(0, "PNH_Core\\GUI\\textures\\tablet.edds");
            SetObjectTexture(1, "PNH_Core\\GUI\\textures\\tablet.edds");
        }
    }

    override void OnWorkStop()
    {
        super.OnWorkStop();
        if (GetGame().IsServer() || !GetGame().IsMultiplayer())
        {
            // O jogador desligou ou a bateria acabou: Apaga o ecrã
            SetObjectTexture(0, "PNH_Core\\Models\\textures\\tab2_co.paa");
            SetObjectTexture(1, "PNH_Core\\Models\\textures\\tab2_co.paa");
        }
        
        // Segurança: Se o tablet desligar, o áudio do rádio também é cortado
        if (IsFMReceiverListening())
        {
            TurnFMReceiving_MediaOff();
        }
    }

    override void SetActions()
    {
        super.SetActions();
        // Permite ligar/desligar com a tecla de atalho enquanto está nas mãos
        AddAction(ActionTurnOnWhileInHands);
        AddAction(ActionTurnOffWhileInHands);
    }

    // ==========================================
    // SISTEMA DE SINTONIA E ÁUDIO
    // ==========================================
    override void OnStoreSave(ParamsWriteContext ctx) {
        super.OnStoreSave(ctx);
        ctx.Write(m_TunedFrequencyServerSide);
        ctx.Write(m_IsFMReceiverListeningServerSide);
        ctx.Write(m_Volume);
    }
    
    override bool OnStoreLoad(ParamsReadContext ctx, int version) {
        if (!super.OnStoreLoad(ctx, version)) return false;
        if (!ctx.Read(m_TunedFrequencyServerSide)) return false;
        if (!ctx.Read(m_IsFMReceiverListeningServerSide)) return false;
        if (!ctx.Read(m_Volume)) return false;
        return true;
    }

    override void AfterStoreLoad() {
        super.AfterStoreLoad();
        TurnFMReceiving_MediaOff();
    }

    void TurnFMReceiving_MediaOn() {
        if (!GetCompEM().IsWorking()) return; // Impede ligar a app de rádio sem bateria
        
        m_IsFMReceiverListeningServerSide = true;
        SetSynchDirty();
        PNH_RadioSystem.RegisterRadio(this);
        if (!GetGame().IsDedicatedServer()) {
            if (PNH_RadioSystem.m_LastBroadcastFrequency == GetTunedFrequency()) {
                PlayPublicRadioSound(PNH_RadioSystem.m_LastBroadcastSoundSet);
            }
        }
    }

    void TurnFMReceiving_MediaOff() {
        m_IsFMReceiverListeningServerSide = false;
        SetSynchDirty();
        PNH_RadioSystem.UnregisterRadio(this);
        if (!GetGame().IsDedicatedServer()) StopPublicRadioSound();
    }

    void IncreaseFMReceiving_MediaHz() {
        if (IsFMReceiverListening() && GetTunedFrequency() < 125) {
            float Increase_Hz = m_TunedFrequencyServerSide + 1;
            if (Increase_Hz > 120) m_TunedFrequencyServerSide = 85;
            else m_TunedFrequencyServerSide = Increase_Hz;
            SetSynchDirty();
            if (!GetGame().IsDedicatedServer()) StopPublicRadioSound();
        }
    }

    void DecreaseFMReceiving_MediaHz() {
        if (IsFMReceiverListening() && GetTunedFrequency() > 80) {
            float Decrease_Hz = m_TunedFrequencyServerSide - 1;
            if (Decrease_Hz < 85) m_TunedFrequencyServerSide = 120;
            else m_TunedFrequencyServerSide = Decrease_Hz;
            SetSynchDirty();
            if (!GetGame().IsDedicatedServer()) StopPublicRadioSound();
        }
    }

    void SetCurrentSongName(string name) { m_CurrentSongName = name; }
    string GetCurrentSongName() { return m_CurrentSongName; }
    string GetCurrentlyPlayingSoundSet() { return m_CurrentlyPlayingSoundSet; }
    bool IsFMReceiverListening() { return m_IsFMReceiverListeningServerSide; }
    float GetTunedFrequency() { return m_TunedFrequencyServerSide; }
    float GetMediaVolumeMin() { return PR_VOLUME_MIN; }
    float GetMediaVolumeMax() { return PR_VOLUME_MAX; }
    float GetCurrentMediaVolume() { return m_Volume; }

    void PlayPublicRadioSound(string soundSet) {
        if (!GetGame().IsDedicatedServer()) {
            if (m_SoundPlaying && m_CurrentlyPlayingSoundSet == soundSet) return;
            StopPublicRadioSound();
            if (!m_SoundPlaying) {
                PlaySoundSetLoop(m_SoundPlaying, soundSet, 1, 0.3);
                m_CurrentlyPlayingSoundSet = soundSet;
            }
        }
    }

    void StopPublicRadioSound() {
        if (!GetGame().IsDedicatedServer()) {
            if (m_SoundPlaying) {
                m_SoundPlaying.SoundStop();
                SEffectManager.DestroyEffect(m_SoundPlaying);
                m_SoundPlaying = null;
            }
        }
        m_CurrentlyPlayingSoundSet = "";
        m_CurrentSongName = "";
    }

    void IncreaseMediaVolume() {
        if (!IsFMReceiverListening()) return;
        if (GetCurrentMediaVolume() >= GetMediaVolumeMax()) return;
        m_Volume += PR_VOLUME_STEP;
        if (m_Volume > GetMediaVolumeMax()) m_Volume = GetMediaVolumeMax();
        SetSynchDirty();
    }

    void DecreaseMediaVolume() {
        if (!IsFMReceiverListening()) return;
        if (GetCurrentMediaVolume() <= GetMediaVolumeMin()) return;
        m_Volume -= PR_VOLUME_STEP;
        if (m_Volume < GetMediaVolumeMin()) m_Volume = GetMediaVolumeMin();
        SetSynchDirty();
    }

    void UpdateMediaVolume() {
        if (!IsFMReceiverListening()) return;
        if (!GetGame().IsDedicatedServer()) {
            if (m_SoundPlaying) m_SoundPlaying.SetSoundVolume(m_Volume);
            if (m_FMStaticSoundPlaying) m_FMStaticSoundPlaying.SetSoundVolume(m_Volume * 0.5);
        }
        if (m_SoundPlaying && m_FMStaticSoundPlaying) {
            if (m_SoundPlaying.GetSoundVolume() == GetCurrentMediaVolume() && m_FMStaticSoundPlaying.GetSoundVolume() == GetCurrentMediaVolume() * 0.5) {
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(UpdateMediaVolume);
            }
        }
    }

    override void OnVariablesSynchronized() {
        super.OnVariablesSynchronized();
        if (m_TunedFrequencyClientSide != m_TunedFrequencyServerSide) {
            m_TunedFrequencyClientSide = m_TunedFrequencyServerSide;
        }
        if (m_IsFMReceiverListeningClientSide != m_IsFMReceiverListeningServerSide) {
            m_IsFMReceiverListeningClientSide = m_IsFMReceiverListeningServerSide;
            if (IsFMReceiverListening()) {
                TurnFMReceiving_MediaOn();
                if (!m_FMStaticSoundPlaying) {
                    EffectSound FMRadio_OnClick = SEffectManager.PlaySound(FM_RADIO_TURNON_SOUNDSET, GetPosition());
                    FMRadio_OnClick.SetSoundAutodestroy(true);
                    PlaySoundSetLoop(m_FMStaticSoundPlaying, FM_RADIO_STATIC_SOUNDSET, 1, 0.2);
                    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(UpdateMediaVolume);
                    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.UpdateMediaVolume, 100, true);
                }
            } else {
                TurnFMReceiving_MediaOff();
                if (m_FMStaticSoundPlaying) {
                    EffectSound FMRadio_OffClick = SEffectManager.PlaySound(FM_RADIO_TURNOFF_SOUNDSET, GetPosition());
                    FMRadio_OffClick.SetSoundAutodestroy(true);
                    m_FMStaticSoundPlaying.SoundStop();
                    SEffectManager.DestroyEffect(m_FMStaticSoundPlaying);
                    m_FMStaticSoundPlaying = null;
                }
                GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(UpdateMediaVolume);
            }
        }
    }

    override void EEDelete(EntityAI parent) {
        super.EEDelete(parent);
        if (GetGame().IsClient()) TurnFMReceiving_MediaOff();
        StopSoundSet(m_SoundPlaying);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(UpdateMediaVolume);
    }
}

class PNH_Tablet_Black : PNH_Tablet_ColorBase {};