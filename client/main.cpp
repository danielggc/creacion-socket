#include <asm-generic/socket.h>
#include <cstdlib>
#include <functional>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <type_traits>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>

using namespace std;

class SocketOpen{
    private:

        const unsigned port = 9000;
        const char * mse  = " client connect ";
        int sock = 0, valread, client_fd;
        struct sockaddr_in serv_addr;
        char buffer[1024] = { 0 };
    public:
    void error(const char *msg){
      perror(msg);
      exit(1);
    }


    int openSKT(){
        sock =socket(AF_INET,SOCK_STREAM,0);
        if(sock<0){

                error("error iniciando socket");
            }
        return sock;
    }
   

    void bind_to_port( ){
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
    
        // Convert IPv4 and IPv6 addresses from text to binary
        // form
        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
            <= 0) {
            cout<<"\nInvalid address/ Address not supported \n";
            error("init socket");
        }
        if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
            cout<<"\nConnection Failed \n";
            error(" connection ");
        }


    }

 
    void init ( ){
        openSKT();
        bind_to_port( );
    }

    void initComunication(){
        send(sock, mse, strlen(mse), 0);
        valread = read(sock, buffer, 1024);
        cout<<"coneccion realizada --> escriaba su mensaje:\n";
        while (1) {
            cin>>buffer;
            send(sock, buffer,strlen(buffer), 1024);

        }
        printf("%s\n", buffer);
    }


};

int main(int argc, char const* argv[]){
    SocketOpen    socketOpen = SocketOpen();

    socketOpen.init();
    socketOpen.initComunication();

    
}

