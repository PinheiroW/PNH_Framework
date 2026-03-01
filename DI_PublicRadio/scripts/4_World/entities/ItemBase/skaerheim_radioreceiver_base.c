class skaerheim_radioreceiver_base : ItemBase {
    protected 	float 	m_TunedFrequencyServerSide 			= 85;
    protected 	float 	m_TunedFrequencyClientSide 			= 85;
    protected 	bool 	m_IsFMReceiverListeningServerSide 	= false;
    protected 	bool 	m_IsFMReceiverListeningClientSide 	= false;
	protected 	string 	m_CurrentSongName 					= "";
    protected 	string 	m_CurrentlyPlayingSoundSet 			= "";
    const 		string 	FM_RADIO_TURNON_SOUNDSET 			= "turnOnRadio_SoundSet";
    const 		string 	FM_RADIO_TURNOFF_SOUNDSET 			= "turnOffRadioNoise_SoundSet";
    const 		string 	FM_RADIO_STATIC_SOUNDSET 			= "baseradio_staticnoise_SoundSet";
    protected 			EffectSound m_SoundPlaying;
    protected 			EffectSound m_FMStaticSoundPlaying;
	protected 	float 	m_Volume 							= 1.0;
	protected 	bool 	m_WasRadioVolumeIncreased 			= false;
	protected 	bool 	m_WasRadioVolumeDecreased 			= false;
	protected 	bool 	m_WasRadioFrequencyIncreased 		= false;
	protected 	bool 	m_WasRadioFrequencyDecreased 		= false;
    void skaerheim_radioreceiver_base() {
        RegisterNetSyncVariableFloat("m_TunedFrequencyServerSide");
        RegisterNetSyncVariableBool("m_IsFMReceiverListeningServerSide");
        RegisterNetSyncVariableFloat( "m_Volume" );
		PR_VOLUME_STEP = 0.25;
		PR_VOLUME_MIN = 0.00;
		PR_VOLUME_MAX = 2.00;
		SetEventMask(EntityEvent.FRAME);
    }
    override void OnStoreSave(ParamsWriteContext ctx) {
        super.OnStoreSave(ctx);
        ctx.Write(m_TunedFrequencyServerSide);
        ctx.Write(m_IsFMReceiverListeningServerSide);
		ctx.Write( m_Volume );
    }
    override bool OnStoreLoad(ParamsReadContext ctx, int version) {
        super.OnStoreLoad(ctx, version);
        if (!ctx.Read(m_TunedFrequencyServerSide)) return false;
        if (!ctx.Read(m_IsFMReceiverListeningServerSide)) return false;
		if ( !ctx.Read( m_Volume ) ) return false;
        return true;
    }
    override void AfterStoreLoad() {
        super.AfterStoreLoad();
        TurnFMReceiving_MediaOff();
    }
    override void TurnFMReceiving_MediaOn() {
        m_IsFMReceiverListeningServerSide = true;
        SetSynchDirty();
		UpdateAnimationPhaseState();
        PassiveRadioSystem.RegisterRadio(this);
        if (!GetGame().IsDedicatedServer()) {
            if (PassiveRadioSystem.m_LastBroadcastFrequency == GetTunedFrequency()) {
                PlayPublicRadioSound(PassiveRadioSystem.m_LastBroadcastSoundSet);
            }
        }
    }
    override void TurnFMReceiving_MediaOff() {
        m_IsFMReceiverListeningServerSide = false;
        SetSynchDirty();
		UpdateAnimationPhaseState();
        PassiveRadioSystem.UnregisterRadio(this);
        if (!GetGame().IsDedicatedServer()) {
            StopPublicRadioSound();
        }
    }
	override void IncreaseFMReceiving_MediaHz() {
		if ( IsFMReceiverListening() && GetTunedFrequency() < 125 ) {
			float Increase_Hz = m_TunedFrequencyServerSide + 1;
			if ( Increase_Hz > 120 )
				m_TunedFrequencyServerSide = 85;
			else m_TunedFrequencyServerSide = Increase_Hz;
			SetSynchDirty();
			if (!GetGame().IsDedicatedServer()) {
				StopPublicRadioSound();
			}
		}
	}
	override void DecreaseFMReceiving_MediaHz() {
		if ( IsFMReceiverListening() && GetTunedFrequency() > 80 ) {
			float Decrease_Hz = m_TunedFrequencyServerSide - 1;
			if ( Decrease_Hz < 85 )
				m_TunedFrequencyServerSide = 120;
			else m_TunedFrequencyServerSide = Decrease_Hz;
			SetSynchDirty();
			if (!GetGame().IsDedicatedServer()) {
				StopPublicRadioSound();
			}
		}
	}
	override void SetCurrentSongName(string name) {
		if ( name ) m_CurrentSongName = name;
	}
	override string GetCurrentSongName() {
		if ( m_CurrentSongName)
			return m_CurrentSongName;
		return "";
	}
    override void PlayPublicRadioSound(string soundSet) {
        if (!GetGame().IsDedicatedServer()) {
            if (m_SoundPlaying && m_CurrentlyPlayingSoundSet == soundSet) {
                return;
			}
            StopPublicRadioSound();
            if (!m_SoundPlaying) {
                PlaySoundSetLoop(m_SoundPlaying, soundSet, 1, 0.3);
                m_CurrentlyPlayingSoundSet = soundSet;
            }
        }
    }
    override void StopPublicRadioSound() {
        if (!GetGame().IsDedicatedServer()) {
            if (m_SoundPlaying)  {
                m_SoundPlaying.SoundStop();
                SEffectManager.DestroyEffect(m_SoundPlaying);
                m_SoundPlaying = null;
            }
        }
		m_CurrentlyPlayingSoundSet = "";
		m_CurrentSongName = "";
    }
	override string GetCurrentlyPlayingSoundSet() {
		return m_CurrentlyPlayingSoundSet;
	}
    override bool IsFMReceiverListening() {
        return m_IsFMReceiverListeningServerSide;
    }
    override float GetTunedFrequency()  {
        return m_TunedFrequencyServerSide;
    }
    int GetTunedFrequencyHz()  {
        return Math.Round(m_TunedFrequencyServerSide * 10);
    }
    override void EEDelete(EntityAI parent)  {
        super.EEDelete(parent);
        if (GetGame().IsClient()) TurnFMReceiving_MediaOff();
		StopSoundSet(m_SoundPlaying);
		RemoveCustomCallBacks();
    }
	override bool NameOverride(out string output) {
		string songName = GetCurrentSongName();
		output = "FM Radio [" + m_TunedFrequencyServerSide.ToString() + " MHz] " + songName;
		return true;
	}
    override bool DescriptionOverride(out string output) {
		string songDesc = GetCurrentSongName();
        output = "Frequency: " + m_TunedFrequencyServerSide.ToString() + " MHz] " + songDesc;
        return true;
    }
    override void OnVariablesSynchronized() {
        super.OnVariablesSynchronized();
        if (m_TunedFrequencyClientSide != m_TunedFrequencyServerSide)  {
            m_TunedFrequencyClientSide = m_TunedFrequencyServerSide;
        }
        if (m_IsFMReceiverListeningClientSide != m_IsFMReceiverListeningServerSide)  {
            m_IsFMReceiverListeningClientSide = m_IsFMReceiverListeningServerSide;
            if (IsFMReceiverListening()) {
                TurnFMReceiving_MediaOn();
				if (!m_FMStaticSoundPlaying) {
					EffectSound FMRadio_OnClick = SEffectManager.PlaySound( FM_RADIO_TURNON_SOUNDSET, GetPosition() );
					FMRadio_OnClick.SetSoundAutodestroy( true );
					PlaySoundSetLoop(m_FMStaticSoundPlaying, FM_RADIO_STATIC_SOUNDSET, 1, 0.2);
					RemoveCustomCallBacks();
					GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( this.UpdateMediaVolume, 100, true );
				}
            } else  {
                TurnFMReceiving_MediaOff();
				if (m_FMStaticSoundPlaying) {
					EffectSound FMRadio_OffClick = SEffectManager.PlaySound( FM_RADIO_TURNOFF_SOUNDSET, GetPosition() );
					FMRadio_OffClick.SetSoundAutodestroy( true );
					m_FMStaticSoundPlaying.SoundStop();
					SEffectManager.DestroyEffect(m_FMStaticSoundPlaying);
					m_FMStaticSoundPlaying = null;
				}
				RemoveCustomCallBacks();
            }
        }
		UpdateAnimationPhaseState();
    }
	void RemoveCustomCallBacks() {
		if (GetGame().IsServer()) {
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(UpdateMediaVolume);
		}
	}
	override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner) {
		super.OnItemLocationChanged(old_owner, new_owner);
		SetSynchDirty();
		UpdateAnimationPhaseState();
	}
	override void UpdateAnimationPhaseState() {
		if ( IsFMReceiverListening() ) {
			SetAnimationPhase( "Rotate_Antenna", 1 );
		}
		else {
			if ( ItemIsInHands() ) { SetAnimationPhase( "Rotate_Antenna", 0.35 ); }
			else { SetAnimationPhase( "Rotate_Antenna", 0 ); }
		}
	}
	bool ItemIsInHands() {
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player) return false;
		EntityAI item = player.GetHumanInventory().GetEntityInHands();
		return item && item == this;
	}
	
	override float GetMediaVolumeMin() { return PR_VOLUME_MIN; }
	override float GetMediaVolumeMax() { return PR_VOLUME_MAX; }
	override float GetCurrentMediaVolume() { return m_Volume; }
	override void IncreaseMediaVolume() {
		if (!IsFMReceiverListening()) return;
		if ( GetCurrentMediaVolume() >= GetMediaVolumeMax() ) return;
		m_Volume += PR_VOLUME_STEP;
		if ( m_Volume > GetMediaVolumeMax() )
			m_Volume = GetMediaVolumeMax();
		SetSynchDirty();
	}
	override void DecreaseMediaVolume() {
		if (!IsFMReceiverListening()) return;
		if ( GetCurrentMediaVolume() <= GetMediaVolumeMin() ) return;
		m_Volume -= PR_VOLUME_STEP;
		if ( m_Volume < GetMediaVolumeMin() )
			m_Volume = GetMediaVolumeMin();
		SetSynchDirty();
	}
	override void UpdateMediaVolume() {
		if (!IsFMReceiverListening()) return;
        if (!GetGame().IsDedicatedServer()) {
			if ( m_SoundPlaying ) {
				m_SoundPlaying.SetSoundVolume( m_Volume );
			}
			if ( m_FMStaticSoundPlaying ) {
				m_FMStaticSoundPlaying.SetSoundVolume( m_Volume * 0.5 );
			}
		}
		if (m_SoundPlaying && m_FMStaticSoundPlaying) {
			if (m_SoundPlaying.GetSoundVolume() == GetCurrentMediaVolume()) {
				if (m_FMStaticSoundPlaying.GetSoundVolume() == GetCurrentMediaVolume() * 0.5) {
					RemoveCustomCallBacks();
				}
			}
		}
	}
    override void SetActions() {
        super.SetActions();
        AddAction(ActionTurn_FMReceiver_On);
        AddAction(ActionTurn_FMReceiver_Off);
    }
}
