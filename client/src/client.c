#include "client.h"
#include "string.h"
#include "utils.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "Logger inicializado.");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	log_info(logger, "configuracion de entorno inicializada.");

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	
	if(ip == NULL || puerto == NULL){
		log_error(logger, "no se pudo recuperar algunas de las variables de entorno: ip, puerto, ...");
		abort();
	}

	// Loggeamos el valor de config
	log_info(logger, "logeando valor de la ip: ");
	log_info(logger, ip);

	log_info(logger, "logeando valor del puerto: ");
	log_info(logger, puerto);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	t_config* config = iniciar_config();

	char* log_path_file_name;
	bool log_in_console;
	char* process_name;

	if(config_has_property(config, "LOG_PATH_FILE_NAME")){
		log_path_file_name = config_get_string_value(config, "LOG_PATH_FILE_NAME");
	} else {
		log_path_file_name = "./../client/logs/bocajrs.log";
	};

	if(config_has_property(config, "LOG_IN_CONSOLE")){
		log_in_console = config_get_int_value(config, "LOG_IN_CONSOLE");
	} else {
		log_in_console = 1;
	};

	if(config_has_property(config, "LOG_PROCESS_NAME")){
		process_name = config_get_string_value(config, "LOG_PROCESS_NAME");
	} else {
		process_name = "someProcessName";
	};

	nuevo_logger = log_create(log_path_file_name, process_name, log_in_console, LOG_LEVEL_INFO);

	config_destroy(config);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("./../client/cliente.config");
	
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	bool iterar = true;
	char* leido;

	while(iterar){

		// La primera te la dejo de yapa
		leido = readline("> ");

		// El resto, las vamos leyendo y logueando hasta recibir un string vacío
		log_info(logger, leido);

		if(es_string_vacio(leido)){
			log_info(logger, "se recibió una cadena nula o vacía, finalizando");
			iterar = false;
		}
	}
	
	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);
}

int es_string_vacio(char* cadena){
	
	if(cadena == NULL){
		return 1;
	} else if(cadena[0] == '\0'){
		return 1;
	}

	for(int i = 0; cadena[i] != '\0'; i++){
		if(!isspace(cadena[i])){
			return 0;
		}
	}

	return 1;
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	  log_destroy(logger);
	  config_destroy(config);
}
