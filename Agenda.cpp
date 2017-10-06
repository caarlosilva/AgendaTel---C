//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

/*
Nome: Agenda para armazenar contatos e seus dados b�sicos
Autor: Carlos Eduardo T. da Silva
Data: 15/05/2017
Fun��o: Armazenar Nome, Telefone e Data de Anivers�rio(Dia e M�s) de contatos.
Pesquisar por Nome ou Inicial, e mostrar os Aniversariantes do m�s quando requisitado
*/


//DECLARA��O DA STRUCT AGENDA
typedef struct{
	char nome[50];			//Nome do contato
	char tel[12];
	int dia, mes;		//Telefone, dia e m�s de anivers�rio respectivamente
}agenda;

//PROT�TIPOS DAS FUN��ES
/*insert adicionar� novos contatos a struct */
void insert		(agenda *a, FILE *arq, int *c, int *M);

/*search ir� comparar uma string lida com os nomes dos contatos na struct
se forem iguais, ser� mostrado os dados do contato na tela */
void search		(agenda *a, int *c);

/* list ir� listar todos os contatos adicionados na tela */
void list		(agenda *a, int *c);

/* listchar ir� receber um caractere inicial, e ir� comparar com os contatos
se as inicias forem iguais, ser� mostrado os dados do contato na tela */
void listchar	(agenda *a, int *c);

/* bday ir� receber um mes(numero) e ir� comparar com o m�s dos contatos
se forem iguais, ser� mostrado os dados do aniversariante na tela */
void bday		(agenda *a, int *c);


//INICIO DO MAIN
int main(){
	int func,contato,max,menu=1;
	//printf("\nNO INICIO CONT: %d  MAX=%d ",contato,max);

	setlocale(LC_ALL,"Portuguese");			//Inser��o dos caracteres e pontua��es brasileiros
	
	agenda *ag;								//ag aponta para a struct agenda
		
	FILE *arq;								//Inicializa��o do arquivo com os dados da agenda
	arq = fopen("agenda.dat","rb"); 		//Tentativa de abrir o arquivo 'agenda.dat' em modo de leitura
	if(arq == NULL){						//Se N�O EXISTIR
		contato=0;							//Logo, existem 0 contatos
		max=5;								//E define-se um m�ximo de contatos
		ag = (agenda*)malloc(max*sizeof(agenda)); //Aloca��o Din. com base no maximo de contatos
	}
	else{									//Se EXISTIR
		rewind(arq);						//Volta o ponteiro do arquivo no inico
		fread(&contato,sizeof(int),1,arq);	//� feito a leitura do total de contatos, o primeiro item gravado no arquivo
		max=contato+5;						//O total de contatos tem que ser maior o total de contatos ja armazenados
		ag=(agenda*)malloc(max*sizeof(agenda));//Aloca��o Din. com base no maximo de contatos
		fread(ag,sizeof(agenda),contato,arq);//Leitura dos dados,os armazenando na struct	
	}
	fclose(arq);							//Fecha o arquivo ap�s as leituras
	
	while(menu){							//Enquanto menu for = 1
	system ("clear || cls");				//Limpa a tela 'clear' = Linux 'cls'=Windows
	printf("\t\t\tAGENDA\n");
	printf("\n\t\tVoce tem %d contatos adicionados!\n",contato);//Imprime na tela o total de contatos ja armazenados
	printf("\n[1].Inserir Contatos\t\t[2].Pesquisar\n[3].Listar Contatos\t\t[4].Listar por Letra Inicial\n[5].Aniversariantes por m�s\n[0].Sair e Salvar\n");
	printf("\nC�digo: ");
	scanf("%d",&func);						//Leitura da fun��o desejada do menu
	switch(func){							//switch em fun��o da fun��o
		case 1:								//se == 1
			insert(ag, arq, &contato, &max);//Chama fun��o insert
			getch();						//Pausa a tela (equivale a um system("PAUSE")
			break;
		case 2:								//se == 2
			search	(ag, &contato);			//Chama a fun��o search
			getch();						//Pausa a tela
			break;
		case 3:								//se == 3
			list	(ag, &contato);			//Chama a fun��o list
			getch();						//Pausa a tela
			break;
		case 4:								//se == 4
			listchar(ag, &contato);			//Chama a fun��o listchar
			getch();						//Pausa a tela
			break;								
		case 5:								//se == 5
			bday	(ag, &contato);			//Chama a fun��o bday
			getch();						//Pausa a tela
			break;
		case 0:								//se == 0
			arq = fopen("agenda.dat","wb");	//Abre o arquivo em modo de escrita
			/*Escreve primeiramente o total de contatos, presente na variavel 'contato' */
			fwrite(&contato, sizeof(int), 1, arq);
			
			/*Depois escreve a struct inteira, do tamanho total de contatos */
			fwrite(ag,sizeof(agenda),contato,arq);
			
			fclose(arq);					//Fecha o arquivo ap�s as escritas	
			menu=0;							//Menu recebe 0, logo sai do loop do menu
			free(ag);						//Libera a mem�ria alocada por 'ag'
			printf("\nSalvando....");
			break;
			
		default:							//se for algo diferente dos valores dos cases
			break;							//Simplesmente volta ao menu
 	}//FIM DO SWITCH
	}//FIM DO WHILE (LOOP DO MENU)
	return 0;
}//FIM DO MAIN


//INICIO DA FUN��O INSERT
void insert(agenda *a, FILE *arq,int *c,int *M){
		
	int add,aux;							//add = quant de contatos, aux = soma do total de contatos com o add
	printf("Quantos contatos ser�o adicionados?\n");
	scanf("%d",&add);						//add recebe o tanto que ser� adicionado
	aux=*c+add;								//aux recebe add + total de contatos ja salvos
	while(aux>=*M){							//Se o numero de contatos a adicionar exceder o maximo pr�-definido
		*M=*M+add+5;						//O Maximo torna a ser o tanto que ser� adicionado + 5
		a = (agenda*)realloc(a,(*M *sizeof(agenda)));//e a struct � realocada com o MAX ja recalculado
	}

	for(int i=*c;i<aux;i++){				//i come�a com o numero de contatos, e vai at� aux
		
		system("cls || clear");

		printf("\t\tInserir Contato %d\n",i+1);
		printf("\nNome: ");
		fflush(stdin);
		fgets(a[i].nome,50,stdin);			//Leitura do nome, de tamanho max de 50 char.
		strupr(a[i].nome);					//String inteira � transformada em maiuscula
		printf("\nTelefone: ");
		fgets(a[i].tel,12,stdin);			//Leitura do num. do telefone de 11 numeros(max atualmente)
		printf("\n\tAnivers�rio\nDia: ");	
		fflush(stdin);	
		scanf("%2d",&a[i].dia);				//Leitura do dia, 2 numeros apenas
		
		while(a[i].dia < 1 || a[i].dia > 31){	//Enquanto n�o for um dia v�lido do calend�rio
			printf("\nDia inv�lido ! \n\t\tTente novamente\nDia: ");
			fflush(stdin);
				scanf("%2d",&a[i].dia);		//A leitura ser� refeita	
			}	
		printf("\nM�s: ");
		fflush(stdin);
		scanf("%2d",&a[i].mes);				//Leitura do m�s, 2 numeros apenas
			
		while(a[i].mes < 1	|| a[i].mes >12){	//Enquanto n�o for um numero/m�s v�lido
			printf("\nM�s inv�lido ! \n\t\tTente novamente\nM�s: ");
			fflush(stdin);
			scanf("%2d",&a[i].mes);			//A leitura ser� refeita
		}
	}
	printf("\n\n\t%d Contato(s) adicionado(s) !",add);
	*c=*c+add;								//O Total de contatos passa a ser o total ja adicionado + o que foi adicionado
	
}//FIM DA FUN��O INSERT


//INICIO DA FUN��O SEARCH
void search(agenda *a, int *c){
	
	char name[20], aux[20];					
	int j=0, compara, compara1, contador=0;
	system("cls || clear");
	printf("Buscar por: ");
	fflush(stdin);
	fgets(name,20,stdin);					//name receber� a string que o usuario ir� pesquisar
	strupr(name);							//a string toda � transformado em maiusculo
	
	printf("\n---------------------------------------------------------------------------");
	for(int i=0; i<*c; i++){				//de i=0 at� o total de contatos
	/* esse while servir� para copiar somente o primeiro nome(caso o usuario tenha cadastrado sobrenome e etc.) na variavel aux
	assim, se o	usuario inserir somente o primeiro nome, sera possivel encontrar usuarios que tenha sobrenome					*/
			while(!isspace(a[i].nome[j])){	//enquanto n�o houver espa�o na string
				aux[j]=a[i].nome[j];		//aux receber� a string salva
				j++;						
			}
		compara = strncmp(name, a[i].nome, 20);	//compara ir� comparar name com o nome salvo
		compara1= strncmp(name, aux, j);		//compara1 ir� comparar name com o aux, que possui somente o primeiro nome
		
		if(compara==0 || compara1==0){			//se compara OU compara1 for igual a 0
												//� printado todos os dados do contato			
			printf("\n\t\t\t[%d].%s\nTelefone:%s\nAnivers�rio(D/M): %d/%d\n",i+1,a[i].nome,a[i].tel,a[i].dia,a[i].mes);
			printf("---------------------------------------------------------------------------");
			contador++;			//Contagem do total de contatos que se encaixam na busca
		}
		j=0;
	}
		printf("\n\n\tSua busca foi finalizada e retornou %d contato(s)!",contador);
		printf("\n\t\tPressione qualquer tecla para continuar...");	
}//FIM DA FUN��O SEARCH


//INICIO DA FUN��O LIST
void list(agenda *a, int *c){
	
	system ("clear || cls");
	printf("\t\t\tLISTA DE CONTATOS \n\n\t\tVoce t�m %d contatos adicionados !",*c);
	printf("\n---------------------------------------------------------------------------");
	/* � printado todos os contatos ja adicionados */
	for(int i=0;i<*c;i++){
		printf("\n\t\t\t[%d].%s\nTelefone:%s\nAnivers�rio(D/M): %d/%d\n",i+1,a[i].nome,a[i].tel,a[i].dia,a[i].mes);
		printf("---------------------------------------------------------------------------");
	}
	printf("\n\t\tPressione qualquer tecla para continuar...");
}//FIM DA FUN��O LIST


//INICIO DA FUN��O LIST CHAR
void listchar(agenda *a, int *c){
	
	int contador=0, compara;
	char inicial[1];
	system("cls || clear");	
	printf("Buscar pela inicial: ");
	fflush(stdin);
	scanf("%c",&inicial);							//Leitura da letra inicial
	strupr(inicial);								//Inicial � transformada em maiusculo
	
	printf("\n---------------------------------------------------------------------------");	
	for(int i=0;i<*c;i++){
		compara  = strncmp (a[i].nome,inicial,1);	//Compara ir� comparar com a letra maiuscula6552	
		if(compara == 0){		//Sendo assim, o programa ir� comparar o caracter digitado, sendo maiusculo ou minusculo		
			printf("\n\t\t\t[%d].%s\nTelefone:%s\nAnivers�rio(D/M): %d/%d\n",i+1,a[i].nome,a[i].tel,a[i].dia,a[i].mes);
			printf("---------------------------------------------------------------------------");
			contador++;								//Contagem do total de contatos que se encaixam na busca
		}	
	
	}
	printf("\n\n\tSua busca foi finalizada e retornou %d contato(s) com a inicial '%c'!",contador,inicial[0]);
	printf("\n\t\tPressione qualquer tecla para continuar...");	
	
}// FIM FUN��O LISTCHAR


//INICIO DA FUN��O BDAY
void bday(agenda *a, int *c){
	
	int m,contador=0;
	char month[10];
	system("cls || clear");
	printf("Buscar por m�s(n�mero): ");
	scanf("%d",&m);									//Leitura do m�s(numero) desejado
	
	while(m < 1 || m > 12){							//Se for um m�s(numero) inv�lido
			printf("\nM�s inv�lido ! \n\t\tTente novamente\nM�s: ");
			fflush(stdin);
			scanf("%2d",&m);						//A leitura ser� refeita
	}
	printf("\n---------------------------------------------------------------------------");
	for(int i=0;i<*c;i++){							
		if(a[i].mes == m){							//Se o m�s inserido for igual a alguma salvo na struct
			/* � printado na tela todos os dados do contato */
			printf("\n\t\t\t[%d].%s\nTelefone:%s\nAnivers�rio(D/M): %d/%d\n",i+1,a[i].nome,a[i].tel,a[i].dia,a[i].mes);
			printf("---------------------------------------------------------------------------");
			contador++;								//Contagem do total de contatos que se encaixam na busca
	}
	}
	switch(m){										//Dando nome aos meses p/ printar no final
		case 1: strcpy(month,"Janeiro");
			break;
		case 2: strcpy(month,"Fevereiro");
			break;
		case 3: strcpy(month,"Mar�o");
			break;
		case 4: strcpy(month,"Abril");
			break;
		case 5: strcpy(month,"Maio");
			break;
		case 6: strcpy(month,"Junho");
			break;
		case 7: strcpy(month,"Julho");
			break;
		case 8: strcpy(month,"Agosto");
			break;
		case 9: strcpy(month,"Setembro");
			break;
		case 10: strcpy(month,"Outubro");	
			break;
		case 11: strcpy(month,"Novembro");
			break;
		case 12: strcpy(month,"Dezembro");
			break;
	}
	printf("\n\nSua busca foi finalizada e retornou %d aniversariante(s) em %s !",contador,month);
	printf("\n\t\tPressione qualquer tecla para continuar...");
}//FIM DA FUN��O BDAY