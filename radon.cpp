#include <windows.h>
#define _USE_MATH_DEFINES 1
#include <cmath>
#define RGBBRUSH (DWORD)0x1900ac010e
#include <intrin.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "kernel32.lib")

DWORD xs;
VOID SeedXorshift32(DWORD dwSeed) {
    xs = dwSeed;
}
DWORD xorshift32() {
    xs ^= xs << 13;
    xs ^= xs << 17;
    xs ^= xs << 5;
    return xs;
}
DWORD WINAPI RGB2(LPVOID lpParam)
{
    HWND v3;
    HBITMAP h;
    HDC hdcSrc;
    HDC hdc;
    void* lpvBits;
    int nHeight;
    int nWidth;
    DWORD v12;
    int j;
    int v14;
    int i;
    v12 = GetTickCount();
    nWidth = GetSystemMetrics(0);
    nHeight = GetSystemMetrics(1);
    lpvBits = VirtualAlloc(0, 4 * nWidth * (nHeight + 1), 0x3000u, 4u);
    for (i = 0; ; i = (i + 1) % 2)
    {
        hdc = GetDC(0);
        hdcSrc = CreateCompatibleDC(hdc);
        h = CreateBitmap(nWidth, nHeight, 1u, 0x20u, lpvBits);
        SelectObject(hdcSrc, h);
        BitBlt(hdcSrc, 0, 0, nWidth, nHeight, hdc, 0, 0, 0xCC0020u);
        GetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        v14 = 0;
        if (GetTickCount() - v12 > 0xA)
            rand();
        for (j = 0; nHeight * nWidth > j; ++j)
        {
            if (!(j % nHeight) && !(rand() % 110))
                v14 = rand() % 24;
            *((BYTE*)lpvBits + 4 * j + v14) -= 5;
        }
        SetBitmapBits(h, 4 * nHeight * nWidth, lpvBits);
        BitBlt(hdc, 0, 0, nWidth, nHeight, hdcSrc, 0, 0, 0xCC0020u);
        DeleteObject(h);
        DeleteObject(hdcSrc);
        DeleteObject(hdc);
    }
}
DWORD WINAPI payload2(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
        SeedXorshift32(__rdtsc());
        desk = GetDC(0);
        SelectObject(desk, CreateHatchBrush(xorshift32() % 7, RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
        SelectObject(desk, CreateHatchBrush(xorshift32() % 15, RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
        Ellipse(desk, xorshift32() % sw, xorshift32() % sh, xorshift32() % sw, xorshift32() % sh);
        Rectangle(desk, xorshift32() % sw, xorshift32() % sh, xorshift32() % sw, xorshift32() % sh);
        Sleep(20);
    }
}
VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCERASE);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}
DWORD WINAPI payload3(LPVOID lpParam) {
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    int rx;
    for (int i = 0;; i++) {
        SeedXorshift32(__rdtsc());
        desk = GetDC(0);
        rx = xorshift32() % sw;
        int ry = xorshift32() % sh;
        SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
        BitBlt(desk, rx, 10, 100, sh, desk, rx, 0, RGBBRUSH);
        BitBlt(desk, rx, -10, -100, sh, desk, rx, 0, RGBBRUSH);
        BitBlt(desk, 10, ry, sw, 96, desk, 0, ry, RGBBRUSH);
        BitBlt(desk, -10, ry, sw, -96, desk, 0, ry, RGBBRUSH);
        BitBlt(desk, rx, 10, 100, sh, desk, rx, 0, SRCCOPY);
        BitBlt(desk, rx, -10, -100, sh, desk, rx, 0, SRCPAINT);
        BitBlt(desk, 10, ry, sw, 96, desk, 0, ry, SRCAND);
        BitBlt(desk, -10, ry, sw, -96, desk, 0, ry, SRCINVERT);
        BitBlt(desk, -104, ry, sw, -966, desk, 0, ry, SRCERASE);
        Sleep(1);
    }
}
DWORD WINAPI wef(LPVOID lpParam) {
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

    for (int t = 0;; t++)
    {
        const int size = 1000;
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

        for (int i = 0; i < size; i += 100)
        {
            ci(x - i / 2, y - i / 2, i, i);
            Sleep(25);
        }
    }
}
DWORD WINAPI textout(LPVOID lpParam)
{
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"RADON";
    while (1)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(0);
        sy = GetSystemMetrics(1);
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
        Sleep(10);
    }
}
DWORD WINAPI payload6(LPVOID lpParam)
{
    while (1) {
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 222, rand() % 222, w, h, hdc, rand() % 222, rand() % 222, NOTSRCERASE);
        BitBlt(hdc, rand() % 222, rand() % 222, w, h, hdc, rand() % 222, rand() % 222, SRCINVERT);
        Sleep(10);
    }
}
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t / 8 >> (t >> 9) * t / ((t >> 14 & 3) + 4));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> (t & 4096 ? t * t >> 12 : t >> 12)) | t << (t >> 8));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t & t >> 12) * (t >> 4 | t >> 8);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int main() {
    if (MessageBoxW(NULL, L"Ayo man do you want to run GDI malware?", L"Radon.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"Are you sure little man?", L"Radon.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
          
            HANDLE thread1 = CreateThread(0, 0, RGB2, 0, 0, 0);
            sound1();
            Sleep(30000);
            TerminateThread(thread1, 0);
            CloseHandle(thread1);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
            HANDLE thread3 = CreateThread(0, 0, wef, 0, 0, 0);
            sound2();
            Sleep(30000);
            TerminateThread(thread2, 0);
            CloseHandle(thread2);
            InvalidateRect(0, 0, 0);
            TerminateThread(thread3, 0);
            CloseHandle(thread3);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread4 = CreateThread(0, 0, payload3, 0, 0, 0);
            sound3();
            Sleep(30000);
            TerminateThread(thread4, 0);
            CloseHandle(thread4);
            InvalidateRect(0, 0, 0);
            Sleep(2000);
            HANDLE thread5 = CreateThread(0, 0, textout, 0, 0, 0);
            HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
            HANDLE thread7 = CreateThread(0, 0, wef, 0, 0, 0);
            sound4();
            Sleep(30000);
            Sleep(-1);
        }
    }
}