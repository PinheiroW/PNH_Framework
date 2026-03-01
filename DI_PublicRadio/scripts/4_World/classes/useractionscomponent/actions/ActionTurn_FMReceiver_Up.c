// class ActionTurn_FMReceiver_Up : ActionSingleUseBase {
	// void ActionTurn_FMReceiver_Up() {
		// m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_PRESS_TRIGGER;
		// m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_PRESS_TRIGGER;
	// }
	// override void CreateConditionComponents() {
		// m_ConditionItem = new CCINonRuined();
		// m_ConditionTarget = new CCTNone();
	// }
	// override string GetText() { return m_Text; }
	// override bool HasTarget() { return false; }
	// override bool HasProneException() { return true; }
	// override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item ) {
		// if ( !item || !item.IsInherited( skaerheim_radioreceiver_base ) ) return false;
		// if ( item.IsFMReceiverListening() ) {
			// float volumePercent = ( item.GetCurrentMediaVolume() * 100 ) / ( item.GetMediaVolumeMax() / 2 );
			// m_Text = "+Volume [" + volumePercent + "%]";
			// return item.GetCurrentMediaVolume() < item.GetMediaVolumeMax();
		// } return false;
	// }
	// override void OnStartServer( ActionData action_data ) {
		// super.OnStartServer( action_data );
		// if ( action_data.m_MainItem ) {
			// skaerheim_radioreceiver_base mediaPlayer = skaerheim_radioreceiver_base.Cast( action_data.m_MainItem );
			// if ( mediaPlayer && mediaPlayer.IsFMReceiverListening() )
				// mediaPlayer.IncreaseMediaVolume();
		// }
	// }
// }
