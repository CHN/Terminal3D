#include "Terminal3D.h"

#include "Terminal3D/Renderer.h"

#include <chrono>
#include <unistd.h>
#include <cmath>
#include <ncurses.h>

void Terminal3D::Run()
{
    system("printf '\033c'");
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    refresh();

    Renderer renderer;
    float x=0,y=0;
    float x1 = 50, y1 = 10;
    float z = 10;
    float z1 = 7;

    float v2F = M_PI / 3.f;
    float v3F = M_PI / 3.f * 2.f;

    while(true)
    {
        std::chrono::steady_clock::time_point frameStartTime = std::chrono::steady_clock::now();

        renderer.PreRenderTest();

        Vector3DF v1(cos(x) * z + x1, sin(y) * z1 + y1, 0);
        Vector3DF v2(cos(x + v2F) * z + x1, sin(y + v2F) * z1 + y1, 0);
        Vector3DF v3(cos(x + v3F) * z + x1, sin(y + v3F) * z1 + y1, 0);

        Vector3DF vv[] = { v1, v2, v3 };
        Vector3DF vv2[] = { Vector3DF(2, 2, 0), Vector3DF(20, 2, 0), Vector3DF(20, 20, 0) };
        Vector3DF vv3[] = { Vector3DF(2, 2, 0), Vector3DF(2, 20, 0), Vector3DF(20, 20, 0) };
        //renderer.DrawTriangleOnScreen(vv2);
        //renderer.DrawTriangleOnScreen(vv3);

        //renderer.DrawTriangleOnScreen(vv);

        float z = -2.5f - cos(x);
        float xx = sin(x) * 50.f;
        Vector3DF vv3D1[] = { Vector3DF(-150, -35, -1 - x), Vector3DF(150, -35, -1 - x), Vector3DF(140, 35, -1.f) };

        if(x > 19)
        {
            x = 0;
        }

        renderer.DrawTriangleInWorld(vv3D1);

        x += 0.0007f;
        y += 0.000f;

        renderer.Render();

        std::chrono::steady_clock::time_point frameEndTime = std::chrono::steady_clock::now();
        uint32_t frameElapsedTimeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - frameStartTime).count();

        if(frameElapsedTimeInMs < 17)
        {
            usleep(17 - frameElapsedTimeInMs);
        }
    }
}