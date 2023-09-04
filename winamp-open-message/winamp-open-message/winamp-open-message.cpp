#include <iostream>
#include <Windows.h>

#define WM_WA_IPC WM_USER
#define IPC_ENQUEUEFILE 100
#define IPC_DELETE 101
#define IPC_STARTPLAY 102
#define IPC_SETPLAYLISTPOS 121
#define WINAMP_BUTTON2 40045

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Wrong number of arguments!" << std::endl;
    }

    HWND winampWindow = FindWindowA("Winamp v1.x", NULL);
    if (winampWindow)
    {
        SendMessageA(winampWindow, WM_WA_IPC, 0, IPC_DELETE);
        std::cout << "Message sent!" << std::endl;

        COPYDATASTRUCT cds = { 0 };
        cds.dwData = IPC_ENQUEUEFILE;
        cds.lpData = (void*)argv[1];
        cds.cbData = strlen((char*)cds.lpData) + 1;  // include space for null char
        SendMessageA(winampWindow, WM_COPYDATA, 0, (LPARAM)&cds);
        std::cout << "Message sent!" << std::endl;

        //SendMessageA(winampWindow, WM_WA_IPC, 0, IPC_STARTPLAY);
        SendMessageA(winampWindow, WM_WA_IPC, 1, IPC_SETPLAYLISTPOS);
        std::cout << "Message sent!" << std::endl;

        SendMessageA(winampWindow, WM_COMMAND, MAKEWPARAM(WINAMP_BUTTON2, 0), 0);
        std::cout << "Message sent!" << std::endl;
    }
    else
    {
        std::cout << "Window not found aborting." << std::endl;
    }
}
