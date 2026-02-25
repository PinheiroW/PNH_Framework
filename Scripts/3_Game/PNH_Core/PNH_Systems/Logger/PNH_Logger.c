/*
    MOD: PNH_Core
    FILE: PNH_Logger.c
    DESC: Sistema de Log avançado que escreve em arquivos .log separados por dia.
*/

class PNH_Logger
{
    private static const string LOG_FOLDER = "$profile:PNH_Logs/";

    static void Init()
    {
        if (!FileExist(LOG_FOLDER))
        {
            MakeDirectory(LOG_FOLDER);
        }
    }

    /**
     * @brief Escreve uma mensagem de log.
     * @param module: O nome do sistema (ex: "Trader", "Admin", "Core")
     * @param message: A mensagem
     */
    static void Log(string module, string message)
    {
        string time = GetDate();
        string formattedMsg = string.Format("[%1] [%2] :: %3", time, module, message);

        // 1. Escreve no console do servidor (script.log)
        Print("[PNH] " + formattedMsg);

        // 2. Escreve no arquivo de log persistente
        string fileName = "PNH_" + GetDateShort() + ".log";
        FileHandle file = OpenFile(LOG_FOLDER + fileName, FileMode.APPEND);
        
        if (file != 0)
        {
            FPrintln(file, formattedMsg);
            CloseFile(file);
        }
    }

    // Atalho para logs de erro
    static void Error(string module, string message)
    {
        Log("ERROR|" + module, message);
    }

    // Atalho para logs de debug (só aparecem se #define PNH_DEBUG estiver ativo)
    static void Debug(string module, string message)
    {
        #ifdef PNH_DEBUG
        Log("DEBUG|" + module, message);
        #endif
    }

    // --- Auxiliares de Data ---
    private static string GetDate()
    {
        int year, month, day, hour, minute, second;
        GetHourMinuteSecondUTC(hour, minute, second);
        GetYearMonthDayUTC(year, month, day);
        return string.Format("%1-%2-%3 %4:%5:%6", year.ToString(), month.ToString(), day.ToString(), hour.ToString(), minute.ToString(), second.ToString());
    }

    private static string GetDateShort()
    {
        int year, month, day;
        GetYearMonthDayUTC(year, month, day);
        return string.Format("%1-%2-%3", year.ToString(), month.ToString(), day.ToString());
    }
}