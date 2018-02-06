#include <stdio.h>
#include <stdlib.h>

/*
Universidade de Brasilia
Instituto de ciencias Exatas
Departamento de Ciencia da Computação

Estrutura de Dados - 1/2016

Aluno: Frederico Pinheiro Dib
Matricula: 15/0125925
Aluno: Amanda Oliveira Alves
Matricula: 15/0116276
Turma: A
Versão do copilador: Ubuntu 4.9.2
*/


/*função que contem a struct da arvore*/
typedef struct no{
	int jogador;
	int jogarn;
	int tab[14];
	struct no * um;
	struct no * dois;
	struct no * tres;
	struct no * quatro;
	struct no * cinco;
	struct no * seis;
}t_no;


/*a cada jogada do computador a funcao reseta a raiz, ou seja, iguala todos os ponteiros a NULL e reorganiza o tabuleiro*/
void resetaRaiz(t_no* n, int* tabuleiro) {
	int i;
   for(i=0;i<14;i++) {
   		n->tab[i] = tabuleiro[i];
   }
   n->um = NULL;
   n->dois = NULL;
   n->tres = NULL;
   n->quatro = NULL;
   n->cinco = NULL;
   n->seis = NULL;
}


/*Cria um no da arvore*/
t_no * criarNo(int* tabuleiro){
	int i;
   t_no * n =  (t_no *)malloc(sizeof(t_no));
   for(i=0;i<14;i++) {
   		n->tab[i] = tabuleiro[i];
   }
   n->um = NULL;
   n->dois = NULL;
   n->tres = NULL;
   n->quatro = NULL;
   n->cinco = NULL;
   n->seis = NULL;
   return n;
}


/*um menu que escolhe a dificuldade do jogo*/
void menu(int* computador, int* lim) {
	system("clear || cls");
	printf("digite a modalidade desejada\n");
	printf("1) Player vs Player\n");
	printf("2) Player vs Computador Facil\n");
	printf("3) Player vs Computador Medio\n");
	printf("4) Player vs Computador Dificil\n");
	printf("Coloque o numero desejado: ");
	scanf("%d", computador);
	while((*computador < 1) || (*computador > 4)) {
		printf("Opção invalida, digite novamente\n");
		scanf("%d", computador);
	}
	if(*computador == 2) {
		*lim = 2; /*lim = tamanho maximo da arvore*/
	}
	else {
		if(*computador == 3) {
			*lim = 2;
		}
		else {
			*lim = 3;
		}
	}
}


/*criar tabuleiro*/
void CriarTab(int* tabuleiro) {
	int i = 0;
	for(i=0;i<14;i++) {
		tabuleiro[i] = 4;
	}
	tabuleiro[6] = 0;
	tabuleiro[13] = 0;
}


/*funcao que mostra o campo na tela*/
void Tela(int jogador, int* tabuleiro) {
	int i;
	system("clear || cls");
	if(jogador == 2) {
		printf("jogador: 2, Seu turno\n\n");
	}
	else {
		printf("jogador: 2\n\n");
	}
	printf("       6   5   4   3   2   1\n");
	printf("      ");
	for(i=12;i>6;i--) {
		printf("|%d| ", tabuleiro[i]);
	}
	printf("\n");
	printf("|%d|\t\t\t\t|%d|", tabuleiro[13], tabuleiro[6]);
	printf("\n");
	printf("      ");
	for(i=0;i<6;i++) {
		printf("|%d| ", tabuleiro[i]);
	}
	printf("\n");
	printf("       1   2   3   4   5   6\n\n");
	if(jogador == 1) {
		printf("jogador: 1, Seu turno\n\n");
	}
	else {
		printf("jogador: 1\n\n");
	}
	printf("Digite a casa desejada, jogador %d: ", jogador);
}


/*converte a casa escolhida pelo jogador para o indice do vetor*/
int I_casa(int casa, int jogador) {
	if(jogador == 1) { /*jogador 1*/
		if(casa == 1) {
			return 0;
		}
		if(casa == 2) {
			return 1;
		}
		if(casa == 3) {
			return 2;
		}
		if(casa == 4) {
			return 3;
		}
		if(casa == 5) {
			return 4;
		}
		if(casa == 6) {
			return 5;
		}
	}
	else {/*jogador 2*/
		if(casa == 1) {
			return 7;
		}
		if(casa == 2) {
			return 8;
		}
		if(casa == 3) {
			return 9;
		}
		if(casa == 4) {
			return 10;
		}
		if(casa == 5) {
			return 11;
		}
		if(casa == 6) {
			return 12;
		}
	}

	return -1;
}


/*essa função recebe o indice da jogada e analisa o indice da casa oposta do adversario, essa função é usada na hora da captura*/
int Equivalente(int i) {
	if(i == 0) {
		return 12;
	}
	if(i == 1) {
		return 11;
	}
	if(i == 2) {
		return 10;
	}
	if(i == 3) {
		return 9;
	}
	if(i == 4) {
		return 8;
	}
	if(i == 5) {
		return 7;
	}
	if(i == 7) {
		return 5;
	}
	if(i == 8) {
		return 4;
	}
	if(i == 9) {
		return 3;
	}
	if(i == 10) {
		return 2;
	}
	if(i == 11) {
		return 1;
	}
	if(i == 12) {
		return 0;
	}
	return -1;
}


/*quando o jogo chegar ao final, retorna 1, ela faz isso vendo se alguma fileira inteira é nula*/
int Fim(int* tabuleiro) {
	int fim = 0;
	int cont = 0;
	int i;
	for(i=12;i>6;i--) {
		if(tabuleiro[i] == 0) {
			cont++;
		}
	}
	if (cont == 6) {
		fim = 1;
	}
	cont = 0;
	for(i=0;i<6;i++) {
		if(tabuleiro[i] == 0) {
			cont++;
		}
	}
	if (cont == 6) {
		fim = 1;
	}
	return fim;
}


/*São as jogadas usadas quando está montando a arvore, ele nao imprime nada na tela*/
void Jogada1Comp(int i_casa, int *troca, int* tabuleiro) {
	*troca = 0;
	int soma;
	int cont = tabuleiro[i_casa];
	tabuleiro[i_casa] = 0;
	while(cont > 0) {
		if(i_casa == 13) {
			i_casa = 0;
		}
		else {
			i_casa++;
		}
		if(i_casa != 13) {
			tabuleiro[i_casa]++;
			cont--;
		}
	}
	if(i_casa == 6) {
		*troca = 1;
	}
	if((tabuleiro[i_casa] == 1) && (i_casa != 6) && (i_casa < 6)) {
		if(tabuleiro[Equivalente(i_casa)] != 0) {
			soma = tabuleiro[i_casa] + tabuleiro[Equivalente(i_casa)];
			tabuleiro[Equivalente(i_casa)] = 0;
			tabuleiro[i_casa] = 0;
			tabuleiro[6] = tabuleiro[6] + soma;
		}
	}
}


/*São as jogadas usadas no tabuleiro principal, ela mostra na tela algumas mensagens explicando o que aconteceu*/
void Jogada1(int i_casa, int *troca, int* tabuleiro) {
	*troca = 0;
	int soma;
	int cont = tabuleiro[i_casa];
	tabuleiro[i_casa] = 0;
	while(cont > 0) {
		if(i_casa == 13) {
			i_casa = 0;
		}
		else {
			i_casa++;
		}
		if(i_casa != 13) {
			tabuleiro[i_casa]++;
			cont--;
		}
	}
	if(i_casa == 6) {
		*troca = 1;
		printf("JOGADOR 1, JOGUE NOVAMENTE :D\n");
		printf("aperte ENTER para continuar\n");
		getchar();
		getchar();
	}
	if((tabuleiro[i_casa] == 1) && (i_casa != 6) && (i_casa < 6)) {
		if(tabuleiro[Equivalente(i_casa)] != 0) {
			soma = tabuleiro[i_casa] + tabuleiro[Equivalente(i_casa)];
			tabuleiro[Equivalente(i_casa)] = 0;
			tabuleiro[i_casa] = 0;
			tabuleiro[6] = tabuleiro[6] + soma;
			printf("CAPTUROU!!!! :D\n");
			printf("aperte ENTER para continuar\n");
			getchar();
			getchar();
		}
	}
}


/*São as jogadas usadas quando está montando a arvore, ele nao imprime nada na tela*/
void Jogada2Comp(int i_casa, int *troca, int* tabuleiro) {
	*troca = 0;
	int soma;
	int cont = tabuleiro[i_casa];
	tabuleiro[i_casa] = 0;
	while(cont > 0) {
		if(i_casa == 13) {
			i_casa = 0;
		}
		else {
			i_casa++;
		}
		if(i_casa != 6) {
			tabuleiro[i_casa]++;
			cont--;
		}
	}
	if(i_casa == 13) {
		*troca = 1;
	}
	if((tabuleiro[i_casa] == 1) && (i_casa != 13) && (i_casa > 6)) {
		if(tabuleiro[Equivalente(i_casa)] != 0) {
			soma = tabuleiro[i_casa] + tabuleiro[Equivalente(i_casa)];
			tabuleiro[Equivalente(i_casa)] = 0;
			tabuleiro[i_casa] = 0;
			tabuleiro[13] = tabuleiro[13] + soma;
		}
	}
}


/*São as jogadas usadas no tabuleiro principal, ela mostra na tela algumas mensagens explicando o que aconteceu*/
void Jogada2(int i_casa, int *troca, int* tabuleiro) {
	*troca = 0;
	int soma;
	int cont = tabuleiro[i_casa];
	tabuleiro[i_casa] = 0;
	while(cont > 0) {
		if(i_casa == 13) {
			i_casa = 0;
		}
		else {
			i_casa++;
		}
		if(i_casa != 6) {
			tabuleiro[i_casa]++;
			cont--;
		}
	}
	if(i_casa == 13) {
		*troca = 1;
		printf("JOGADOR 2, JOGUE NOVAMENTE :D\n");
		printf("aperte ENTER para continuar\n");
		getchar();
		getchar();
	}
	if((tabuleiro[i_casa] == 1) && (i_casa != 13) && (i_casa > 6)) {
		if(tabuleiro[Equivalente(i_casa)] != 0) {
			soma = tabuleiro[i_casa] + tabuleiro[Equivalente(i_casa)];
			tabuleiro[Equivalente(i_casa)] = 0;
			tabuleiro[i_casa] = 0;
			tabuleiro[13] = tabuleiro[13] + soma;
			printf("CAPTUROU!!!! :D\n");
			printf("aperte ENTER para continuar\n");
			getchar();
			getchar();
		}
	}
}


/*Apos o jogo acabar, ela passa todas as pessas remanescentes no campo para suas respectivas Kahalas, porem nessa ele não analisa se houve um vencedor*/
void PontoFinalComp(int* tabuleiro) {
	int soma = 0;
	int i;
	for(i=12;i>6;i--) {
		soma = soma + tabuleiro[i];
	}
	tabuleiro[13] = tabuleiro[13] + soma;
	soma = 0;
	for(i=0;i<6;i++) {
		soma = soma + tabuleiro[i];
	}
	tabuleiro[6] = tabuleiro[6] + soma;
}


/*Apos o jogo acabar, ela passa todas as pessas remanescentes no campo para suas respectivas Kahalas, e ela informa quem ganhou*/
void PontoFinal(int* tabuleiro) {
	int soma = 0;
	int i;
	for(i=12;i>6;i--) {
		soma = soma + tabuleiro[i];
	}
	tabuleiro[13] = tabuleiro[13] + soma;
	soma = 0;
	for(i=0;i<6;i++) {
		soma = soma + tabuleiro[i];
	}
	tabuleiro[6] = tabuleiro[6] + soma;
	system("clear || cls");
	printf("\n\n\n");
	if(tabuleiro[6] > tabuleiro[13]) {
		printf("JOGADOR 1 FOI O VENCEDOR!!!\n");
	}
	else {
		if(tabuleiro[6] < tabuleiro[13]) {
			printf("JOGADOR 2 FOI O VENCEDOR!!!\n");
		}
		else {
			printf("HOUVE UM EMPATE!!!\n");
		}
	}
	printf("JOGADOR 1: %d PONTOS!\tJOGADOR 2: %d PONTOS!\n", tabuleiro[6], tabuleiro[13]);

}


/*Essa é a função usada para montar toda a arvore, ela recebe a altura maxima da arvore(lim), a raiz, o jogador, e a casa em que se deseja jogar naquele no*/
void criarArvore(t_no * raiz, int jogador, int cont, int lim, int casa) { /*apos entrar na função, a jogada é realizada para a devida casa enviada*/
	int troca;
	raiz->jogador = jogador;
	if (casa != -1) {
	   if(jogador == 1) {
			Jogada1Comp(casa, &troca, raiz->tab);
		}
		else {
			Jogada2Comp(casa, &troca, raiz->tab);
		}
		if(troca == 0) {
			if(jogador == 1) {
				jogador = 2;
			}
			else {
				jogador = 1;
			}
		}
	}
	if(jogador == raiz->jogador) {
		raiz->jogarn = 1;
	}
	else {
		raiz->jogarn = 0;
	}
	if ((cont < lim) && (Fim(raiz->tab) == 0)) { /*e apos isso ela cria outras nos, se houver novas jogadas possiveis*/
		if (jogador == 2) {
			if(raiz->tab[7] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->um = n;
				criarArvore(raiz->um, jogador, (cont + 1), lim, 7); 
			}
			if(raiz->tab[8] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->dois = n;
				criarArvore(raiz->dois, jogador, (cont + 1), lim, 8);
			}
			if(raiz->tab[9] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->tres = n;
				criarArvore(raiz->tres, jogador, (cont + 1), lim, 9);
			}
			if(raiz->tab[10] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->quatro = n;
				criarArvore(raiz->quatro, jogador, (cont + 1), lim, 10);
			}
			if(raiz->tab[11] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->cinco = n;
				criarArvore(raiz->cinco, jogador, (cont + 1), lim, 11);
			}
			if(raiz->tab[12] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->seis = n; 
				criarArvore(raiz->seis, jogador, (cont + 1), lim, 12);
			}
		}
		else {
			if(raiz->tab[0] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->um = n;
				criarArvore(raiz->um, jogador, (cont + 1), lim, 0);
			}
			if(raiz->tab[1] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->dois = n;
				criarArvore(raiz->dois, jogador, (cont + 1), lim, 1);
			}
			if(raiz->tab[2] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->tres = n;
				criarArvore(raiz->tres, jogador, (cont + 1), lim, 2);
			}
			if(raiz->tab[3] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->quatro = n;
				criarArvore(raiz->quatro, jogador, (cont + 1), lim, 3);
			}
			if(raiz->tab[4] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->cinco = n;
				criarArvore(raiz->cinco, jogador, (cont + 1), lim, 4);
			}
			if(raiz->tab[5] != 0) {
				t_no *n = criarNo(raiz->tab);
				raiz->seis = n;
				criarArvore(raiz->seis, jogador, (cont + 1), lim, 5);
			}
		}
	}
	else {
		raiz->um = NULL;
		raiz->dois = NULL;
		raiz->tres = NULL;
		raiz->quatro = NULL;
		raiz->cinco = NULL;
		raiz->seis = NULL;
		if(Fim(raiz->tab) != 0) {
			PontoFinalComp(raiz->tab);
		}
	}
}


int minimaxFacil(t_no* raiz, int inicio) {/*essa é uma versão da minimax que nao leva em conta o que o jogador pensou, e se ele joga novamente*/
	int a, b, c, d, e, f;
	if (inicio == 1) { /*essa parte é a parte que retorna para a main, ela vai retorna o ramo que recebe o maior numero*/
		if(raiz->um != NULL) {
			a = minimaxFacil(raiz->um, 0);
		}
		else{
			a = 0;
		}
		if(raiz->dois != NULL) {
			b = minimaxFacil(raiz->dois, 0);
		}
		else{
			b = 0;
		}
		if(raiz->tres != NULL) {
			c = minimaxFacil(raiz->tres, 0);
		}
		else{
			c = 0;
		}
		if(raiz->quatro != NULL) {
			d = minimaxFacil(raiz->quatro, 0);
		}
		else{
			d = 0;
		}
		if(raiz->cinco != NULL) {
			e = minimaxFacil(raiz->cinco, 0);
		}
		else{
			e = 0;
		}
		if(raiz->seis != NULL) {
			f = minimaxFacil(raiz->seis, 0);
		}
		else{
			f = 0;
		}
		if(raiz->um != NULL) {
			if ((a >= b) && (a >= c) && (a >= d) && (a >= e) && (a >= f)) {
				return 1;
			}
		}
		if(raiz->dois != NULL) {
			if ((b >= a) && (b >= c) && (b >= d) && (b >= e) && (b >= f)) {
				return 2;
			}
		}
		if(raiz->tres != NULL) {
			if ((c >= b) && (c >= a) && (c >= d) && (c >= e) && (c >= f)) {
				return 3;
			}
		}
		if(raiz->quatro != NULL) {
			if ((d >= b) && (d >= c) && (d >= a) && (d >= e) && (d >= f)) {
				return 4;
			}
		}
		if(raiz->cinco != NULL) {
			if ((e >= b) && (e >= c) && (e >= d) && (e >= a) && (e >= f)) {
				return 5;
			}
		}
		if(raiz->seis != NULL) {
			if ((f >= b) && (f >= c) && (f >= d) && (f >= e) && (f >= a)) {
				return 6;
			}
		}
		return -1;

	}
	else {
		
		if(raiz->um != NULL) { /*essa é a parte que ele retorna a soma dos ramos*/
			a = minimaxFacil(raiz->um, 0);
		}
		else{
			a = 0;
		}
		if(raiz->dois != NULL) {
			b = minimaxFacil(raiz->dois, 0);
		}
		else{
			b = 0;
		}
		if(raiz->tres != NULL) {
			c = minimaxFacil(raiz->tres, 0);
		}
		else{
			c = 0;
		}
		if(raiz->quatro != NULL) {
			d = minimaxFacil(raiz->quatro, 0);
		}
		else{
			d = 0;
		}
		if(raiz->cinco != NULL) {
			e = minimaxFacil(raiz->cinco, 0);
		}
		else{
			e = 0;
		}
		if(raiz->seis != NULL) {
			f = minimaxFacil(raiz->seis, 0);
		}
		else{
			f = 0;
		}
		if(raiz->um != NULL) {
			if ((a >= b) && (a >= c) && (a >= d) && (a >= e) && (a >= f)) {
				return minimaxFacil(raiz->um, 0);
			}
		}
		if(raiz->dois != NULL) {
			if ((b >= a) && (b >= c) && (b >= d) && (b >= e) && (b >= f)) {
				return minimaxFacil(raiz->dois, 0);
			}
		}
		if(raiz->tres != NULL) {
			if ((c >= b) && (c >= a) && (c >= d) && (c >= e) && (c >= f)) {
				return minimaxFacil(raiz->tres, 0);
			}
		}
		if(raiz->quatro != NULL) {
			if ((d >= b) && (d >= c) && (d >= a) && (d >= e) && (d >= f)) {
				return minimaxFacil(raiz->quatro, 0);
			}
		}
		if(raiz->cinco != NULL) {
			if ((e >= b) && (e >= c) && (e >= d) && (e >= a) && (e >= f)) {
				return minimaxFacil(raiz->cinco, 0);
			}
		}
		if(raiz->seis != NULL) {
			if ((f >= b) && (f >= c) && (f >= d) && (f >= e) && (f >= a)) {
				return minimaxFacil(raiz->seis, 0);
			}
		}
		return a + b + c + d + e;
	}

}

/*Essa função é usada para percorrer a arvore criada e informar qual a melhor jogada para o computador*/
int minimax(t_no* raiz, int inicio) {
	int a, b, c, d, e, f;
	if (inicio == 1) { /*essa parte é a parte que retorna para a main, ela vai retornar o ramo q recebe o maior numero*/
	/*parte para ver se em alguma opção joga novamente*/
		if(raiz->seis != NULL) {
			if(raiz->seis->jogarn == 1) {
				return 6;
			}
		}
		if(raiz->cinco != NULL) {
			if(raiz->cinco->jogarn == 1) {
				return 5;
			}
		}
		if(raiz->quatro != NULL) {
			if(raiz->quatro->jogarn == 1) {
				return 4;
			}
		}
		if(raiz->tres != NULL) {
			if(raiz->tres->jogarn == 1) {
				return 3;
			}
		}
		if(raiz->dois != NULL) {
			if(raiz->dois->jogarn == 1) {
				return 2;
			}
		}
		if(raiz->um != NULL) {
			if(raiz->um->jogarn == 1) {
				return 1;
			}
		}
		/*parte q monta a arvore se em nenhuma opção ele joga novamente*/
		if(raiz->um != NULL) {
			a = minimax(raiz->um, 0);
		}
		else{
			a = 0;
		}
		if(raiz->dois != NULL) {
			b = minimax(raiz->dois, 0);
		}
		else{
			b = 0;
		}
		if(raiz->tres != NULL) {
			c = minimax(raiz->tres, 0);
		}
		else{
			c = 0;
		}
		if(raiz->quatro != NULL) {
			d = minimax(raiz->quatro, 0);
		}
		else{
			d = 0;
		}
		if(raiz->cinco != NULL) {
			e = minimax(raiz->cinco, 0);
		}
		else{
			e = 0;
		}
		if(raiz->seis != NULL) {
			f = minimax(raiz->seis, 0);
		}
		else{
			f = 0;
		}
		if(raiz->um != NULL) {
			if ((a >= b) && (a >= c) && (a >= d) && (a >= e) && (a >= f)) {
				return 1;
			}
		}
		if(raiz->dois != NULL) {
			if ((b >= a) && (b >= c) && (b >= d) && (b >= e) && (b >= f)) {
				return 2;
			}
		}
		if(raiz->tres != NULL) {
			if ((c >= b) && (c >= a) && (c >= d) && (c >= e) && (c >= f)) {
				return 3;
			}
		}
		if(raiz->quatro != NULL) {
			if ((d >= b) && (d >= c) && (d >= a) && (d >= e) && (d >= f)) {
				return 4;
			}
		}
		if(raiz->cinco != NULL) {
			if ((e >= b) && (e >= c) && (e >= d) && (e >= a) && (e >= f)) {
				return 5;
			}
		}
		if(raiz->seis != NULL) {
			if ((f >= b) && (f >= c) && (f >= d) && (f >= e) && (f >= a)) {
				return 6;
			}
		}
		return -1;

	}
	else {
		if((raiz->um == NULL) && (raiz->dois == NULL) && (raiz->tres == NULL) && (raiz->quatro == NULL) &&(raiz->cinco == NULL) && (raiz->seis == NULL)) {
			 int diferenca = raiz->tab[13] - raiz->tab[6]; /*se for uma folha, ela retorna a diferença entre as casas*/
			 return diferenca;
		}

		/*parte para ver se em alguma opção joga novamente*/
		if(raiz->seis != NULL) {
			if(raiz->seis->jogarn == 1) {
				return minimax(raiz->seis, 0);
			}
		}
		if(raiz->cinco != NULL) {
			if(raiz->cinco->jogarn == 1) {
				return minimax(raiz->cinco, 0);
			}
		}
		if(raiz->quatro != NULL) {
			if(raiz->quatro->jogarn == 1) {
				return minimax(raiz->quatro, 0);
			}
		}
		if(raiz->tres != NULL) {
			if(raiz->tres->jogarn == 1) {
				return minimax(raiz->tres, 0);
			}
		}
		if(raiz->dois != NULL) {
			if(raiz->dois->jogarn == 1) {
				return minimax(raiz->dois, 0);
			}
		}
		if(raiz->um != NULL) {
			if(raiz->um->jogarn == 1) {
				return minimax(raiz->um, 0);
			}
		}

		if(raiz->jogador == 1) {
			a = raiz->um->tab[6];
			b = raiz->dois->tab[6];
			c = raiz->tres->tab[6];
			d = raiz->quatro->tab[6];
			e = raiz->cinco->tab[6];
			f = raiz->seis->tab[6];
			if(raiz->um != NULL) {
				if ((a >= b) && (a >= c) && (a >= d) && (a >= e) && (a >= f)) {
					return minimax(raiz->um, 0);
				}
			}
			if(raiz->dois != NULL) {
				if ((b >= a) && (b >= c) && (b >= d) && (b >= e) && (b >= f)) {
					return minimax(raiz->dois, 0);
				}
			}
			if(raiz->tres != NULL) {
				if ((c >= b) && (c >= a) && (c >= d) && (c >= e) && (c >= f)) {
					return minimax(raiz->tres, 0);
				}
			}
			if(raiz->quatro != NULL) {
				if ((d >= b) && (d >= c) && (d >= a) && (d >= e) && (d >= f)) {
					return minimax(raiz->quatro, 0);
				}
			}
			if(raiz->cinco != NULL) {
				if ((e >= b) && (e >= c) && (e >= d) && (e >= a) && (e >= f)) {
					return minimax(raiz->cinco, 0);
				}
			}
			if(raiz->seis != NULL) {
				if ((f >= b) && (f >= c) && (f >= d) && (f >= e) && (f >= a)) {
					return minimax(raiz->seis, 0);
				}
			}
		}
		if(raiz->um != NULL) { /*essa é a parte q ele retorna a soma dos ramos*/
			a = minimax(raiz->um, 0);
		}
		else{
			a = 0;
		}
		if(raiz->dois != NULL) {
			b = minimax(raiz->dois, 0);
		}
		else{
			b = 0;
		}
		if(raiz->tres != NULL) {
			c = minimax(raiz->tres, 0);
		}
		else{
			c = 0;
		}
		if(raiz->quatro != NULL) {
			d = minimax(raiz->quatro, 0);
		}
		else{
			d = 0;
		}
		if(raiz->cinco != NULL) {
			e = minimax(raiz->cinco, 0);
		}
		else{
			e = 0;
		}
		if(raiz->seis != NULL) {
			f = minimax(raiz->seis, 0);
		}
		else{
			f = 0;
		}
		if(raiz->um != NULL) {
			if ((a >= b) && (a >= c) && (a >= d) && (a >= e) && (a >= f)) {
				return minimax(raiz->um, 0);
			}
		}
		if(raiz->dois != NULL) {
			if ((b >= a) && (b >= c) && (b >= d) && (b >= e) && (b >= f)) {
				return minimax(raiz->dois, 0);
			}
		}
		if(raiz->tres != NULL) {
			if ((c >= b) && (c >= a) && (c >= d) && (c >= e) && (c >= f)) {
				return minimax(raiz->tres, 0);
			}
		}
		if(raiz->quatro != NULL) {
			if ((d >= b) && (d >= c) && (d >= a) && (d >= e) && (d >= f)) {
				return minimax(raiz->quatro, 0);
			}
		}
		if(raiz->cinco != NULL) {
			if ((e >= b) && (e >= c) && (e >= d) && (e >= a) && (e >= f)) {
				return minimax(raiz->cinco, 0);
			}
		}
		if(raiz->seis != NULL) {
			if ((f >= b) && (f >= c) && (f >= d) && (f >= e) && (f >= a)) {
				return minimax(raiz->seis, 0);
			}
		}
		return a + b + c + d + e;
	}

}


int main() {
	int tabuleiro[14];
	int jogador = 1;
	int casa;
	int i_casa;
	int troca;
	int computador;
	int lim;
	CriarTab(tabuleiro);
	menu(&computador, &lim);
	t_no *raiz = criarNo(tabuleiro);
	while(Fim(tabuleiro) == 0) { /*enquanto o jogo nao acaba ele repete o processo*/
		Tela(jogador, tabuleiro);
		if(computador == 1) {
			scanf("%d", &casa);
		}
		else {
			if (jogador == 1) {
				scanf("%d", &casa);
			}
			else { /*caso seja a vez do computador ele executa esses passos*/
				resetaRaiz(raiz, tabuleiro);
				criarArvore(raiz, jogador, 1, lim, -1);
				if (computador == 2) {
					casa = minimaxFacil(raiz, 1);
				}
				else {
					casa = minimax(raiz, 1);
				}
				printf("\n");
				printf("Jogador 2, jogou a casa de numero %d\n", casa);
				printf("contendo %d pedrinhas\n", tabuleiro[I_casa(casa, jogador)]);
				getchar();
				getchar();
			}
		}
		while(((casa > 6) || (casa < 0)) || (tabuleiro[I_casa(casa, jogador)] == 0)) {
			printf("ERROR\n");
			printf("Digite uma casa valida!\n");
			scanf("%d", &casa);
		}
		i_casa = I_casa(casa, jogador);
		if(jogador == 1) { /*a jogada é executada para o jogador 1*/
			Jogada1(i_casa, &troca, tabuleiro);
		}
		else { /*a jogada é executada para o jogador 2*/
			Jogada2(i_casa, &troca, tabuleiro);
		}
		if(troca == 0) { /*se troca for 0 ele troca o jogador, se n, o jogador joga novamente*/
			if(jogador == 1) {
				jogador = 2;
			}
			else {
				jogador = 1;
			}
		}
	}
	PontoFinal(tabuleiro);
	return 0;
}