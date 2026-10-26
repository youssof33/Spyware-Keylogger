#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
	// 1. Dah bey5aly el timezone bta3 el system yeb2a Africa/Cairo, bas howa me4 dakeek elsara7a
    _putenv_s("TZ", "Africa/Cairo");
    _tzset();

	// 2. Bena3mel log file w keylogger file
    char* log_file = "c2_exfil.log";
    char* keylog_file = "keylog.txt";

	// 3. Bengeeb el current time w ne7otoh fel log
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char time_string[64];
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", t);

	// 4. Bene3mel log 3ala el start bta3 el spyware
    FILE* event_log = fopen(log_file, "a");
    if (event_log != NULL) {
        fprintf(event_log, "[%s] [START] Spyware simulation started\n", time_string);
        fclose(event_log);
    }

	// 5. Dah el spyware simulation, we ask the user to type something and we log it
    printf("=== Spyware Simulation ===\n");
    printf("Type a fake password or message: ");

    char user_input[100];

	// Bete2ra eh el user katabo w te7otoh fel keylog file
    fgets(user_input, sizeof(user_input), stdin);

	// Bete3mel log lel input bta3 el user
    FILE* keylog = fopen(keylog_file, "a");
    if (keylog != NULL) {
        fprintf(keylog, "[%s] Captured: %s", time_string, user_input);
        fclose(keylog);
    }

	// 6. Dah el file exfiltration simulation, we pretend to steal a file and log it
    FILE* file_log = fopen(log_file, "a");
    if (file_log != NULL) {
        fprintf(file_log, "[%s] [FILE] Stole target_docs/data.txt\n", time_string);
        fclose(file_log);
    }

	// 7. Dah el spyware simulation end, we log the end of the simulation and create a fake persistence marker
    FILE* finish_log = fopen(log_file, "a");
    if (finish_log != NULL) {
        fprintf(finish_log, "[%s] [EXFIL] Data sent to hacker\n", time_string);
        fprintf(finish_log, "[%s] [PERSIST] Persistence marker created\n", time_string);
        fprintf(finish_log, "[%s] [END] Spyware simulation finished\n", time_string);
        fclose(finish_log);
    }

	// Hena ben3mel fake persistence marker file
    FILE* marker = fopen(".persistence_note", "w");
    if (marker != NULL) {
        fprintf(marker, "I was here!\n");
        fclose(marker);
    }

    printf("\n[SUCCESS] Check c2_exfil.log and keylog.txt to see the results.\n");
    return 0;
}