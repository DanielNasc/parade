// get the OS name

#if _WIN32 || _WIN64
#define OS_NAME "Windows"
#elif __linux__
#define OS_NAME "Linux"
#elif __APPLE__ || __MACH__
#define OS_NAME "Mac OSX"
#elif __unix__
#define OS_NAME "Unix"
#else
#define OS_NAME "Unknown"
#endif