/*
    MOD: PNH_Core
    FILE: PNH_Defines.c
    DESC: Macros globais. Comente a linha abaixo quando for lançar o servidor para o público (ganho de performance).
*/

#define PNH_DEBUG

// ==========================================
// IDs DE COMUNICAÇÃO DE REDE (RPC)
// ==========================================
const int PNH_RPC_CONFIG_SYNC     = 9991;
const int PNH_RPC_RADIO_GLOBAL    = 9992;
const int PNH_RPC_ADMIN_COMMAND   = 9993;
const int PNH_RPC_RADIO_TOGGLE    = 9994;
const int PNH_RPC_RADIO_BROADCAST = 9995; // Transmissão das músicas do servidor

// ==========================================
// IDs DE INTERFACES VISUAIS (MENUS)
// ==========================================
const int PNH_UI_TABLET_OS        = 9996; // ID que abre o nosso Tablet OS