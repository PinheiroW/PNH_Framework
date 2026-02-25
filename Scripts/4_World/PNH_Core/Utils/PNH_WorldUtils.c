/*
    MOD: PNH_Core
    FILE: PNH_WorldUtils.c
    DESC: Funções auxiliares para itens e ambiente.
*/

class PNH_WorldUtils
{
    /**
     * @brief Spawna um item no chão em uma posição específica de forma segura.
     */
    static EntityAI SpawnItem(string className, vector pos)
    {
        return EntityAI.Cast(GetGame().CreateObjectEx(className, pos, ECE_PLACE_ON_SURFACE));
    }

    /**
     * @brief Calcula a distância entre dois objetos.
     */
    static float GetDistance(Object obj1, Object obj2)
    {
        if (!obj1 || !obj2) return 0;
        return vector.Distance(obj1.GetPosition(), obj2.GetPosition());
    }
}