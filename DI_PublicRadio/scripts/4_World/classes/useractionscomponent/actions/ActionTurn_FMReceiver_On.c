class ActionTurn_FMReceiver_On : ActionSingleUseBase {
	void ActionTurn_FMReceiver_On() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_PRESS_TRIGGER;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_PRESS_TRIGGER;
		m_Text = "#switch_on";
	}
	override void CreateConditionComponents() {	
		m_ConditionItem = new CCINonRuined();
		m_ConditionTarget = new CCTNone();
	}
	override bool HasTarget() { return false; }
	override bool HasProneException() { return true; }
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item ) {
		if ( !item || !item.IsInherited( skaerheim_radioreceiver_base ) ) return false;
		return !item.IsFMReceiverListening();
	}
	override void OnStartServer( ActionData action_data ) {
		super.OnStartServer( action_data );
		if ( action_data.m_MainItem ) {
			skaerheim_radioreceiver_base mediaPlayer = skaerheim_radioreceiver_base.Cast( action_data.m_MainItem );
			if ( mediaPlayer ) mediaPlayer.TurnFMReceiving_MediaOn();
		}
	}
}
