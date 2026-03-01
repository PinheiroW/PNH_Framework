modded class DayZGame
{
    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        // Intercepta e processa nossos RPCs
        if (PNH_RpcManager.Get())
        {
            PNH_RpcManager.Get().Dispatch(sender, target, rpc_type, ctx);
        }

        super.OnRPC(sender, target, rpc_type, ctx);
    }
}