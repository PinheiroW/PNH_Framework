class CfgPatches
{
	class DI_PublicRadio
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class DI_PublicRadio
	{
		dir="DI_PublicRadio";
		hideName=1;
		hidePicture=1;
		name="di_publicradio";
		author="Skaerheim + TankROG";
		action="";
		inputs="DI_PublicRadio\scripts\Inputs.xml";
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
				files[]=
				{
					"DI_PublicRadio/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				files[]=
				{
					"DI_PublicRadio/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				files[]=
				{
					"DI_PublicRadio/scripts/5_Mission"
				};
			};
		};
		defines[]=
		{
			"SKAERHEIM_PUBLICRADIO"
		};
	};
};
class CfgSoundShaders
{
	class PublicRadio_SoundShader_Base
	{
		volume=1;
		range=50;
	};
	class PublicRadio_Dummy_SoundShader: PublicRadio_SoundShader_Base
	{
		samples[]=
		{
			
			{
				"dummy_soundset",
				1
			}
		};
		volume=1;
		range=1;
	};
	class PublicRadio_Ezra_SoundShader: PublicRadio_SoundShader_Base
	{
		samples[]=
		{
			
			{
				"di_publicradio\sounds\ezra_broadcast",
				1
			}
		};
	};
	class PublicRadio_Jax_SoundShader: PublicRadio_SoundShader_Base
	{
		samples[]=
		{
			
			{
				"di_publicradio\sounds\jax_broadcast",
				1
			}
		};
	};
	class PublicRadio_Static_SoundShader: PublicRadio_SoundShader_Base
	{
		samples[]=
		{
			
			{
				"di_publicradio\sounds\jax_broadcast",
				1
			}
		};
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
		soundShaders[]=
		{
			"PublicRadio_Dummy_SoundShader"
		};
	};
	class PublicRadio_Ezra_SoundSet: PublicRadio_SoundSet_Base
	{
		soundShaders[]=
		{
			"PublicRadio_Ezra_SoundShader"
		};
	};
	class PublicRadio_Jax_SoundSet: PublicRadio_SoundSet_Base
	{
		soundShaders[]=
		{
			"PublicRadio_Jax_SoundShader"
		};
	};
};
