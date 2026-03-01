class CfgPatches
{
	class DI_PublicRadio_Receivers
	{
		units[]=
		{
			"skaerheim_radioreceiver_01"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"di_publicradio"
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class skaerheim_radioreceiver_base: Inventory_Base
	{
		scope=0;
		displayName="FM Radio";
		descriptionShort="";
		model="DI_PublicRadio\receivers\skaerheim_fmradio.p3d";
		itemSize[]={1,2};
		rotationFlags=16;
		weight=100;
		hiddenSelections[]=
		{
			"camoGround"
		};
		inventorySlot[]=
		{
			"Chemlight",
			"WalkieTalkie",
			"cabin_radio_slot"
		};
		hiddenSelectionsTextures[]=
		{
			"DI_PublicRadio\receivers\data\radio_low_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"DI_PublicRadio\receivers\data\radio_low.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							{}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							{}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							{}
						}
					};
				};
			};
		};
		class AnimationSources
		{
			class Rotate_Antenna
			{
				source="user";
				initPhase=0;
				animPeriod=0.5;
			};
		};
	};
	class skaerheim_radioreceiver_01: skaerheim_radioreceiver_base
	{
		scope=2;
		hiddenSelectionsTextures[]=
		{
			"DI_PublicRadio\receivers\data\radio_low_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"DI_PublicRadio\receivers\data\radio_low.rvmat"
		};
	};
};
