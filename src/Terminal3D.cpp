#include "Terminal3D.h"

#include "Terminal3D/Renderer.h"

#include <chrono>

void Terminal3D::Run()
{
    Renderer renderer;
    float x = 0;

    while(true)
    {
        std::chrono::steady_clock::time_point frameStartTime = std::chrono::steady_clock::now();

        renderer.PreRenderTest();

        float xx = sin(x) * 50.f;
        Vector3DF vv3D1[] = { Vector3DF(-150, -35, -1 - x), Vector3DF(150, -35, -1 - x), Vector3DF(140, 35, -1.f) };

        if(x > 19)
        {
            x = 0;
        }

        renderer.DrawTriangleInWorld(vv3D1);

        x += 0.0007f;

        renderer.Render();

        std::chrono::steady_clock::time_point frameEndTime = std::chrono::steady_clock::now();
        uint32_t frameElapsedTimeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - frameStartTime).count();

        if(frameElapsedTimeInMs < 17)
        {
            usleep(17 - frameElapsedTimeInMs);
        }
    }
}