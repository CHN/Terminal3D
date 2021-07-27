#include "Terminal3DConfig.h"
#include "Terminal3D.h"

#include <csignal>
#include <cstdio>
#include <curses.h>
#include <cstdlib>

void HandleAbortSignal(int signum)
{
    addstr("\rProgram aborted, press any key to close!");

    for(;;)
    {
        if(getch() != ERR)
        {
            break;
        }
    }
}

int main()
{
    signal(SIGABRT, HandleAbortSignal);

    (new Terminal3D())->Run();

    return 0;
}