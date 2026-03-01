class CfgPatches
{
	class GPS_Tablet
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Characters",
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class GPS_Tablet
	{
		dir="GPS_Tablet";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="GPS_Tablet";
		author="n1nj4";
		version="1.0";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"GPS_Tablet/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"GPS_Tablet/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"GPS_Tablet/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{
	class Clothing_Base;
	class Clothing: Clothing_Base
	{
	};
	class GPS_Tablet_ColorBase: Clothing
	{
		scope=0;
		displayName="Satellite GPS Tablet";
		descriptionShort="A wearable satellite GPS tablet.";
		model="\GPS_Tablet\data\tab2_g.p3d";
		inventorySlot[]=
		{
			"Armband"
		};
		itemInfo[]=
		{
			"Clothing",
			"Armband"
		};
		animClass="ItemPDA";
		rotationFlags=34;
		weight=500;
		itemSize[]={2,3};
		attachments[]=
		{
			"BatteryD"
		};
		class ClothingTypes
		{
			male="\GPS_Tablet\data\tab2_m.p3d";
			female="\GPS_Tablet\data\tab2_f.p3d";
		};
		class EnergyManager
		{
			hasIcon=1;
			autoSwitchOff=1;
			energyUsagePerSecond=0.0099999998;
			plugType=1;
			attachmentAction=1;
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=350;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"GPS_Tablet\data\textures\tab2.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"GPS_Tablet\data\textures\tab2.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"GPS_Tablet\data\textures\tab2_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"GPS_Tablet\data\textures\tab2_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"GPS_Tablet\data\textures\tab2_destruct.rvmat"
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0.80000001;
					};
					class Blood
					{
						damage=0.40000001;
					};
					class Shock
					{
						damage=0.80000001;
					};
				};
				class Melee
				{
					class Health
					{
						damage=0.80000001;
					};
					class Blood
					{
						damage=0.40000001;
					};
					class Shock
					{
						damage=0.80000001;
					};
				};
				class Infected
				{
					class Health
					{
						damage=0.80000001;
					};
					class Blood
					{
						damage=0.40000001;
					};
					class Shock
					{
						damage=0.80000001;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0.80000001;
					};
					class Blood
					{
						damage=0.40000001;
					};
					class Shock
					{
						damage=0.80000001;
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="Shirt_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="Shirt_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class GPS_Tablet_Black: GPS_Tablet_ColorBase
	{
		scope=2;
		hiddenSelections[]=
		{
			"lcd_1",
			"lcd_2",
			"zbytek"
		};
		hiddenSelectionsTextures[]=
		{
			"GPS_Tablet\data\textures\hardware_display.edds",
			"GPS_Tablet\data\textures\hardware_display.edds",
			"GPS_Tablet\data\textures\tab2_co.paa"
		};
	};
};
