#include"utils.h"
#include <netdb.h>

t_log* logger;

int iniciar_servidor(void)
{
	// Quitar esta línea cuando hayamos terminado de implementar la funcion
	//assert(!"no implementado!");

	int socket_servidor;

	struct addrinfo hints, *servinfo, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, PUERTO, &hints, &servinfo);

	// Creamos el socket de escucha del servidor
	socket_servidor= socket(
		servinfo->ai_family,
		servinfo->ai_socktype,
		servinfo->ai_protocol
	);

	// Asociamos el socket a un puerto

	// Escuchamos las conexiones entrantes
	setsockopt(socket_servidor, SOL_SOCKET, SO_REUSEPORT, &(int){1}, sizeof(int));
    bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);
    listen(socket_servidor, SOMAXCONN);

	//int conexionReal = accept(socket_escucha, NULL, NULL);

	freeaddrinfo(servinfo);
	log_trace(logger, "Listo para escuchar a mi cliente");

	return socket_servidor;
}

int esperar_cliente(int socket_servidor)
{
	
	int socket_cliente;
	socket_cliente = accept(socket_servidor, NULL, NULL);
	log_info(logger, "Se conecto un cliente!");

	return socket_cliente;
}

char* recibir_buffer(int socket_cliente)
{
	char* buffer = malloc(50);
	int size =50;

	
	
	recv(socket_cliente, buffer, size, MSG_WAITALL);

	return buffer;
}

void recibir_mensaje(int socket_cliente)
{
	int size;
	char* buffer = recibir_buffer(socket_cliente);
	log_info(logger, "Me llego el mensaje %s", buffer);
	free(buffer);
}


