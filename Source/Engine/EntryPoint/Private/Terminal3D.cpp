#include "Terminal3D.h"

#include "Renderer.h"
#include "ConsoleManager.h"
#include "GameObject.h"

#include <chrono>

void Terminal3D::Run()
{
    ConsoleManager::TryToInitializeConsole();

    Renderer renderer(ConsoleManager::GetScreenBufferSize());
    float x = 1;

    GameObject go;
    go.SetPosition({ 0, 0, 0 });

    while(true)
    {
        std::chrono::steady_clock::time_point frameStartTime = std::chrono::steady_clock::now();

        renderer.PreRenderTest();

        float xx = sin(x) * 100.f;
        float yy = sin(x + PI) * 100.f;

        float zz = sin(x) * 2.f - 3.7f;
        float zzz = sin(x + PI) * 2.f - 3.7f;

        go.SetRotation(go.GetRotation().RotateByAngleAxis({0, 1, 0}, 0.007f));

        Vector3DF vv3D1[] = { Vector3DF(-4, -3, 0), Vector3DF(4, -3, 0), Vector3DF(4, 2, 0) };
        Vector3DF vv3D2[] = { Vector3DF(4, -3, 0), Vector3DF(4, 2, 0), Vector3DF(4, 2, 4) };

        if(x > 19)
        {
            x = 0;
        }

        Vector3DF vv2D1[] = { { 0,0,0 }, { 0, 30,0 }, {20, 30, 0} };

        //renderer.DrawTriangleOnScreen(vv2D1);

        renderer.DrawTriangleInWorld(go.GetTransformationMatrix(), vv3D2);
        renderer.DrawTriangleInWorld(go.GetTransformationMatrix(), vv3D1);

        x += 0.007f;

        renderer.Render();

        std::chrono::steady_clock::time_point frameEndTime = std::chrono::steady_clock::now();
        uint32_t frameElapsedTimeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - frameStartTime).count();

        if(frameElapsedTimeInMs < 17)
        {
            ConsoleManager::SleepForMilliseconds(17 - frameElapsedTimeInMs);
        }
    }
}