// https://www.cs.toronto.edu/~arnold/427/18s/427_18S/indepth/dirty-cow/index.html
// https://www.cs.toronto.edu/~arnold/427/18s/427_18S/indepth/dirty-cow/demo.html

// standard librairies
#include "macros_librairies.c"

// librairies
#include "library_timekepping.c"
// macros
#include "macros.c"

static void main_setup();

void *common_passwd_file_memory_mapping;

// actors (processus)
#include "actor_pokemon.c"
#include "actor_advisor.c"

int main(int argc, char *argv[]) // race_length race_interval advisor_interval
{
    if (argc != 4)
    {
        printf("\n⛔ usage: build_name race_length race_interval advisor_interval\n\n");
        exit(1);
    }
    main_setup();
    int fork_value = fork();
    if (fork_value)
    {
        PRINTN_PROCESS("POKEMON (MAIN is now POKEMON)", INSPECTOR_RUN, INSPECTOR_POKEMON_LEVEL)
        pokemon_setup(fork_value);
        pokemon_run(fork_value, atoi(argv[1]), atoi(argv[2]));
    }
    else
    {
        PRINTN_PROCESS("COWHERD -> ADVISOR", INSPECTOR_RUN, INSPECTOR_ADVISOR_LEVEL)
        advisor_setup(atoi(argv[2]));
    }
}

#define INSPECTOR_MAIN_LEVEL INSPECTOR_POKEMON_LEVEL
#define INSPECTOR_MAIN_SUB_LEVEL INSPECTOR_POKEMON_SUB_LEVEL
#define INSPECTOR_MAIN_SUB_SUB_LEVEL INSPECTOR_POKEMON_SUB_SUB_LEVEL

void main_backup_passwd_file()
{
    PRINTN_FUNCTION("MAIN", "main", "main_setup -> ", INSPECTOR_RUN, INSPECTOR_MAIN_SUB_SUB_LEVEL);
    // echo "/tmp/passwd.1666539874" | wc -c => 23
    char backup_filename[23];
    sprintf(backup_filename, "/tmp/passwd.%u", time(NULL));
    char copy_command[40] = "cp /etc/passwd ";
    strcat(copy_command, backup_filename);
    system(copy_command);
    PRINTN_FUNCTION("MAIN", "main", "main_setup -> ", INSPECTOR_END, INSPECTOR_MAIN_SUB_SUB_LEVEL);
}

void main_map_passwd_file_to_memory()
{
    PRINTN_FUNCTION("MAIN", "main", "main_setup -> ", INSPECTOR_RUN, INSPECTOR_MAIN_SUB_SUB_LEVEL);
    int file_descriptor;
    file_descriptor = open("/etc/passwd", O_RDONLY);

    struct stat informations;
    fstat(file_descriptor, &informations);

    common_passwd_file_memory_mapping = mmap(
        NULL,
        informations.st_size,
        PROT_READ,
        MAP_PRIVATE,
        file_descriptor,
        0);
    PRINTN_FUNCTION("MAIN", "main", "main_setup -> ", INSPECTOR_END, INSPECTOR_MAIN_SUB_SUB_LEVEL);
}

void main_setup()
{
    timekeeping_init();
    setvbuf(PROGRESSION_OUT, NULL, _IONBF, 0);
    setvbuf(INSPECTOR_OUT, NULL, _IONBF, 0);
    printf("\n");
    PRINTN_PROCESS("MAIN", INSPECTOR_RUN, INSPECTOR_MAIN_LEVEL)
    PRINTN_FUNCTION("MAIN", "main", "", INSPECTOR_RUN, INSPECTOR_MAIN_SUB_LEVEL)
    main_backup_passwd_file();
    main_map_passwd_file_to_memory();
    PRINTN_FUNCTION("MAIN", "main", "main_setup -> ", INSPECTOR_END, INSPECTOR_MAIN_SUB_LEVEL);
}
