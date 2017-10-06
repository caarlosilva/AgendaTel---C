//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

/*
Nome: Agenda para armazenar contatos e seus dados básicos
Autor: Carlos Eduardo T. da Silva
Data: 15/05/2017
Função: Armazenar Nome, Telefone e Data de Aniversário(Dia e Mês) de contatos.
Pesquisar por Nome ou Inicial, e mostrar os Aniversariantes do mês quando requisitado
*/


//DECLARAÇÃO DA STRUCT AGENDA
typedef struct{
	char nome[50];			//Nome do contato
	char tel[12];
	int dia, mes;		//Telefone, dia e mês de aniversário respectivamente
}agenda;

//PROTÓTIPOS DAS FUNÇÕES
/*insert adicionará novos contatos a struct */
void insert		(agenda *a, FILE *arq, int *c, int *M);

/*search irá comparar uma string lida com os nomes dos contatos na struct
se forem iguais, será mostrado os dados do contato na tela */
void search		(agenda *a, int *c);

/* list irá listar todos os contatos adicionados na tela */
void list		(agenda *a, int *c);

/* listchar irá receber um caractere inicial, e irá comparar com os contatos
se as inicias forem iguais, será mostrado os dados do contato na tela */
void listchar	(agenda *a, int *c);

/* bday irá receber um mes(numero) e irá comparar com o mês dos contatos
se forem iguais, será mostrado os dados do aniversariante na tela */
void bday		(agenda *a, int *c);


//INICIO DO MAIN
int main(){
	int func,contato,max,menu=1;
	//printf("\nNO INICIO CONT: %d  MAX=%d ",contato,max);

	setlocale(LC_ALL,"Portuguese");			//Inserção dos caracteres e pontuações brasileiros
	
	agenda *ag;								//ag aponta para a struct agenda
		
	FILE *arq;								//Inicialização do arquivo com os dados da agenda
	arq = fopen("agenda.dat","rb"); 		//Tentativa de abrir o arquivo 'agenda.dat' em modo de leitura
	if(arq == NULL){						//Se NÃO EXISTIR
		contato=0;							//Logo, existem 0 contatos
		max=5;								//E define-se um máximo de contatos
		ag = (agenda*)malloc(max*sizeof(agenda)); //Alocação Din. com base no maximo de contatos
	}
	else{									//Se EXISTIR
		rewind(arq);						//Volta o ponteiro do arquivo no inico
		fread(&contato,sizeof(int),1,arq);	//É feito a leitura do total de contatos, o primeiro item gravado no arquivo
		max=contato+5;						//O total de contatos tem que ser maior o total de contatos ja armazenados
		ag=(agenda*)malloc(max*sizeof(agenda));//Alocação Din. com base no maximo de contatos
		fread(ag,sizeof(agenda),contato,arq);//Leitura dos dados,os armazenando na struct	
	}
	fclose(arq);							//Fecha o arquivo após as leituras
	
	while(menu){							//Enquanto menu for = 1
	system ("clear || cls");				//Limpa a tela 'clear' = Linux 'cls'=Windows
	printf("\t\t\tAGENDA\n");
	printf("\n\t\tVoce tem %d contatos adicionados!\n",contato);//Imprime na tela o total de contatos ja armazenados
	printf("\n[1].Inserir Contatos\t\t[2].Pesquisar\n[3].Listar Contatos\t\t[4].Listar por Letra Inicial\n[5].Aniversariantes por mês\n[0].Sair e Salvar\n");
	printf("\nCódigo: ");
	scanf("%d",&func);						//Leitura da função desejada do menu
	switch(func){							//switch em função da função
		case 1:								//se == 1
			insert(ag, arq, &contato, &max);//Chama função insert
			getch();						//Pausa a tela (equivale a um system("PAUSE")
			break;
		case 2:								//se == 2
			search	(ag, &contato);			//Chama a função search
			getch();						//Pausa a tela
			break;
		case 3:								//se == 3
			list	(ag, &contato);			//Chama a função list
			getch();						//Pausa a tela
			break;
		case 4:								//se == 4
			listchar(ag, &contato);			//Chama a função listchar
			getch();						//Pausa a tela
			break;								
		case 5:								//se == 5
			bday	(ag, &contato);			//Chama a função bday
			getch();						//Pausa a tela
			break;
		case 0:								//se == 0
			arq = fopen("agenda.dat","wb");	//Abre o arquivo em modo de escrita
			/*Escreve primeiramente o total de contatos, presente na variavel 'contato' */
			fwrite(&contato, sizeof(int), 1, arq);
			
			/*Depois escreve a struct inteira, do tamanho total de contatos */
			fwrite(ag,sizeof(agenda),contato,arq);
			
			fclose(arq);					//Fecha o arquivo após as escritas	
			menu=0;							//Menu recebe 0, logo sai do loop do menu
			free(ag);						//Libera a memória alocada por 'ag'
			printf("\nSalvando....");
			break;
			
		default:							//se for algo diferente dos valores dos cases
			break;							//Simplesmente volta ao menu
 	}//FIM DO SWITCH
	}//FIM DO WHILE (LOOP DO MENU)
	return 0;
}//FIM DO MAIN


//INICIO DA FUNÇÃO INSERT
void insert(agenda *a, FILE *arq,int *c,int *M){
		
	int add,aux;							//add = quant de contatos, aux = soma do total de contatos com o add
	printf("Quantos contatos serão adicionados?\n");
	scanf("%d",&add);						//add recebe o tanto que será adicionado
	aux=*c+add;								//aux recebe add + total de contatos ja salvos
	while(aux>=*M){							//Se o numero de contatos a adicionar exceder o maximo pré-definido
		*M=*M+add+5;						//O Maximo torna a ser o tanto que será adicionado + 5
		a = (agenda*)realloc(a,(*M *sizeof(agenda)));//e a struct é realocada com o MAX ja recalculado
	}

	for(int i=*c;i<aux;i++){				//i começa com o numero de contatos, e vai até aux
		
		system("cls || clear");

		printf("\t\tInserir Contato %d\n",i+1);
		printf("\nNome: ");
		fflush(stdin);
		fgets(a[i].nome,50,stdin);			//Leitura do nome, de tamanho max de 50 char.
		strupr(a[i].nome);					//String inteira é transformada em maiuscula
		printf("\nTelefone: ");
		fgets(a[i].tel,12,stdin);			//Leitura do num. do telefone de 11 numeros(max atualmente)
		printf("\n\tAniversário\nDia: ");	
		fflush(stdin);	
		scanf("%2d",&a[i].dia);				//Leitura do dia, 2 numeros apenas
		
		while(a[i].dia < 1 || a[i].dia > 31){	//Enquanto não for um dia válido do calendário
			printf("\nDia inválido ! \n\t\tTente novamente\nDia: ");
			fflush(stdin);
				scanf("%2d",&a[i].dia);		//A leitura será refeita	
			}	
		printf("\nMês: ");
		fflush(stdin);
		scanf("%2d",&a[i].mes);				//Leitura do mês, 2 numeros apenas
			
		while(a[i].mes < 1	|| a[i].mes >12){	//Enquanto não for um numero/mês válido
			printf("\nMês inválido ! \n\t\tTente novamente\nMês: ");
			fflush(stdin);
			scanf("%2d",&a[i].mes);			//A leitura será refeita
		}
	}
	printf("\n\n\t%d Contato(s) adicionado(s) !",add);
	*c=*c+add;								//O Total de contatos passa a ser o total ja adicionado + o que foi adicionado
	
}//FIM DA FUNÇÃO INSERT


//INICIO DA FUNÇÃO SEARCH
void search(agenda *a, int *c){
	
	char name[20], aux[20];					
	int j=0, compara, compara1, contador=0;
	system("cls || clear");
	printf("Buscar por: ");
	fflush(stdin);
	fgets(name,20,stdin);					//name receberá a string que o usuario irá pesquisar
	strupr(name);							//a string toda é transformado em maiusculo
	
	printf("\n---------------------------------------------------------------------------");
	for(int i=0; i<*c; i++){				//de i=0 até o total de contatos
	/* esse while servirá para copiar somente o primeiro nome(caso o usuario tenha cadastrado sobrenome e etc.) na variavel aux
	assim, se o	usuario inserir somente o primeiro nome, sera possivel encontrar usuarios que tenha sobrenome					*/
			while(!isspace(a[i].nome[j])){	//enquanto não houver espaço na string
				aux[j]=a[i].nome[j];		//aux receberá a string salva
				j++;						
			}
		compara = strncmp(name, a[i].nome, 20);	//compara irá comparar name com o nome salvo
		compara1= strncmp(name, aux, j);		//compara1 irá comparar name com o aux, que possui somente o primeiro nome
		
		if(compara==0 || compara1==0){			//se compara OU compara1 for igual a 0
												//é printado todos os dados do contato			
			printf("\n\t\t\t[%d].%s\nTelefone:%s\nAniversário(D/M): %d/%d\n",i+1,a[i].nome,a[i].tel,a[i].dia,a[i].mes);
			printf("---------------------------------------------------------------------------");
			contador++;			//Contagem do total de contatos que se encaixam na busca
		}
		j=0;
	}
		printf("\n\n\tSua busca foi finalizada e retornou %d contato(s)!",contador);
		printf("\n\t\tPressione qualquer tecla para continuar...");	
}//FIM DA FUNÇÃO SEARCH


//INICIO DA FUNÇÃO LIST
void list(agenda *a, int *c){
	
	system ("clear || cls");
	printf("\t\t\tLISTA DE CONTATOS \n\n\t\tVoce têm %d contatos adicionados !",*c);
	printf("\n---------------------------------------------------------------------------");
	/* é printado todos os contatos ja adicionados */
	for(int i=0;i<*c;i++){
		printf("\n\t\t\t[%d].%s\nTelefone:%s\nAniversário(D/M): %d/%d\n",i+1,a[i].nome,a[i].tel,a[i].dia,a[i].mes);
		printf("---------------------------------------------------------------------------");
	}
	printf("\n\t\tPressione qualquer tecla para continuar...");
}//FIM DA FUNÇÃO LIST


//INICIO DA FUNÇÃO LIST CHAR
void listchar(agenda *a, int *c){
	
	int contador=0, compara;
	char inicial[1];
	system("cls || clear");	
	printf("Buscar pela inicial: ");
	fflush(stdin);
	scanf("%c",&inicial);							//Leitura da letra inicial
	strupr(inicial);								//Inicial é transformada em maiusculo
	
	printf("\n---------------------------------------------------------------------------");	
	for(int i=0;i<*c;i++){
		compara  = strncmp (a[i].nome,inicial,1);	//Compara irá comparar com a letra maiuscula6552	
		if(compara == 0){		//Sendo assim, o programa irá comparar o caracter digitado, sendo maiusculo ou minusculo		
			printf("\n\t\t\t[%d].%s\nTelefone:%s\nAniversário(D/M): %d/%d\n",i+1,a[i].nome,a[i].tel,a[i].dia,a[i].mes);
			printf("---------------------------------------------------------------------------");
			contador++;								//Contagem do total de contatos que se encaixam na busca
		}	
	
	}
	printf("\n\n\tSua busca foi finalizada e retornou %d contato(s) com a inicial '%c'!",contador,inicial[0]);
	printf("\n\t\tPressione qualquer tecla para continuar...");	
	
}// FIM FUNÇÃO LISTCHAR


//INICIO DA FUNÇÃO BDAY
void bday(agenda *a, int *c){
	
	int m,contador=0;
	char month[10];
	system("cls || clear");
	printf("Buscar por mês(número): ");
	scanf("%d",&m);									//Leitura do mês(numero) desejado
	
	while(m < 1 || m > 12){							//Se for um mês(numero) inválido
			printf("\nMês inválido ! \n\t\tTente novamente\nMês: ");
			fflush(stdin);
			scanf("%2d",&m);						//A leitura será refeita
	}
	printf("\n---------------------------------------------------------------------------");
	for(int i=0;i<*c;i++){							
		if(a[i].mes == m){							//Se o mês inserido for igual a alguma salvo na struct
			/* é printado na tela todos os dados do contato */
			printf("\n\t\t\t[%d].%s\nTelefone:%s\nAniversário(D/M): %d/%d\n",i+1,a[i].nome,a[i].tel,a[i].dia,a[i].mes);
			printf("---------------------------------------------------------------------------");
			contador++;								//Contagem do total de contatos que se encaixam na busca
	}
	}
	switch(m){										//Dando nome aos meses p/ printar no final
		case 1: strcpy(month,"Janeiro");
			break;
		case 2: strcpy(month,"Fevereiro");
			break;
		case 3: strcpy(month,"Março");
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
}//FIM DA FUNÇÃO BDAY