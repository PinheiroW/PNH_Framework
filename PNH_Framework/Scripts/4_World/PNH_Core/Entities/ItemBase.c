/**
 * MOD: PNH_Core
 * FILE: ItemBase.c
 */

modded class ItemBase
{
    override void EEInit()
    {
        super.EEInit();
        PNH_Guard.CheckEntity(this);
    }

    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);
        PNH_Guard.RemoveFromTracking(this);
    }

    override bool OnStoreLoad(ParamsReadContext ctx, int version)
    {
        if (!super.OnStoreLoad(ctx, version)) return false;
        
        // Validação extra crítica para storages virtuais e físicos
        PNH_Guard.CheckEntity(this);
        return true;
    }
}