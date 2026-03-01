class CfgPatches
{
    class PNH_Core
    {
        units[]={"PNH_Tablet_Black"}; // Registo do nosso novo item no jogo
        weapons[]={};
        requiredVersion=0.1;
        // O Tablet precisa do Characters para as animações de mão
        requiredAddons[]={ "DZ_Data", "DZ_Scripts", "DZ_Characters" }; 
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
        
        dependencies[] = { "Game", "World", "Mission" };

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

// ==========================================
// REGISTRO DE SONS E RÁDIO
// ==========================================
class CfgSoundShaders
{
	class PublicRadio_SoundShader_Base
	{
		volume=1;
		range=50;
	};
	class PublicRadio_Dummy_SoundShader: PublicRadio_SoundShader_Base
	{
		samples[]={ {"dummy_soundset", 1} };
		volume=1;
		range=1;
	};
	class PublicRadio_Ezra_SoundShader: PublicRadio_SoundShader_Base
	{
        // CAMINHO ATUALIZADO: Aponta para a nova pasta dentro do PNH_Core
		samples[]={ {"PNH_Core\Sounds\Radio\ezra_broadcast", 1} }; 
	};
	class PublicRadio_Jax_SoundShader: PublicRadio_SoundShader_Base
	{
		samples[]={ {"PNH_Core\Sounds\Radio\jax_broadcast", 1} };
	};
	class PublicRadio_Static_SoundShader: PublicRadio_SoundShader_Base
	{
		samples[]={ {"PNH_Core\Sounds\Radio\jax_broadcast", 1} }; // Adaptação da estática
		volume=0.5;
	};
};

class CfgSoundSets
{
	class PublicRadio_SoundSet_Base
	{
		volumeCurve="InverseSquare2Curve";
		spatial=1;
		doppler=0;
		loop=0;
	};
	class PublicRadio_Dummy_SoundSet: PublicRadio_SoundSet_Base
	{
		soundShaders[]={"PublicRadio_Dummy_SoundShader"};
	};
	class PublicRadio_Ezra_SoundSet: PublicRadio_SoundSet_Base
	{
		soundShaders[]={"PublicRadio_Ezra_SoundShader"};
	};
	class PublicRadio_Jax_SoundSet: PublicRadio_SoundSet_Base
	{
		soundShaders[]={"PublicRadio_Jax_SoundShader"};
	};
};

// ==========================================
// REGISTRO DO NOVO ITEM (O TABLET HUB)
// ==========================================
class CfgVehicles
{
	class Clothing_Base;
	class Clothing: Clothing_Base {};
	
	class PNH_Tablet_ColorBase: Clothing
	{
		scope=0;
		displayName="Tablet Tático PNH";
		descriptionShort="Hub Tático multifunções: Integra Mapa GPS e Sintonia de Rádios via Bluetooth.";
        // CAMINHOS ATUALIZADOS para procurar os 3D dentro do PNH_Core
		model="\PNH_Core\Models\Tablet\data\tab2_g.p3d"; 
		inventorySlot[]={"Armband"};
		itemInfo[]={"Clothing","Armband"};
		animClass="ItemPDA";
		rotationFlags=34;
		weight=500;
		itemSize[]={2,3};
		attachments[]={"BatteryD"}; // Exige bateria
		class ClothingTypes
		{
			male="\PNH_Core\Models\Tablet\data\tab2_m.p3d";
			female="\PNH_Core\Models\Tablet\data\tab2_f.p3d";
		};
		class EnergyManager
		{
			hasIcon=1;
			autoSwitchOff=1;
			energyUsagePerSecond=0.0099999998;
			plugType=1;
			attachmentAction=1;
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem { soundSet="Shirt_pickup_SoundSet"; id=797; };
				class drop { soundset="Shirt_drop_SoundSet"; id=898; };
			};
		};
	};
    
	class PNH_Tablet_Black: PNH_Tablet_ColorBase
	{
		scope=2; // Spawna no jogo
		hiddenSelections[]={"lcd_1","lcd_2","zbytek"};
        // TEXTURAS ATUALIZADAS
		hiddenSelectionsTextures[]=
		{
			"PNH_Core\GUI\Textures\tablet.edds",
			"PNH_Core\GUI\Textures\tablet.edds",
			"PNH_Core\Models\Tablet\data\textures\tab2_co.paa"
		};
	};
};