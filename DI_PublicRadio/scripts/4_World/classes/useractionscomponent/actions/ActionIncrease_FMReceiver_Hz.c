// class ActionIncrease_FMReceiver_Hz : ActionSingleUseBase {
	// void ActionIncrease_FMReceiver_Hz() {
		// m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONMOD_PRESS_TRIGGER;
		// m_CommandUIDProne 	= DayZPlayerConstants.CMD_ACTIONFB_PRESS_TRIGGER;
	// }
	// override void CreateConditionComponents() {	
		// m_ConditionItem 	= new CCINonRuined();
		// m_ConditionTarget 	= new CCTNone();
	// }
	// override string GetText() { return m_Text; }
	// override bool HasTarget() { return false; }
	// override bool HasProneException() { return true; }
	// override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item ) {
		// if ( item ) {
			// skaerheim_radioreceiver_base FMRadio_Item = skaerheim_radioreceiver_base.Cast( item );
			// if ( FMRadio_Item ) {
				// m_Text = "Increase Frequency";
				// return item.IsFMReceiverListening();
			// }
		// } return false;
	// }
	// override void OnStartServer( ActionData action_data ) {
		// super.OnStartServer( action_data );
		// if ( action_data.m_MainItem ) {
			// skaerheim_radioreceiver_base mediaPlayer = skaerheim_radioreceiver_base.Cast( action_data.m_MainItem );
			// if ( mediaPlayer ) mediaPlayer.IncreaseFMReceiving_MediaHz();
		// }
	// }
// }
