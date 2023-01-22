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

using namespace std;

class SocketOpen{
    private:


        int server_fd, new_socket, valread;
        struct sockaddr_in address;
        int opt = 1;
        int addrlen = sizeof(address);
        char buffer[1024] = { 0 };
        const unsigned port = 8081;
        const char * mse  = "socket Init";

    public:
    void error(const char *msg){
      perror(msg);
      exit(1);
    }


    void setScoket( ){
        if (setsockopt(server_fd, SOL_SOCKET,
                    SO_REUSEADDR | SO_REUSEPORT, &opt,
                    sizeof(opt))) {
            error("setsockopt");
        }

    }

    void bind_to_port( ){
        address.sin_family = AF_INET;
        address.sin_port = htons(port);
        address.sin_addr.s_addr = INADDR_ANY;
        int c=bind( server_fd ,(struct sockaddr*) &address, sizeof(address));
        if(c<0){
            error("bind error ");
        }
    }

    int openSKT(){
        server_fd =socket(AF_INET,SOCK_STREAM,0);
        if(server_fd<0){

                error("error iniciando socket");
            }
        return server_fd;
    }

    void init ( ){
        openSKT();
        setScoket();
        bind_to_port( );
    }


    void listenServidor(){
        if( listen( server_fd ,  3) <0 ){
            error("listen");
        }
        if( (new_socket =  accept(server_fd, (struct sockaddr* ) &address, (socklen_t*)&addrlen )) < 0 ){
            error("accept");
        }
        valread = read(new_socket, buffer,1024);
        cout<<buffer;
        send( new_socket, mse , strlen( mse ), 0);
        printf(" mesaje enviado : \n  y resivido :");
        for(int i = 0; buffer[i] != '\0'; i++){
            buffer[i] = ' ';
        }
        
        while (1) {
            valread = read(new_socket, buffer, 1024);
            printf("%s\n", buffer);            
            for(int i = 0; buffer[i] != '\0'; i++){
                buffer[i] = ' ';
            }
        }


    }


    void closeSocket(){
        close(new_socket);
        shutdown(server_fd, SHUT_RDWR);
    }

};

int main(int argc, char const* argv[]){
    SocketOpen    socketOpen = SocketOpen();

    socketOpen.init();
    while (1) {
        socketOpen.listenServidor();
        printf("terminanado la coneccion");
        socketOpen.closeSocket();
    }
    
}

