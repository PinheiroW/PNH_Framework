/*
    MOD: PNH_Core
    FILE: PNH_RpcManager.c
    DESC: Sistema de Rede (Network) sem conflitos.
*/

class PNH_RpcManager
{
    private static ref PNH_RpcManager m_Instance;
    private ref map<int, string> m_RpcMethods;
    private ref map<int, Class> m_RpcInstances;

    void PNH_RpcManager()
    {
        m_RpcMethods = new map<int, string>();
        m_RpcInstances = new map<int, Class>();
        PNH_Logger.Log("RPC", "Gerenciador de RPC Iniciado.");
    }

    static PNH_RpcManager Get()
    {
        if (!m_Instance) m_Instance = new PNH_RpcManager();
        return m_Instance;
    }

    void Register(int rpc_id, Class instance, string functionName)
    {
        if (m_RpcMethods.Contains(rpc_id)) return;
        m_RpcMethods.Insert(rpc_id, functionName);
        m_RpcInstances.Insert(rpc_id, instance);
    }

    void Dispatch(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        if (!m_RpcMethods.Contains(rpc_type)) return;

        string funcName = m_RpcMethods.Get(rpc_type);
        Class instance = m_RpcInstances.Get(rpc_type);

        if (instance && funcName != "")
        {
            // CORRIGIDO: Chamada direta e mais segura para a engine Enfusion.
            // Evita criar um objeto Param3 que pode causar falhas em sobrecarga.
            GetGame().GameScript.CallFunction(instance, funcName, null, ctx, sender, target);
        }
    }
    
    void SendRPC(int rpc_id, Param params, bool guaranteed = true, PlayerIdentity recipient = null)
    {
        GetGame().RPCSingleParam(null, rpc_id, params, guaranteed, recipient);
    }
}