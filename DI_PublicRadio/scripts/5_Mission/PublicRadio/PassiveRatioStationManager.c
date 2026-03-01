class PassiveRadioConfig {
	int BroadcastInterval = 30;
}
class PassiveRadioStationManager {
	ref array<ref RadioStation> m_Stations;
	ref Timer m_BroadcastTimer;
	ref PassiveRadioConfig m_Config;
	const string RADIO_JSON_FOLDER = "$profile:PublicRadio\\";
	const string RADIO_JSON_PATH = "$profile:PublicRadio\\RadioStations.json";
	const string RADIO_CONFIG_PATH = "$profile:PublicRadio\\RadioConfig.json";
	void PassiveRadioStationManager() {
		m_Stations = new array<ref RadioStation>();
		EnsureRadioJsonExists();
		LoadStations();
		LoadConfig();
		m_BroadcastTimer = new Timer(CALL_CATEGORY_GAMEPLAY);
		m_BroadcastTimer.Run(m_Config.BroadcastInterval, this, "BroadcastStations", NULL, true);
	}
	void EnsureRadioJsonExists() {
		if (!FileExist(RADIO_JSON_FOLDER))
			MakeDirectory(RADIO_JSON_FOLDER);
		if (!FileExist(RADIO_JSON_PATH)) {
			ref array<ref RadioStation> dummyStations = new array<ref RadioStation>();
			for (int freq = 85; freq <= 120; freq++) {
				ref RadioStation station = new RadioStation;
				station.Frequency = freq;
				station.Playlist = new array<ref RadioSong>();
				ref RadioSong dummy = new RadioSong;
				dummy.SoundSet = "PublicRadio_Dummy_SoundSet";
				dummy.Length = 360;
				dummy.SongName = "";
				station.Playlist.Insert(dummy);
				dummyStations.Insert(station);
			}
			FileHandle file = OpenFile(RADIO_JSON_PATH, FileMode.WRITE);
			if (file != 0) {
				FPrintln(file, "[");
				for (int i = 0; i < dummyStations.Count(); i++) {
					RadioStation s = dummyStations[i];
					FPrintln(file, "    {");
					FPrintln(file, "        \"Frequency\": " + (int)s.Frequency + ",");
					FPrintln(file, "        \"Playlist\": [");

					for (int j = 0; j < s.Playlist.Count(); j++) {
						RadioSong song = s.Playlist[j];
						FPrint(file, "            {");
						FPrint(file, "\"SoundSet\": \"" + song.SoundSet + "\", ");
						FPrint(file, "\"Length\": " + song.Length + ", ");
						FPrint(file, "\"SongName\": \"" + song.SongName + "\"");
						FPrint(file, "}");
						if (j < s.Playlist.Count() - 1)
							FPrintln(file, ",");
						else FPrintln(file, "");
					}
					FPrint(file, "        ]\n    }");
					if (i < dummyStations.Count() - 1)
						FPrintln(file, ",");
					else FPrintln(file, "");
				}
				FPrintln(file, "]");
				CloseFile(file);
			}
		}
		if (!FileExist(RADIO_CONFIG_PATH)) {
			ref PassiveRadioConfig defaultConfig = new PassiveRadioConfig();
			JsonFileLoader<PassiveRadioConfig>.JsonSaveFile(RADIO_CONFIG_PATH, defaultConfig);
		}
	}
	void LoadStations() {
		if (!FileExist(RADIO_JSON_PATH)) return;
		JsonFileLoader<array<ref RadioStation>>.JsonLoadFile(RADIO_JSON_PATH, m_Stations);
		foreach (RadioStation station : m_Stations) {
			station.m_CurrentIndex = 0;
			station.m_CurrentSong = null;
			station.m_CurrentSongTimeRemaining = 0;
		}
	}

	void LoadConfig() {
		if (!FileExist(RADIO_CONFIG_PATH)) {
			m_Config = new PassiveRadioConfig();
			return;
		}
		m_Config = new PassiveRadioConfig();
		JsonFileLoader<PassiveRadioConfig>.JsonLoadFile(RADIO_CONFIG_PATH, m_Config);
		if (m_Config.BroadcastInterval <= 0)
			m_Config.BroadcastInterval = 10;
	}
	void BroadcastStations() {
		array<Man> players = new array<Man>();
		GetGame().GetPlayers(players);
		foreach (RadioStation station : m_Stations) {
			station.Tick(m_Config.BroadcastInterval);
			RadioSong currentSong = station.GetCurrentSong();
			foreach (Man man : players) {
				PlayerBase pb;
				if (!Class.CastTo(pb, man)) continue;
				ref Param4<float, string, int, string> data;
				if (!currentSong) {
					data = new Param4<float, string, int, string>(station.Frequency, "", 0, "");
				} else {
					data = new Param4<float, string, int, string>(station.Frequency, currentSong.SoundSet, currentSong.Length, currentSong.SongName);
				}
				GetGame().RPCSingleParam(pb, RPC_SKAERHEIM_PUBLIC_RADIO_BROADCAST, data, true, pb.GetIdentity());
			}
		}
	}
	array<ref RadioStation> GetStations() { return m_Stations; }
}
