static int RPC_SKAERHEIM_PUBLIC_RADIO_BROADCAST = 2846357952;
modded class ItemBase {
	float PR_VOLUME_STEP						= 0.25;
	float PR_VOLUME_MIN							= 0.00;
	float PR_VOLUME_MAX 						= 2.00;
	void TurnFMReceiving_MediaOn() 				{ return; }
	void TurnFMReceiving_MediaOff() 			{ return; }
	void UpdateAnimationPhaseState()			{ return; }
	void StopPublicRadioSound() 				{ return; }
	void PlayPublicRadioSound(string soundSet) 	{ return; }
	void IncreaseFMReceiving_MediaHz()			{ return; }
	void DecreaseFMReceiving_MediaHz()			{ return; }
	void ChangeFMRadioHz(int direction)			{ return; }
	void SetCurrentSongName(string name) 		{ return; }
	bool IsFMReceiverListening() 				{ return false; }
    float GetTunedFrequency() 					{ return 85; }
	string GetCurrentSongName() 				{ return ""; }
	string GetCurrentlyPlayingSoundSet() 		{ return ""; }
	float GetMediaVolumeMin() 					{ return PR_VOLUME_MIN; }
	float GetMediaVolumeMax() 					{ return PR_VOLUME_MAX; }
	float GetCurrentMediaVolume() 				{ return 1; }
	void UpdateMediaVolume() 					{ return; }
	void IncreaseMediaVolume() 					{ return; }
	void DecreaseMediaVolume() 					{ return; }
}

