pthread_mutex_t advisor_mutex_start = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t advisor_mutex_advise = PTHREAD_MUTEX_INITIALIZER;
unsigned long advisor_memory_advise_count;

#define INSPECTOR_ADVISOR_LEVEL INSPECTOR_POKEMON_SUB_LEVEL
#define INSPECTOR_ADVISOR_SUB_LEVEL INSPECTOR_ADVISOR_LEVEL INSPECTOR_SUB_LEVEL
#define INSPECTOR_ADVISOR_SUB_SUB_LEVEL INSPECTOR_ADVISOR_SUB_LEVEL INSPECTOR_SUB_LEVEL


void advisor_sigterm(int code)
{
    PRINTN_FUNCTION("POKEMON -> ADVISOR", "main", "", INSPECTOR_RUN, INSPECTOR_ADVISOR_SUB_LEVEL);
    FORMAT_COUNTER(advisor_memory_advise_count)
    char line[100];
    sprintf(line, "ADVISOR:%s memory advise\n", number);
    PRINTN_PROGRESSION(line);
    PRINTN_FUNCTION("POKEMON -> ADVISOR", "main", "", INSPECTOR_END, INSPECTOR_ADVISOR_SUB_LEVEL);
    PRINTN_PROCESS("POKEMON -> ADVISOR", INSPECTOR_END, INSPECTOR_ADVISOR_LEVEL)
    exit(0);
}

void *advise_kernel(void *interval)
{
    PRINTN_INFINITE_FUNCTION("POKEMON -> ADVISOR", "advisor", "", INSPECTOR_RUN, INSPECTOR_ADVISOR_SUB_LEVEL)
    pthread_mutex_unlock(&advisor_mutex_start);
    while (1)
    {
        usleep((long)interval);
        madvise(
            common_passwd_file_memory_mapping,
            ETC_PASSWD_ROOT_LINE_LENGTH,
            MADV_DONTNEED);
        advisor_memory_advise_count++;
    }
    PRINTN_INFINITE_FUNCTION("POKEMON -> ADVISOR", "advisor", "", INSPECTOR_END, INSPECTOR_ADVISOR_SUB_LEVEL)
}

void advisor_setup(long advisor_interval)
{
    PRINTN_FUNCTION("POKEMON -> ADVISOR", "main", "", INSPECTOR_RUN, INSPECTOR_ADVISOR_SUB_LEVEL);
    signal(SIGTERM, &advisor_sigterm);
    pthread_mutex_lock(&advisor_mutex_start);
    pthread_t thread;
    pthread_create(
        &thread,
        NULL,
        advise_kernel,
        (void *)advisor_interval);
    PRINTN_THREAD("POKEMON -> ADVISOR", "advisor", INSPECTOR_RUN, INSPECTOR_ADVISOR_LEVEL);
    // wait that the thread is running to start pokemon's race
    pthread_mutex_lock(&advisor_mutex_start);
    ptrace(PTRACE_TRACEME);
    // said I am ready to pokemon (observer processus)
    raise(SIGTRAP);
    pthread_join(thread, NULL);
    PRINTN_FUNCTION("POKEMON -> ADVISOR", "main", "", INSPECTOR_RUN, INSPECTOR_ADVISOR_SUB_LEVEL);
}
