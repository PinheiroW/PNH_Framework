modded class MissionGameplay
{
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player) return;

        // Get item in hands
        EntityAI item = player.GetHumanInventory().GetEntityInHands();
        skaerheim_radioreceiver_base radio;
        if (!Class.CastTo(radio, item))
            return; // not holding your radio
        if (!radio.IsFMReceiverListening())
            return;
		
        Input input = GetGame().GetInput();

        // Frequency up
        if (input.LocalPress("UA_PUBLIC_RADIO_FREQUENCY_UP"))
        {
            radio.IncreaseFMReceiving_MediaHz();
        }

        // Frequency down
        if (input.LocalPress("UA_PUBLIC_RADIO_FREQUENCY_DOWN"))
        {
            radio.DecreaseFMReceiving_MediaHz();
        }

        // Volume up
        if (input.LocalPress("UA_PUBLIC_RADIO_VOLUME_UP"))
        {
            radio.IncreaseMediaVolume();
        }

        // Volume down
        if (input.LocalPress("UA_PUBLIC_RADIO_VOLUME_DOWN"))
        {
            radio.DecreaseMediaVolume();
        }
    }
}
