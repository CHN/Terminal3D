#include "Terminal3D/Renderer.h"
#include "Terminal3D/Math.h"
#include "Terminal3D/Camera.h"

#include <cstdio>
#include <sys/ioctl.h>
#include <unistd.h>
#include <memory>
#include <ncurses.h>

namespace
{
    constexpr const char* BRIGHTNESS_TABLE = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";
    constexpr float BRIGHTNESS_TABLE_LENGTH = 68.f;
    constexpr int BRIGHTNESS_TABLE_LENGTH_INT = BRIGHTNESS_TABLE_LENGTH;
}

Renderer::Renderer()
{
    AutoSetWidthAndHeightByTerminalSize();

    init();
}

Renderer::Renderer(uint32_t width, uint32_t height)
{
    m_Width = width;
    m_Height = height;

    init();
}

void Renderer::PreRenderTest()
{
    memset(m_ScreenBuffer, ' ', m_ScreenBufferSize * sizeof(std::remove_pointer<decltype(m_ScreenBuffer)>::type));
    m_ScreenBuffer[m_ScreenBufferSize - 1] = '\0';

    for(size_t i = 1; i < m_ActualHeight; ++i)
    {
        m_ScreenBuffer[i * m_ActualWidth - 1] = '\n';
    }
}

void Renderer::Render()
{
    mvaddstr(0, 0, m_ScreenBuffer);
    refresh();
}

void Renderer::DrawTriangleOnScreen(const Vector3DF vertices[3])
{
    SortVerticesIntoCache(vertices);

    auto* const v = m_TriangleRenderingCacheVertices;

    Vector3DF v4(v[0].x + (v[1].y - v[0].y) / (v[2].y - v[0].y) * (v[2].x - v[0].x), v[1].y, 0);

    float v0v4SqrDst = (v4.x - v[0].x) * (v4.x - v[0].x) + (v4.y - v[0].y) * (v4.y - v[0].y);
    float v0v2SqrDst = (v[0].x - v[2].x) * (v[0].x - v[2].x) + (v[0].y - v[2].y) * (v[0].y - v[2].y);
    v4.z = std::lerp(v[0].z, v[2].z, std::sqrtf(v0v4SqrDst / v0v2SqrDst)); 

    if(v4.x < v[1].x)
    {
        float x = v4.x;
        v4.x = v[1].x;
        v[1].x = x;
    }

    DrawBottomTriangle(v[0], v[1], v4);
    DrawTopTriangle(v[1], v4, v[2]);
}

Camera testCam = Camera(130);

void Renderer::DrawTriangleInWorld(const Vector3DF vertices[3])
{
    auto& m = testCam.GetVPMatrix();

    for(int i = 0; i < 3; ++i)
    {
        m_TriangleRenderingCacheVertices[i] = m * vertices[i];
        m_TriangleRenderingCacheVertices[i].x += m_Width * 0.5f;
        m_TriangleRenderingCacheVertices[i].y += m_Height * 0.5f;
    }

    DrawTriangleOnScreen(m_TriangleRenderingCacheVertices);
}

void Renderer::init()
{
    m_ActualWidth = m_Width;
    m_ActualHeight = m_Height + 1;

    m_DepthBufferSize = m_ActualWidth * m_ActualHeight + m_ActualHeight;
    m_DepthBuffer = new char[m_DepthBufferSize];

    m_ScreenBufferSize = m_DepthBufferSize + 1; // +1 -> null termination character
    m_ScreenBuffer = new char[m_ScreenBufferSize];
    memset(m_ScreenBuffer, ' ', m_ScreenBufferSize * sizeof(std::remove_pointer<decltype(m_ScreenBuffer)>::type));
    m_ScreenBuffer[m_ScreenBufferSize - 1] = '\0';

    for(size_t i = 1; i < m_ActualHeight; ++i)
    {
        m_ScreenBuffer[i * m_ActualWidth - 1] = '\n';
    }
}

void Renderer::AutoSetWidthAndHeightByTerminalSize()
{
    struct winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);

    m_Width = size.ws_col;
    m_Height = size.ws_row;
}

void Renderer::SortVerticesIntoCache(const Vector3DF vertices[3])
{
    constexpr size_t n = 3;

    auto& v = m_TriangleRenderingCacheVertices;

    for(size_t i = 0; i < n; ++i)
    {
        v[i].x = vertices[i].x;
        v[i].y = (int) vertices[i].y;
        v[i].z = vertices[i].z;
    }

    for (size_t i = 0; i < n-1; i++)    
    {
        for (size_t j = 0; j < n-i-1; j++)
        {
            if (v[j].y > v[j+1].y)
            {
                Vector3DF temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
            else if(v[j].y == v[j+1].y)
            {
                if(v[j].x > v[j+1].x)
                {
                    Vector3DF temp = v[j];
                    v[j] = v[j+1];
                    v[j+1] = temp;
                }
            }
        }
    }
}

void Renderer::DrawTopTriangle(const Vector3DF& v1, const Vector3DF& v2, const Vector3DF& v3)
{
    float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
    float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

    float curx1 = v3.x;
    float curx2 = v3.x;

    for (size_t scanlineY = v3.y; scanlineY > v1.y; --scanlineY)
    {
        for (size_t i = curx1; i < curx2; ++i)
        {
            if(i >= m_ActualWidth)
            {
                break;
            }

            m_ScreenBuffer[i + scanlineY * m_ActualWidth] = CalculateDepth(i, scanlineY, v1, v2, v3);
        }

        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}

void Renderer::DrawBottomTriangle(const Vector3DF& v1, const Vector3DF& v2, const Vector3DF& v3)
{
    float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
    float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

    float curx1 = v1.x;
    float curx2 = v1.x;

    for (size_t scanlineY = v1.y; scanlineY <= v2.y; ++scanlineY)
    {
        for (size_t i = curx1; i < curx2; ++i)
        {
            if(i >= m_ActualWidth)
            {
                break;
            }

            m_ScreenBuffer[i + scanlineY * m_ActualWidth] = CalculateDepth(i, scanlineY, v1, v2, v3);
        }
        
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

char Renderer::CalculateDepth(const size_t sX, const size_t sY, const Vector3DF& v1, const Vector3DF& v2, const Vector3DF& v3)
{   
    float v1XDiff = sX - v1.x;
    float v1YDiff = sY - v1.y;

    float v2XDiff = sX - v2.x;
    float v2YDiff = sY - v2.y;

    float v3XDiff = sX - v3.x;
    float v3YDiff = sY - v3.y;

    float invDstV1 = 1.f / std::sqrtf(v1XDiff * v1XDiff + v1YDiff * v1YDiff);
    float invDstV2 = 1.f / std::sqrtf(v2XDiff * v2XDiff + v2YDiff * v2YDiff);
    float invDstV3 = 1.f / std::sqrtf(v3XDiff * v3XDiff + v3YDiff * v3YDiff);

    float lerpZ = (invDstV1 * v1.z + invDstV2 * v2.z + invDstV3 * v3.z) / (invDstV1 + invDstV2 + invDstV3);

    float n = 0.5f;
    float f = 20.f;

    int index = lerpZ / (f - n) * BRIGHTNESS_TABLE_LENGTH;
    index = std::max(0, std::min(index, BRIGHTNESS_TABLE_LENGTH_INT));

    return BRIGHTNESS_TABLE[index];
}
