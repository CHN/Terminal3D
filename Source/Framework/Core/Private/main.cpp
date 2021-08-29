#include "Terminal3DConfig.h"
#include "Terminal3D.h"

int main(size_t arg1, char** arg2)
{
    auto* program = new Terminal3D();
    program->Run();
    delete program;

    return 0;
}