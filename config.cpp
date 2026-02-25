class CfgPatches
{
    class PNH_Core
    {
        units[]={};
        weapons[]={};
        requiredVersion=0.1;
        // Dependências vitais: O Core precisa carregar DEPOIS do jogo base
        requiredAddons[]={ "DZ_Data", "DZ_Scripts" }; 
    };
};

class CfgMods
{
    class PNH_Core
    {
        dir = "PNH_Core";
        picture = "";
        action = "";
        hideName = 0;
        hidePicture = 1;
        name = "PNH Core System";
        credits = "PNH Team";
        author = "PNH Team";
        authorID = "0"; 
        version = "2.0"; 
        extra = 0;
        type = "mod";
        
        // Define as dependências internas (Script Module)
        dependencies[] = { "Game", "World", "Mission" };

        // Carregamento modular (O Segredo da Organização)
        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = { "PNH_Core/Scripts/3_Game" };
            };
            class worldScriptModule
            {
                value = "";
                files[] = { "PNH_Core/Scripts/4_World" };
            };
            class missionScriptModule
            {
                value = "";
                files[] = { "PNH_Core/Scripts/5_Mission" };
            };
        };
    };
};