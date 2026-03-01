class ActionTurn_FMReceiver_Off : ActionSingleUseBase {
	void ActionTurn_FMReceiver_Off() {
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONMOD_PRESS_TRIGGER;
		m_CommandUIDProne 	= DayZPlayerConstants.CMD_ACTIONFB_PRESS_TRIGGER;
	}
	override void CreateConditionComponents() {	
		m_ConditionItem 	= new CCINone();
		m_ConditionTarget 	= new CCTNone();
	}
	override bool HasTarget() { return false; }
	override bool HasProneException() { return true; }
	override string GetText() { return m_Text; }
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item ) {
		if ( !item || !item.IsInherited( skaerheim_radioreceiver_base ) ) return false;
		float volumePercent = ( item.GetCurrentMediaVolume() * 100 ) / ( item.GetMediaVolumeMax() / 2 );
		m_Text = "Volume [" + volumePercent + "%] " + "#switch_off";
		return item.IsFMReceiverListening();
	}
	override void OnStartServer( ActionData action_data ) {
		super.OnStartServer( action_data );
		if ( action_data.m_MainItem ) {
			skaerheim_radioreceiver_base mediaPlayer = skaerheim_radioreceiver_base.Cast( action_data.m_MainItem );
			if ( mediaPlayer ) mediaPlayer.TurnFMReceiving_MediaOff();
		}
	}
}
