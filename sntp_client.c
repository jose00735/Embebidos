#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h> //for socket(), connect(), send() and recv()
#include <netinet/in.h>

#define Seventy_years 2208988800

// SOCK_STREAM -> TCP 
// SOCK_DGRAM -> UDP

int main(){

    int connection = 0;
    int socket_id = 0;
    long int data[6] = {0};
    int stratum = 0;
    unsigned char msg[48]={0x1B,0,0,0,0,0,0,0,0,0};
    unsigned char buffer[50]={0};

    // Server parameters  IP = 200.89.75.197
    struct sockaddr_in serverntp;
    serverntp.sin_family = AF_INET ; // protocol
    serverntp.sin_addr.s_addr = inet_addr("200.89.75.197"); // server ip
    serverntp.sin_port = htons(123); // 123 is ntp port number


    socket_id = socket(PF_INET, SOCK_DGRAM, 0);
    if (socket_id < 0){
        perror("[ERROR] Socket\r\n");
        return(-1);
    }
    printf("[+] Socket created\r\n");


    connection = connect(socket_id, (struct sockaddr*)&serverntp, sizeof(serverntp));
    if (connection < 0){
        printf("[ERROR] connection failed\r\n");
        return(-1);
    }
    printf("[+] Successful connection\r\n");
    

    send(socket_id, msg, sizeof(msg), 0); 
    printf("[+] Data send\r\n");

    // los penultimos 32 bits  contienen los segundos 
    // El número de segundos corresponde a los segundos transcurridos desde 1970.
    
    recv(socket_id,buffer,sizeof(buffer),0);
    printf("[+] Data receive\r\n");
    

    // convirtiendo las cadenas de 8 bytes a una de 32 bytes para formar el numero correspondiente
    // a los segundos
    
    data[1] = buffer[43]<<24;
    data[2] = buffer[42]<<16;
    data[3] = buffer[41]<<8;
    data[4] = data[1]+ data[2] + data[3] + data[40];

    data[5]= ntohl( data[4] );

    // convierte una cadena de formato de orden de byte de la red al 
    // orden de bytes del host
    
    data[5] = data[5] - Seventy_years; // le restamos los 70 años a la fecha     

    // se captura la informacion correspondiente al stratum para saber que tan confiable es esta fecha
    
    stratum = buffer[2];
          
    //La función ctime (const time_t * timer) 
    //devuelve una cadena que representa el tiempo basado en el argumento timer.
    //La cadena devuelta tiene el siguiente formato: 
    //día de la semana, mes, día del mes, hh: mm: ss la hora y el año.
    
    printf("======== FECHA =========\n\r%s", ctime(&data[5]));
    printf("========================\n\r");
    printf("======== Stratum ========\n\r");
    printf("%d\n\r",stratum);
    printf("========================\n\r");
    if(stratum > 15){
      printf("Fecha desincronizada");   
    }	     
    else 
    {
      printf("fecha sincronizada");
    }
    close(socket_id);
    return (0);

}
