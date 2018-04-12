/*
	Author: Lorenzo Damiano
	Disclaimer: molto probabilmente non funziona un cazzo, aspettiamo che qualcuno (tipo Dio) sistemi il programma
	Disclaimer2: tenete anche conto che sto facendo l'esercizio senza aver capito cosa deve fare esattamente
*/

#include "TCPv2.hpp"
#include "stringhe.hpp"

#define REQUESTCHECK "GET "
#define TAGSQL "<sql"

//prototipi
char* get_file_name(char* request);
char* get_file_content(char* filename);
char* compile_response(char* filecontent, char* sql);

int main(int argc, char* argv[]) {
	if(argc!=3) {
		printf("USAGE:%s PORT ROOT\n",argv[0]);
		return -1;
	}
	
	int port = atoi(argv[1]);
	ServerTCP myself(port,true);
	Connection* connection = myself.accetta();
	char* request = connection.ricevi();
	if(cmp_str(strstr(request,REQUESTCHECK),request)!=0) {
		printf("Request received is not a HTML request\n");
		return 0;
	}
	
	char* filename = get_file_name(request);
	char* filecontent = get_file_content(filename);
	
	if((char* temp = strstr(filecontent, TAGSQL))!=NULL) {
		//connetti al db
		//esegui query
		//crea tabella con risultati
	}
	
	char* response = compile_response(filecontent, temp);
	
	connection.invia(response);
	
	free(filecontent);
	free(filename);
	delete(connection);
	delete(myself);
}

//riceve una request HTML e restituisce il nome del file richiesto
char* get_file_name(char* request) {
	char ret[MAX_STR];
	request+=4;
	int i=0;
	while(*request && *request!='\n') {
		ret[i] = *request;
		request++;
		i++;
	}
	ret[i]='\0';
	return strdup(ret);
}

//riceve un file e copia tutto il contenuto all'interno di una stringa
char* get_file_content(char* filename) {
	FILE *f = fopen(filename,"r");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);	
	char *string = malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);
	string[fsize] = '\0';
	return string;
}

//costruisce la response aggiungendo i risultati della query se il parametro "sql" non è NULL
char* compile_response(char* filecontent, char* sql) {
	char* ret;
	
	return ret;
}
