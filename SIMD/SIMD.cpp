#include "stadfx.h"

string get_cpu_name()
{
    uint32_t data[4] = { 0 };

    _asm
    {
        cpuid;
        mov data[0], ebx;
        mov data[4], edx;
        mov data[8], ecx;
    }

    return string((const char*)data);
}

void assembler()
{
    cout << "CPU Name: " << get_cpu_name() << endl;

    float f1[] = { 1.f, 2.f, 3.f, 4.f };
    float f2[] = { 5.f, 4.f, 3.f, 2.f };
    float result[4] = { 0.f };

    _asm
    {
        movups xmm1, f1;
        movups xmm2, f2;
        mulps xmm1, xmm2;
        movups result, xmm1;
    }

    for (size_t i = 0; i < 4; i++)
    {
        cout << result[i] << "\t";
    }
    cout << endl;

    int d, c;

    _asm 
    {
        mov eax, 1;
        cpuid;
        mov d, edx;
        mov c, edx;
    }

    if ((d & (1 << 26)) != 0)
        cout << "SSE2 is supported " << endl;

    if ((c & 1) != 0)
        cout << "SSE3 is supported " << endl;

    if ((c & (1 << 19)) != 0)
        cout << "SSE4.1 is supported " << endl;

    if ((c & (1 << 20)) != 0)
        cout << "SSE4.2 is supported " << endl;
}

void intrinsics()
{
    int cpuInfo[4];
    __cpuid(cpuInfo, 1);

    auto a = _mm_set_ps(1, 2, 3, 4);
    auto b = _mm_set_ps(4, 3, 2, 1);
    auto c = _mm_add_ps(a, b);

    float f = c.m128_f32[0];

    __try 
    {
        __m256d z = _mm256_set_pd(1, 2, 3, 4);
    }
    __except (1)
    {
        cout << "Operation not supported " << endl;
    }
}

int main()
{
    intrinsics();
    //assembler();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
