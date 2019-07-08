   /*\
   	*________________________________________________________
   	|
	|
	|       @file: trabalho_2_ED.c
 	|     @authores: Jean M. Rolszt (jeanrolszt@gmail.com) & João Luiz M. Junior (joaoluiz.mjr@gmail.com)
 	| @disciplina: Estrutura de Dados
 	| @algoritimo: Decoficação código morsa
 	|
 	|________________________________________________________
 	*
   \*/ 
  /*DESCRIÇÃO DO ALGORÍTIMO:
   	O presente projeto tem como objetivo a concretização dos conceitos de árvores.
   	Mais especificamente, o principal objetivo do trabalho  ́e utilizar uma  ́arvore binária para
   	implementar a decodificação de textos em código morse.  */

/*Inicialização do programa*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct noh	{
	char caracter;
	struct noh *ponto;
	struct noh *traco;
}noh;

typedef struct elemento	{
	char simbolo;
	char codigo_morse[10];
	struct elemento * proximo;
}t_elemento;

typedef struct lista	{
	t_elemento * inicio;
	t_elemento * fim;
}t_lista;

struct noh* novo_noh (char caractere_do_noh) {
	/*Função que recebe um caractere e retorna um ponteiro para um novo nó na árvore de busca*/
	struct noh* inserido = (struct noh*) malloc(sizeof(struct noh));

	inserido->caracter = caractere_do_noh;
	inserido->ponto = inserido->traco = NULL;

	return inserido;
}

void inserir_em_arvore(struct noh* raiz, char caractere_inserido, char codigo_morse[]) {
	/*Função que recebe a raiz da árvore, um caractere e seu codigo morse correspondente, percorre
	 * a árvore até a posição correta e então chama a função de inserção para criar o nó.*/
	int i;
	char vazio;
	struct noh* atual = raiz;
	
	for (i = 0, vazio = '\0'; i < strlen(codigo_morse); i++) {

		if (codigo_morse[i] == '.')	{
			if (atual->ponto == NULL)			{
				atual->ponto = novo_noh(vazio);
			}
			atual=atual->ponto;
		}
		else if (codigo_morse[i] == '-') {
			if (atual->traco == NULL)			{
				atual->traco = novo_noh(vazio);
			}
			atual=atual->traco;
		}
	}
	/*printf("Caminho -> ");
	printf("%s   \tInserido -> %c       Local -> %p\n", codigo_morse, caractere_inserido, atual);*/
	atual->caracter = caractere_inserido;
}

char busca_em_arvore(struct noh* raiz, char codigo_do_caracter[]) {
	/*Função que utiliza a mesma lógica de pesquisa na árvore presente na inserção,
	 * desta vez para localizar e retornar um caracter. */
	int i;
	struct noh* atual = raiz;

	if (codigo_do_caracter[0] == '/')   {
    	return ' ';
    }

	for (i = 0; i <= (strlen(codigo_do_caracter)-1); i++)	{

		if (codigo_do_caracter[i] == '.')	{
			atual = atual->ponto;
		}
		if (codigo_do_caracter[i] == '-')	{
			atual = atual->traco;
		}
	}
	return atual->caracter;
}

char busca_em_lista (t_lista * l, char string[10]) {
	t_elemento *atual = l->inicio;

	if (string[0] == '/')	{
    	return ' ';
    }

	else {
    	while(strcmp(string, atual->codigo_morse) != 0) {
    		atual = atual->proximo;
    	}
    }
	return atual->simbolo;
}

void insere_Final_de_Lista(char caractere, char string[10], t_lista * l)	{
	/*Função que insere caracter e código morse correspondente no último elemento da lista.
	 * Obs.: como sabemos que elementos serão inseridos, e sabemos também que estão em ordem,
	 * não precisamos nem definir outras funções de inserção, como de inserir no início, pois
	 * não serão utilizadas. */
	t_elemento * novoultimo = NULL;

	novoultimo = (t_elemento *)malloc(sizeof(t_elemento));
	novoultimo->simbolo = caractere;
    strcpy(novoultimo->codigo_morse, string);
	novoultimo->proximo = NULL;

	if(l->inicio == NULL)	{
		l->inicio = novoultimo;
	}
	else {
		l->fim->proximo = novoultimo;
	}

	l->fim = novoultimo;
}

void testa_abertura_de_arquivo(char* arquivo) {
	/*Função que simplesmente verifica se o arquivo em questão pode ser aberto*/
    FILE *fp = fopen(arquivo, "r");

    if(!fp) {
        printf("Não foi possivel abrir \"%s\".\n", arquivo);
    }
    fclose(fp);
}

int main()	{
	int i;
	char letra, codigo_correspondente[10];
	char arquivo_com_codigo[] = "morse.txt", arquivo_com_mensagem[] = "mensagem.txt";
	
	struct noh* raiz = (struct noh*) malloc(sizeof(struct noh));
	raiz->ponto = raiz->traco = NULL;
	
	t_lista * l = (t_lista *)malloc(sizeof(t_lista));
    l->inicio = NULL;
    l->fim = NULL;

	/*Lendo o arquivo e preenchendo a árvore*/
	testa_abertura_de_arquivo(arquivo_com_codigo);
    FILE *letras_e_morse = fopen(arquivo_com_codigo, "r");
    while ((fscanf(letras_e_morse, "%c %s\n", &letra, codigo_correspondente))!= EOF)	{
    	inserir_em_arvore(raiz, letra, codigo_correspondente);
    }
    fclose(letras_e_morse);

    testa_abertura_de_arquivo(arquivo_com_mensagem);
    FILE *msg_codificada = fopen(arquivo_com_mensagem, "r");
    printf("\nA mensagem a ser decodificada -> ...");
	while((letra = fgetc(msg_codificada)) != EOF)	{
		printf("%c", letra);
	}
	
	fclose(msg_codificada);

	/* Sessao para testes, em que o usuario pode inserir qualquer codigo valido e verificar se o programa
	consegue encontrar a letra correspondente

	do {
		scanf ("%s", codigo_correspondente);
		printf("%s  --->  %c\n",codigo_correspondente, busca_em_arvore(raiz, codigo_correspondente));
	} while (codigo_correspondente[0] !=  'N');
	*/
    printf("\n\n\t\t\t        PARTE 1\n");
    printf("\t\t\t - ARVORES BINARIAS -\n\n");

	testa_abertura_de_arquivo(arquivo_com_mensagem);
	msg_codificada = fopen(arquivo_com_mensagem, "r");
	printf("\n\nA mensagem, decodificada pelo programa utilizando uma arvore binaria:\n\n");
	while ((fscanf(msg_codificada, "%s ", codigo_correspondente))!= EOF)	{
		printf("%c", busca_em_arvore(raiz, codigo_correspondente));
	}
	fclose(msg_codificada);

	/* Parte referente a lista encadeada */
	printf("\n\n");
    printf("\t\t\t        PARTE 2\n");
    printf("\t\t\t - LISTAS ENCADEADAS -\n\n");
    testa_abertura_de_arquivo(arquivo_com_codigo);
    letras_e_morse = fopen(arquivo_com_codigo, "r");
    while ((fscanf(letras_e_morse, "%c %s\n", &letra, codigo_correspondente))!= EOF)	{
    	insere_Final_de_Lista(letra, codigo_correspondente, l);
    }
    fclose(letras_e_morse);

    testa_abertura_de_arquivo(arquivo_com_mensagem);
    msg_codificada = fopen (arquivo_com_mensagem, "r");
    printf("A mesma mensagem, agora decodificada pelo programa utilizando uma lista encadeada:\n\n");
    while ((fscanf(msg_codificada, "%s", codigo_correspondente))!= EOF)	{
    	printf("%c", busca_em_lista(l, codigo_correspondente));
    }
    fclose(msg_codificada);

	printf("\n\n");
    printf("\t\t\t         PARTE 3\n");
    printf("\t\t\t - MEDINDO PERFORMANCES -\n\n");
    
    testa_abertura_de_arquivo(arquivo_com_mensagem);
	msg_codificada = fopen(arquivo_com_mensagem, "r");

	int nvzs=500000;
	int porcentagem=0;
	long antes = clock();
	printf("\n");
    for (i = 0; i < nvzs; ++i)    {
        while ((fscanf(msg_codificada, "%s", codigo_correspondente))!= EOF)	{
			letra = busca_em_arvore(raiz, codigo_correspondente);
		}
		porcentagem=(i*100)/nvzs;
		printf("\b\b\b%d",porcentagem);

	}
	printf("\b\b\b100");
	long depois = clock();
	double tempo = (double)(depois-antes)/CLOCKS_PER_SEC;
	printf("\nA arvore demorou %lf segundos\n",tempo);
	fclose(msg_codificada);

	testa_abertura_de_arquivo(arquivo_com_mensagem);
	msg_codificada = fopen(arquivo_com_mensagem, "r");

	antes = clock();
	for (i = 0; i < nvzs; ++i){
	    while ((fscanf(msg_codificada, "%s", codigo_correspondente))!= EOF)	{
    		letra = busca_em_lista(l, codigo_correspondente);
    	}
    	porcentagem=(i*100)/nvzs;
		printf("\b\b\b%d",porcentagem);

	}
	depois = clock();
	tempo = (double)(depois-antes)/CLOCKS_PER_SEC;
	printf("\b\b\b100");
	printf("\nA lista demorou %lf segundos",tempo);
	printf("\n");
	fclose(msg_codificada);

	return 0;
}
