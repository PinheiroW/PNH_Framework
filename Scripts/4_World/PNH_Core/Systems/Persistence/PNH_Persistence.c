/**
 * MOD: PNH_Core
 * FILE: PNH_Persistence.c
 * DESC: Gerencia Leitura/Escrita no disco ($profile).
 */

class PNH_Persistence
{
    // Define onde os arquivos ficarão salvos
    static const string ROOT_FOLDER = "$profile:PNH_Core/Players/";

    // Carrega um perfil existente ou cria um novo
    static ref PNH_PlayerProfile LoadProfile(string steamID)
    {
        // 1. Garante que as pastas existem
        if (!FileExist("$profile:PNH_Core")) MakeDirectory("$profile:PNH_Core");
        if (!FileExist(ROOT_FOLDER)) MakeDirectory(ROOT_FOLDER);

        string path = ROOT_FOLDER + steamID + ".json";
        ref PNH_PlayerProfile profile = new PNH_PlayerProfile();

        // 2. Se o arquivo existe, carrega
        if (FileExist(path))
        {
            JsonFileLoader<PNH_PlayerProfile>.JsonLoadFile(path, profile);
            // Backup de segurança: se o ID vier vazio, reinicializa
            if (profile.SteamID == "") profile.SteamID = steamID;
        }
        else
        {
            // 3. Se não existe, cria um novo
            profile.Initialize(steamID);
            SaveProfile(profile);
            PNH_Logger.Log("Persistence", "Novo perfil criado: " + steamID);
        }

        return profile;
    }

    // Salva o perfil no disco
    static void SaveProfile(PNH_PlayerProfile profile)
    {
        if (!profile) return;
        
        string path = ROOT_FOLDER + profile.SteamID + ".json";
        profile.UpdateLoginDate();
        
        JsonFileLoader<PNH_PlayerProfile>.JsonSaveFile(path, profile);
    }
}