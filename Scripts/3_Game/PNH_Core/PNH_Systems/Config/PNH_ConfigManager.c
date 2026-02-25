/*
    MOD: PNH_Core
    FILE: PNH_ConfigManager.c
    DESC: Sistema genérico para Salvar e Carregar JSON.
*/

class PNH_ConfigManager
{
    private static const string ROOT_FOLDER = "$profile:PNH_Core/";

    static void Load(string filename, Class configData)
    {
        string path = ROOT_FOLDER + filename;
        
        if (!FileExist(ROOT_FOLDER))
        {
            MakeDirectory(ROOT_FOLDER);
        }

        if (FileExist(path))
        {
            JsonFileLoader<Class>.JsonLoadFile(path, configData);
            PNH_Logger.Log("Config", "Carregado: " + filename);
        }
        else
        {
            PNH_Logger.Log("Config", "Criando padrao: " + filename);
            Save(filename, configData);
        }
    }

    static void Save(string filename, Class configData)
    {
        string path = ROOT_FOLDER + filename;

        if (!FileExist(ROOT_FOLDER))
        {
            MakeDirectory(ROOT_FOLDER);
        }

        JsonFileLoader<Class>.JsonSaveFile(path, configData);
    }
}