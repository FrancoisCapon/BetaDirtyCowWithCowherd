#define INSPECTOR_OUT stderr
#define INSPECTOR_OUT_NEWLINE() fprintf(INSPECTOR_OUT, "\n");

#define INSPECTOR_RUN  FORE_GREEN "● run " FORE_RESET
#define INSPECTOR_END FORE_CYAN "● end " FORE_RESET

#define INSPECTOR_LEVEL_ONE ""
#define INSPECTOR_SUB_LEVEL "⚬ "

#define PRINT_PROCESS(process, state, level)            \
    PRINT_TIME_KEEPING(INSPECTOR_OUT, FORE_BLUE) \
    fprintf(INSPECTOR_OUT, level state "process[" FORE_GREEN "%s" FORE_RESET "]", process);

#define PRINTN_PROCESS(process, state, level) \
    PRINTN_THREAD(process, "main", state, level)

#define PRINT_THREAD(process, thread, state, level) \
    PRINT_PROCESS(process, state, level)            \
    fprintf(INSPECTOR_OUT, " >> thread[" FORE_GREEN "%s" FORE_RESET "]", thread);
#define PRINTN_THREAD(process, thread, state, level) \
    PRINT_THREAD(process, thread, state, level)      \
    INSPECTOR_OUT_NEWLINE()

#define PRINT_FUNCTION(process, thread, functions, state, level) \
    PRINT_THREAD(process, thread, state, level)                  \
    fprintf(INSPECTOR_OUT, " >>> function[" FORE_YELLOW "%s%s" FORE_RESET "]", functions, __func__);
#define PRINTN_FUNCTION(process, thread, functions, state, level) \
    PRINT_FUNCTION(process, thread, functions, state, level)      \
    INSPECTOR_OUT_NEWLINE()

#define PRINTN_INFINITE_FUNCTION(process, thread, functions, state, level) \
    PRINT_FUNCTION(process, thread, functions, state, level)               \
    fprintf(INSPECTOR_OUT, "🐮🔄");                            \
    INSPECTOR_OUT_NEWLINE()

// 🔁 🔄 🐮 🏎️ 🎠 🛑 ↩️ ⬇️ ⏺ 🔽 🔁 🟢 🔴 ❌ ✅ ● 🎯 ⚬
