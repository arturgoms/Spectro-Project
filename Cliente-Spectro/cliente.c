#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <stdbool.h>
#include <wiringPi.h>
#include <assert.h>

#define LED 29
#define BTN 5

int menuStado = 0;
void menu();
int ler = 1, escrever = 1;

void erroAplicacao(const char *msg)
{
	perror(msg);
    	exit(1);
}


int main(void)
{
	wiringPiSetup() ;
	bool stadoLed;
	int socketCliente;
	struct sockaddr_in servidorEndereco;
	char mensagem[256];
	char servidorMensagem[256];
	char** mensagemServidor;
	char id;
	char request;
	pinMode(LED, OUTPUT);
	pinMode(BTN, OUTPUT);
	digitalWrite(LED, 1);
	if (digitalRead(LED) >0){
		stadoLed = true;
	}else{
		stadoLed= false;
	}
	socketCliente = socket(AF_INET , SOCK_STREAM , 0);
	if (socketCliente < 0){
	    erroAplicacao("Erro na abertura do socket");
	}

	servidorEndereco.sin_addr.s_addr = inet_addr("192.168.132.106");
	servidorEndereco.sin_family = AF_INET;
	servidorEndereco.sin_port = htons( 1234 );

	if (connect(socketCliente , (struct sockaddr *)&servidorEndereco , sizeof(servidorEndereco)) < 0)
	{
		erroAplicacao("Erro na abertura do socket");
	}

	printf("Conectado com o Servidor\n");
	bzero(mensagem,256);
	bzero(servidorMensagem,256);
	strcpy(mensagem,"pi#");
	write(socketCliente , mensagem , sizeof(mensagem));
	bzero(mensagem,256);
	if (digitalRead(BTN) > 0){
		strcpy(mensagem,"0-Botao esta precionado#");
		write(socketCliente , mensagem , sizeof(mensagem));
	}else{
		strcpy(mensagem,"0-Botao nao esta precionado#");
		write(socketCliente , mensagem , sizeof(mensagem));
	}
bzero(mensagem,256);
	if (digitalRead(LED) > 0){
		strcpy(mensagem,"0-Led aceso#");
		write(socketCliente , mensagem , sizeof(mensagem));
	}else{
		strcpy(mensagem,"0-Led apagado#");;
		write(socketCliente , mensagem , sizeof(mensagem));
		}
bzero(servidorMensagem,256);

	while(true)
	{
		bzero(mensagem,256);
		bzero(servidorMensagem,256);
		menu();
		if( menuStado == 1){ //Ler

			while (ler == 1){
				if( read(socketCliente , servidorMensagem , 255) < 0)
				{
					erroAplicacao("Falha no recebimento");
				}
				puts("Resposta servidor:");
				puts(servidorMensagem);


					digitalWrite (LED, HIGH) ;	// On
	    	   		delay (500) ;		// mS
	    	   		digitalWrite (LED, LOW) ;	// Off
	           		delay (500) ;
					printf("LED Aceso");


				if (strstr(servidorMensagem,"sair") !=NULL){
					ler = 2;
				}

				bzero(servidorMensagem,256);

		}menu();
}

		if( menuStado == 2){ // Escrever
			printf(" deu ler");
			while (escrever == 1){
				if (digitalRead(BTN) > 0){
					strcpy(mensagem,"Botao esta precionado");
					write(socketCliente , mensagem , sizeof(mensagem));
				}else{
					strcpy(mensagem,"Botao nao esta precionado");
					write(socketCliente , mensagem , sizeof(mensagem));
				}
				if (digitalRead(LED) > 0){
					strcpy(mensagem,"Led aceso");
					write(socketCliente , mensagem , sizeof(mensagem));
				}else{
					strcpy(mensagem,"Led apagado");;
					write(socketCliente , mensagem , sizeof(mensagem));
					}
				if( read(socketCliente , mensagem , 255) < 0)
				{
					erroAplicacao("Falha no recebimento");
				}

				if (strcpy(mensagem,"sair") ==0){
					escrever = 2;
			}
			menu();
		}
	}

	close(socketCliente);
	return 0;
}
}

void menu(void){

		printf("O que voce gostaria de fazer?: \n");
		printf(">         1) Ler              \n<");
		printf(">         2) Escrever         \n<");
		printf(">                             \n<");
		scanf("%d" , &menuStado);


}
