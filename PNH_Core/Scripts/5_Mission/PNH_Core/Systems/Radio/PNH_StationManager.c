/**
 * MOD: PNH_Core
 * FILE: PNH_StationManager.c
 * DESC: Gerencia as estações de rádio FM no lado do Servidor.
 */

class PNH_StationManager 
{
	ref array<ref RadioStation> m_Stations;
	ref Timer m_BroadcastTimer;
	ref PassiveRadioConfig m_Config;

	// CAMINHOS CORRIGIDOS PARA O FRAMEWORK PNH
	const string RADIO_JSON_FOLDER = "$profile:PNH\\Radio\\";
	const string RADIO_JSON_PATH   = "$profile:PNH\\Radio\\RadioStations.json";
	const string RADIO_CONFIG_PATH = "$profile:PNH\\Radio\\RadioConfig.json";

	void PNH_StationManager() 
	{
		m_Stations = new array<ref RadioStation>();
		EnsureRadioJsonExists();
		LoadStations();
		LoadConfig();
		
		m_BroadcastTimer = new Timer(CALL_CATEGORY_GAMEPLAY);
		// Inicia o loop de transmissão baseado no intervalo configurado (padrão 10s)
		m_BroadcastTimer.Run(m_Config.BroadcastInterval, this, "BroadcastStations", NULL, true);
		
		PNH_Logger.Log("Radio", "Gerenciador de Estacoes PNH iniciado em: " + RADIO_JSON_FOLDER);
	}

	void EnsureRadioJsonExists() 
	{
		if (!FileExist(RADIO_JSON_FOLDER))
			MakeDirectory(RADIO_JSON_FOLDER);

		if (!FileExist(RADIO_JSON_PATH)) 
		{
			ref array<ref RadioStation> dummyStations = new array<ref RadioStation>();
			// Cria estações padrão de 85 a 120 MHz
			for (int freq = 85; freq <= 120; freq++) 
			{
				ref RadioStation station = new RadioStation;
				station.Frequency = freq;
				station.Playlist = new array<ref RadioSong>();
				
				ref RadioSong dummy = new RadioSong;
				dummy.SoundSet = "PublicRadio_Dummy_SoundSet";
				dummy.Length = 60;
				station.Playlist.Insert(dummy);
				
				dummyStations.Insert(station);
			}
			JsonFileLoader<array<ref RadioStation>>.JsonSaveFile(RADIO_JSON_PATH, dummyStations);
		}
	}

	void LoadStations() 
	{
		if (!FileExist(RADIO_JSON_PATH)) return;
		JsonFileLoader<array<ref RadioStation>>.JsonLoadFile(RADIO_JSON_PATH, m_Stations);
		
		foreach (RadioStation station : m_Stations) 
		{
			station.m_CurrentIndex = 0;
			station.m_CurrentSong = null;
			station.m_CurrentSongTimeRemaining = 0;
		}
	}

	void LoadConfig() 
	{
		m_Config = new PassiveRadioConfig();
		if (FileExist(RADIO_CONFIG_PATH)) 
		{
			JsonFileLoader<PassiveRadioConfig>.JsonLoadFile(RADIO_CONFIG_PATH, m_Config);
		}
		else 
		{
			JsonFileLoader<PassiveRadioConfig>.JsonSaveFile(RADIO_CONFIG_PATH, m_Config);
		}

		if (m_Config.BroadcastInterval <= 0)
			m_Config.BroadcastInterval = 10;
	}

	void BroadcastStations() 
	{
		array<Man> players = new array<Man>();
		GetGame().GetPlayers(players);

		foreach (RadioStation station : m_Stations) 
		{
			station.Tick(m_Config.BroadcastInterval);
			RadioSong currentSong = station.GetCurrentSong();

			if (currentSong)
			{
				foreach (Man man : players) 
				{
					PlayerBase pb = PlayerBase.Cast(man);
					if (!pb || !pb.GetIdentity()) continue;

					// Envia a informação da música para os jogadores (RPC 9995 definida no PNH_Defines)
					auto params = new Param3<float, string, string>(station.Frequency, currentSong.SoundSet, currentSong.SoundSet);
					GetGame().RPCSingleParam(pb, 9995, params, true, pb.GetIdentity());
				}
			}
		}
	}
}

// Configuração auxiliar para o intervalo de tempo
class PassiveRadioConfig 
{
	int BroadcastInterval = 10;
}