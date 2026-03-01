modded class PlayerBase {
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) {
		if ( rpc_type == RPC_SKAERHEIM_PUBLIC_RADIO_BROADCAST ) {
			Param4<float, string, int, string> data;
			if (ctx.Read(data)) {
				float frequency = data.param1;
				string soundSet = data.param2;
				int length = data.param3;
				string songName = data.param4;

				PassiveRadioSystem.HandleIncomingBroadcast(frequency, soundSet, songName);
			}
		} super.OnRPC(sender, rpc_type, ctx);
	}
}
