#pragma once

#include "Math.h"

#include <cstdint>

class Renderer
{
public:
    Renderer(Vector2DI screenSize);
    void PreRenderTest();
    void Render();
    void DrawTriangleOnScreen(const Vector3DF vertices[3]);
    void DrawTriangleInWorld(const Vector3DF vertices[3]);

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }
    const char* GetScreenBuffer() const { return m_ScreenBuffer; }
    uint32_t GetScreenBufferSize() const { return m_ScreenBufferSize; }

private:
    uint32_t m_Width;
    uint32_t m_Height;
    uint32_t m_ActualWidth;
    uint32_t m_ActualHeight;

    uint32_t m_ScreenBufferSize;
    uint32_t m_DepthBufferSize;

    char* m_ScreenBuffer;
    char* m_DepthBuffer;

    void init();
    void AutoSetWidthAndHeightByTerminalSize();

    void SortVerticesIntoCache(const Vector3DF vertices[3]);
    void DrawTopTriangle(const Vector3DF& v1, const Vector3DF& v2, const Vector3DF& v3);
    void DrawBottomTriangle(const Vector3DF& v1, const Vector3DF& v2, const Vector3DF& v3);

    char CalculateDepth(const size_t sX, const size_t sY, const Vector3DF& v1, const Vector3DF& v2, const Vector3DF& v3);

    Vector3DF m_TriangleRenderingCacheVertices[3];
};