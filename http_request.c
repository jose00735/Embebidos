#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdarg.h>

// BSSIZE es el tamnaño del buffer que se usa para leer la informacion que llega al socket

#define BSIZE 0x1000


// Se hace un output en la terminal de lo que llega de la peticion html 

static void get_page (int s, const char * host, const char * page)
{
	// el mensaje msg es una peticion la cual se enviara al server
    char * msg;

    // la constante formato es el formato en el que se envia el HTTP request al servidor web

    const char * format =
        "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: fetch.c\r\n\r\n";

    // en esta variable almacenamos los return values que nos de esta funcion
	
    int status;

	// lo encontre en internet XD
    status = asprintf (& msg, format, page, host);


    //Se enviar el request

    status = send (s, msg, strlen (msg), 0); 


    while (1) {
	// se guardan el numero de bytes recibidos
        int bytes;
	// nuestro buffer para recibir datos
        char buf[BSIZE+10];
	// se agarra el  BSIZE de "s"
        bytes = recvfrom (s, buf, BSIZE, 0, 0, 0);
	// esto se detiene una vez no hay nada mas a lo que hacer printf
        if (bytes == 0) {
            break;
        }
	// se imprime el caracter nulo para terminar
        buf[bytes] = '\0';
	// se hace un print estandar para el caracter nulo
        printf ("%s", buf);
    }
    free (msg);
}

int main ()
{
    struct addrinfo hints, *res, *res0;
    int error;
    // "s" es el archivo que hace la descripcion del socket 
    int s;
    // en este sitio se coloca la URL de la pagina
    const char * host = "www.google.com";

    memset (&hints, 0, sizeof (hints));
    //Se deja sin especificar el tipo si es IPV4 o IPV6 
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    error = getaddrinfo (host, "http", & hints, & res0);
    s = -1;
    for (res = res0; res; res = res->ai_next) {
        s = socket (res->ai_family, res->ai_socktype, res->ai_protocol);
        if (connect (s, res->ai_addr, res->ai_addrlen) < 0) {
            fprintf (stderr, "connect: %s\n", strerror (errno));
            close (s);
	    // exit ok
            exit (EXIT_FAILURE);
        }
        break;
    }
    if (s != -1) {
        get_page (s, host, "c/");
    }
    freeaddrinfo (res0);
    return 0;
}
