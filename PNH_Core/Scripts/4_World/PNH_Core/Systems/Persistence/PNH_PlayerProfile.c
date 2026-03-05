/**
 * MOD: PNH_Core
 * FILE: PNH_PlayerProfile.c
 * DESC: Define a estrutura de dados que será salva no JSON.
 */

class PNH_PlayerProfile
{
    string SteamID;
    string LastLoginDate;
    int JoinCount;
    bool IsRadioMuted;

    // Construtor vazio (Necessário para o serializador JSON do DayZ)
    void PNH_PlayerProfile() {}

    // Configuração inicial para novos jogadores
    void Initialize(string id)
    {
        SteamID = id;
        JoinCount = 0;
        IsRadioMuted = false;
        UpdateLoginDate();
    }

    // Atualiza a data para o momento atual
    void UpdateLoginDate()
    {
        int year, month, day, hour, minute;
        GetHourMinuteSecondUTC(hour, minute, day);
        GetYearMonthDayUTC(year, month, day);
        LastLoginDate = "" + day + "/" + month + "/" + year + " " + hour + ":" + minute;
    }
}