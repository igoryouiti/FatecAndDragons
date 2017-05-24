
#pragma once
// defições do programa
//
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

// definições do sistema
#define VOLTAR			'V'		// voltar nas escolhas de ações

// definições dados
#define D4				4		// dado de 4 faces
#define D6				6		// dado de 6 faces
#define D8				8		// dado de 8 faces
#define D10				10		// dado de 10 faces
#define D20				20		// dado de 20 faces

// definições itens --- cada item só aumenta um atributo na luta
#define CURA		'C'			// item tipo cura
#define BUFF		'B'			// item tipo buff
#define DANO		'D'			// item tipo dano

// definições habilidades/poder do heroi
#define AUMENTAR_FORÇA		'E'			// aumenta a força em lvl
#define ULTIMATE			'R'			// da 10 dano + dano arma + lvl
#define GOLPE_PODEROSO		'Q'			// da lvl + dano arma
#define CABECADA			'W'			// da lvl*2 dano e toma metade desse dano

// definições de equipamentos
//#define ARMA							// da dano d4 a d10 pode aumentar inteligencia...
//#define ARMADURA						// aumenta C.A. (classe armadura), pode diminuir destreza

// definições de combates
#define ATACAR				1
#define PODER				2
#define USARITEM			3

// definições de dungeon
#define TAMANHODUNGEON		3

//definição de lvl
#define BONUSDELVL		1
#define DEFICULLVL		3

// layout struct do heroi
typedef struct tagHeroi
{
	string strNome;
	int nExp;
	int nForca;						// influencia no dano
	int nConstituicao;				// influencia na vida ao ganhar lvl
	int nDestreza;					// influencia na esquiva
									// int nInteligencia;			provisório
	int nDanoArma;
	int nDanoExtra;
	int nVida;
	int nLvl;						// level do heroi
	int nCA;						// classe de armadura --  Destreza + Armadura
	int nCAArmadura;

	int nCodigoArma;
	int nCodigoArmadura;

}HEROI;


// layout struct do monstro
typedef struct tagMonstro
{
	string strNome;
	int nExp;
	int nForca;						// influencia no dano
	int nConstituicao;				// influencia na vida ao ganhar lvl
	int nDestreza;					// influencia na esquiva
									// int nInteligencia;			provisório
	int nDanoArma;
	int nVida;
	int nLvl;						// level do monstro
	int nCA;						// classe de armadura --  Destreza + Armadura

	int nCodigo;
	int vetCodigo[];

}MONSTRO;

typedef struct tagArma
{
	string strNome;
	int nDanoArma;
	int nCodigo;
	int nlvl;
	int nDanoExtra;
	int vetCodigo[];

}ARMA;
typedef struct tagArmadura
{
	string strNome;
	int nCAArmadura;
	int nCodigo;
	int nlvl;

}ARMADURA;
typedef struct tagItem
{
	string strNome;
	char cTipoItem;
	int nEfeito;
	int nCodigo;

}ITEM;




// funções

// Função RolagemDados, faz simulação de rolagem de dados aleatórios com rand
//		Parâmetros: int nDado - recebe valor de qual dado será rolado - o
//						módulo do número aleatório pelo nDado mais um será o resultado da rolagem
//		Retorno: nResultado - retorna o resultado da rolagem do dado

// função para dar clear
void LIMPAR_TELA()
{
	cout << string(100, '\n');
}

int RolagemDados(int nDado)
{
	int nResultado;

	nResultado = 1 + rand() % nDado;

	return nResultado;
}

int UsoItem(ITEM *ptrWorkItem)			/// nao feito ainda
{
	char cOpcao;

	cout << "Escolha um item:" << endl;
	cout << CURA << " - Pocao de cura" << endl;
	cout << VOLTAR << " - para voltar";
	cin >> cOpcao;
	cOpcao = toupper(cOpcao);

	switch (cOpcao)
	{
	case CURA:
		return (RolagemDados(ptrWorkItem->nEfeito));

	case VOLTAR:
		break;

	default:
		cout << "\n\tDigite uma opção válida!" << endl << "\t";
		getchar();
	}
	return 0;
}

// Função do poder heroico - o que cada poder irá realizar na batalha
//		Parâmetros: char cHabilidade - nome da habilidade
//					int nlvl - level do heroi
//					int nDanoArma - Dado de dano da arma
//					HEROI *ptrWorkHeroi - recebe ponteiro do WorkHeroi criado na batalha
//		retorno: int - Dano que causará no oponente
int PoderHeroi(int nDanoArma, HEROI *ptrWorkHeroi)
{
	char cOpcao;

	cout << "Escolha o poder heroico:" << endl;
	cout << GOLPE_PODEROSO << " - Golpe poderoso" << endl;
	cout << CABECADA << " - Cabecada" << endl;
	cout << AUMENTAR_FORÇA << " - Aumentar a forca" << endl;
	if (ptrWorkHeroi->nVida <= ptrWorkHeroi->nVida * 0, 25)
		cout << ULTIMATE << " - Ultimate" << endl;
	cout << VOLTAR << " - para voltar";
	cin >> cOpcao;
	cOpcao = toupper(cOpcao);

	switch (cOpcao)
	{
	case GOLPE_PODEROSO:
		return (ptrWorkHeroi->nLvl + RolagemDados(nDanoArma) + ptrWorkHeroi->nDanoExtra);

	case CABECADA:
		ptrWorkHeroi->nVida -= ptrWorkHeroi->nLvl;
		return (ptrWorkHeroi->nLvl * 2);

	case AUMENTAR_FORÇA:
		ptrWorkHeroi->nForca += ptrWorkHeroi->nLvl;
		return 0;

	case ULTIMATE:
		return(10 + ptrWorkHeroi->nLvl + RolagemDados(nDanoArma) + ptrWorkHeroi->nDanoExtra);

	case VOLTAR:
		break;

	default:
		cout << "\n\tDigite uma opção válida!" << endl << "\t";
		getchar();
	}
}


// Função para o ataque do heroi
int AtaqueHeroi(HEROI *ptrWorkHeroi, MONSTRO *ptrWorkMonstro, int nDanoArma)
{
	if (RolagemDados(D20) >= ptrWorkMonstro->nCA)
		return (nDanoArma + ptrWorkHeroi->nForca + ptrWorkHeroi->nDanoExtra);
	else
		return 0;

}

// função para o ataque do monstro
int AtaqueMonstro(HEROI *ptrWorkHeroi, MONSTRO *ptrWorkMonstro, int nDanoArma)
{
	if (RolagemDados(D20) >= ptrWorkHeroi->nCA + ptrWorkHeroi->nCAArmadura)
		return (nDanoArma + ptrWorkMonstro->nForca);
	else
		return 0;

}

//
// verifica iniciativa da batalha
// Parâmetros: 
//		Entrada: HEROI *ptrWorkHeroi - structWork para heroi
//				MONSTRO *ptrWorkMonstro - idem para monstro
//		Saída: true - Heroi ganhou a iniciativa, se a destreza for maior a do monstro
//				false - Heroi perde a iniciativa, se a destreza for menor ou igual a do monstro

bool Iniciativa(HEROI *ptrWorkHeroi, MONSTRO *ptrWorkMonstro)
{
	if (ptrWorkHeroi->nDestreza + ptrWorkHeroi->nLvl > ptrWorkMonstro->nDestreza + ptrWorkMonstro->nLvl)
		return true;
	else
		return false;
} 


// função para a luta
bool Luta(HEROI *ptrWorkHeroi, MONSTRO *ptrWorkMonstro, ITEM *ptrWorkItem, bool flgIniciativa, int nDanoArma, int nDanoArmaMonstro, int nVidaItem)
{
	int nAcao;		// recebe ação do heroi
	int nDanoHeroi; // recebe o dano que o heroi vai causar
	int nDanoMonstro;	// recebe o dano que o monstro vai causar
	int nBuffItem;	//recebe o buff do item
	bool flgAcabou = false,	// acabou a luta
		flgVitoria;			//quem venceu?

	do
	{
		if (flgIniciativa == true)
		{
			cout << "Combate, escolha a sua ação:" << endl;
			cout << ATACAR << " - Atacar" << endl;
			cout << PODER << " - Poder" << endl;
			cout << USARITEM << " - Item" << endl;
			cin >> nAcao;

			switch (nAcao)
			{
			case ATACAR:
				nDanoHeroi = AtaqueHeroi(ptrWorkHeroi, ptrWorkMonstro, nDanoArma);
				cout << "Voce causou " << nDanoHeroi << " no monstro" << endl;
				break;

			case PODER:
				nDanoHeroi = PoderHeroi(nDanoArma, ptrWorkHeroi);
				cout << "Voce causou " << nDanoHeroi << " no monstro" << endl;
				break;

			case USARITEM:
				nVidaItem = UsoItem(ptrWorkItem);
				ptrWorkHeroi->nVida += nVidaItem;
				cout << "Voce recuperou " << nVidaItem << " de vida" << endl;
				cout << "Vida total: " << ptrWorkHeroi->nVida << endl;
				break;

			default:
				cout << "\n\tDigite uma opção válida!" << endl << "\t";
				getchar();
				break;
			}	// switch ação heroi
			ptrWorkMonstro->nVida -= nDanoHeroi;
			if (ptrWorkMonstro->nVida < 1)
			{
				flgAcabou = true;
				flgVitoria = true;
			}

			flgIniciativa = false;
		}
		else
		{
			nDanoMonstro = AtaqueMonstro(ptrWorkHeroi, ptrWorkMonstro, nDanoArmaMonstro);			// monstro ta só atacando, não usa itens nem habilidade
			cout << "O monstro causou " << nDanoMonstro << " em sua vida" << endl;
			cout << "Vida total: " << ptrWorkHeroi->nVida << endl;

			ptrWorkHeroi->nVida -= nDanoMonstro;
			if (ptrWorkHeroi->nVida < 1)
			{
				flgAcabou = true;
				flgVitoria = false;
			}
			flgIniciativa = true;

		}
	} while (flgAcabou == false);
	return flgVitoria;



}
bool CompararItens(int ItemEquip, int ItemNovo)
{
	if (ItemEquip == ItemNovo)
	{
		cout << "Voce ja possui um item igual a esse" << endl
			<< "Ele sera descartado" << endl;
		getchar();
		return true;
	}
	else
		return false;
}
void Teste(HEROI *ptrWorkHeroi, MONSTRO *ptrWorkMonstro, ITEM *ptrWorkItem, ARMA *ptrWorkArma, ARMADURA *ptrWorkArmadura)
{

	//Heroi
	ptrWorkHeroi->nExp = 0;
	ptrWorkHeroi->nCA = 5;
	ptrWorkHeroi->nForca = 5;
	ptrWorkHeroi->nDestreza = 5;
	ptrWorkHeroi->nConstituicao = 5;
	ptrWorkHeroi->nVida = 500;
	ptrWorkHeroi->nLvl = 1;
	ptrWorkHeroi->nCodigoArma = 0;
	ptrWorkHeroi->nCodigoArmadura = 0;
	ptrWorkHeroi->nDanoArma = D4;
	ptrWorkHeroi->nCAArmadura = 1;
	ptrWorkHeroi->nDanoExtra = 0;




	//Monstros
	//lvl 1
	ptrWorkMonstro->nCA = 5;
	ptrWorkMonstro->nCodigo = 1;
	ptrWorkMonstro->nExp = 3;
	ptrWorkMonstro->nLvl = 1;
	ptrWorkMonstro->nVida = 30;
	ptrWorkMonstro->nDanoArma = D6;
	ptrWorkMonstro->nForca = 3;
	ptrWorkMonstro->nDestreza = 5;
	ptrWorkMonstro->nConstituicao = 2;
	ptrWorkMonstro->strNome = "Goblin";

	/*ptrWorkMonstro->nCA = 5;
	ptrWorkMonstro->nCodigo = 2;
	ptrWorkMonstro->nExp = 2;
	ptrWorkMonstro->nLvl = 1;
	ptrWorkMonstro->nVida = 15;
	ptrWorkMonstro->nDanoArma = D4;
	ptrWorkMonstro->nForca = 2;
	ptrWorkMonstro->nDestreza = 8;
	ptrWorkMonstro->nConstituicao = 1;
	ptrWorkMonstro->strNome = "Aranha";

	ptrWorkMonstro->nCA = 6;
	ptrWorkMonstro->nCodigo = 3;
	ptrWorkMonstro->nExp = 8;
	ptrWorkMonstro->nLvl = 1;
	ptrWorkMonstro->nVida = 60;
	ptrWorkMonstro->nDanoArma = D8;
	ptrWorkMonstro->nForca = 5;
	ptrWorkMonstro->nDestreza = 5;
	ptrWorkMonstro->nConstituicao = 2;
	ptrWorkMonstro->strNome = "Goblin Chefe";

	ptrWorkMonstro->nCA = 5;
	ptrWorkMonstro->nCodigo = 4;
	ptrWorkMonstro->nExp = 6;
	ptrWorkMonstro->nLvl = 1;
	ptrWorkMonstro->nVida = 30;
	ptrWorkMonstro->nDanoArma = D6;
	ptrWorkMonstro->nForca = 3;
	ptrWorkMonstro->nDestreza = 7;
	ptrWorkMonstro->nConstituicao = 2;
	ptrWorkMonstro->strNome = "Aranha Pintada";

	//lvl 2

	ptrWorkMonstro->nCA = 8;
	ptrWorkMonstro->nCodigo = 5;
	ptrWorkMonstro->nExp = 10;
	ptrWorkMonstro->nLvl = 2;
	ptrWorkMonstro->nVida = 70;
	ptrWorkMonstro->nDanoArma = D8;
	ptrWorkMonstro->nForca = 10;
	ptrWorkMonstro->nDestreza = 7;
	ptrWorkMonstro->nConstituicao = 5;
	ptrWorkMonstro->strNome = "Orc";

	ptrWorkMonstro->nCA = 10;
	ptrWorkMonstro->nCodigo = 6;
	ptrWorkMonstro->nExp = 20;
	ptrWorkMonstro->nLvl = 2;
	ptrWorkMonstro->nVida = 80;
	ptrWorkMonstro->nDanoArma = D8;
	ptrWorkMonstro->nForca = 15;
	ptrWorkMonstro->nDestreza = 8;
	ptrWorkMonstro->nConstituicao = 8;
	ptrWorkMonstro->strNome = "Orc Chefe";

	ptrWorkMonstro->nCA = 8;
	ptrWorkMonstro->nCodigo = 7;
	ptrWorkMonstro->nExp = 20;
	ptrWorkMonstro->nLvl = 2;
	ptrWorkMonstro->nVida = 100;
	ptrWorkMonstro->nDanoArma = D10;
	ptrWorkMonstro->nForca = 10;
	ptrWorkMonstro->nDestreza = 2;
	ptrWorkMonstro->nConstituicao = 12;
	ptrWorkMonstro->strNome = "Troll";

	ptrWorkMonstro->nCA = 15;
	ptrWorkMonstro->nCodigo = 8;
	ptrWorkMonstro->nExp = 15;
	ptrWorkMonstro->nLvl = 2;
	ptrWorkMonstro->nVida = 20;
	ptrWorkMonstro->nDanoArma = D20;
	ptrWorkMonstro->nForca = 3;
	ptrWorkMonstro->nDestreza = 8;
	ptrWorkMonstro->nConstituicao = 1;
	ptrWorkMonstro->strNome = "Brxa Aprendiz";

	//lvl 3

	ptrWorkMonstro->nCA = 40;
	ptrWorkMonstro->nCodigo = 9;
	ptrWorkMonstro->nExp = 100;
	ptrWorkMonstro->nLvl = 3;
	ptrWorkMonstro->nVida = 50;
	ptrWorkMonstro->nDanoArma = D20;
	ptrWorkMonstro->nForca = 10;
	ptrWorkMonstro->nDestreza = 25;
	ptrWorkMonstro->nConstituicao = 1;
	ptrWorkMonstro->strNome = "Bruxa Ancia";
*/
/*
	ptrWorkMonstro->nCA = 30;
	ptrWorkMonstro->nCodigo = 10;
	ptrWorkMonstro->nExp = 100;
	ptrWorkMonstro->nLvl = 3;
	ptrWorkMonstro->nVida = 150;
	ptrWorkMonstro->nDanoArma = D10;
	ptrWorkMonstro->nForca = 40;
	ptrWorkMonstro->nDestreza = 15;
	ptrWorkMonstro->nConstituicao = 20;
	ptrWorkMonstro->strNome = "Dragao Jovem";

	ptrWorkMonstro->nCA = 20;
	ptrWorkMonstro->nCodigo = 11;
	ptrWorkMonstro->nExp = 150;
	ptrWorkMonstro->nLvl = 3;
	ptrWorkMonstro->nVida = 200;
	ptrWorkMonstro->nDanoArma = D6;
	ptrWorkMonstro->nForca = 3;
	ptrWorkMonstro->nDestreza = 5;
	ptrWorkMonstro->nConstituicao = 40;
	ptrWorkMonstro->strNome = "Gigante Maligno";

	ptrWorkMonstro->nCA = 30;
	ptrWorkMonstro->nCodigo = 12;
	ptrWorkMonstro->nExp = 250;
	ptrWorkMonstro->nLvl = 3;
	ptrWorkMonstro->nVida = 200;
	ptrWorkMonstro->nDanoArma = D10;
	ptrWorkMonstro->nForca = 30;
	ptrWorkMonstro->nDestreza = 30;
	ptrWorkMonstro->nConstituicao = 30;
	ptrWorkMonstro->strNome = "Demonio Guardiao";

	//Itens
	*/ptrWorkItem->cTipoItem = 'C';
	ptrWorkItem->nCodigo = 1;
	ptrWorkItem->nEfeito = D8;

	//Espadas
	//lvl 1
	ptrWorkArma->nCodigo = 1;
	ptrWorkArma->nDanoArma = D8;
	ptrWorkArma->strNome = "Espada Longa";
	ptrWorkArma->nlvl = 1;
	ptrWorkArma->nDanoExtra = 0;

	/*ptrWorkArma->nCodigo = 2;
	ptrWorkArma->nDanoArma = D6;
	ptrWorkArma->strNome = "Espada velha";
	ptrWorkArma->nlvl = 1;
	ptrWorkArma->nDanoExtra = 0;

	ptrWorkArma->nCodigo = 3;
	ptrWorkArma->nDanoArma = D10;
	ptrWorkArma->strNome = "Espada bastarda";
	ptrWorkArma->nlvl = 1;
	ptrWorkArma->nDanoExtra = 0;

	ptrWorkArma->nCodigo = 4;
	ptrWorkArma->nDanoArma = D10;
	ptrWorkArma->strNome = "Espada Bastarda do fogo";
	ptrWorkArma->nlvl = 1;
	ptrWorkArma->nDanoExtra = 5;

	//lvl 2
	ptrWorkArma->nCodigo = 5;
	ptrWorkArma->nDanoArma = D8;
	ptrWorkArma->strNome = "Espada Longa Sagrada";
	ptrWorkArma->nlvl = 2;
	ptrWorkArma->nDanoExtra = 10;

	ptrWorkArma->nCodigo = 6;
	ptrWorkArma->nDanoArma = D10;
	ptrWorkArma->strNome = "Espada Do falecido heroi";
	ptrWorkArma->nlvl = 2;
	ptrWorkArma->nDanoExtra = 15;

	ptrWorkArma->nCodigo = 7;
	ptrWorkArma->nDanoArma = D10;
	ptrWorkArma->strNome = "Espada bastarda Salvadora";
	ptrWorkArma->nlvl = 2;
	ptrWorkArma->nDanoExtra = 20;

	ptrWorkArma->nCodigo = 8;
	ptrWorkArma->nDanoArma = D10;
	ptrWorkArma->strNome = "Espada dos Gigantes";
	ptrWorkArma->nlvl = 2;
	ptrWorkArma->nDanoExtra = 30;

	//lvl 3
	ptrWorkArma->nCodigo = 9;
	ptrWorkArma->nDanoArma = D10;
	ptrWorkArma->strNome = "Espada Matadora de Dragoes";
	ptrWorkArma->nlvl = 3;
	ptrWorkArma->nDanoExtra = 40;

	ptrWorkArma->nCodigo = 10;
	ptrWorkArma->nDanoArma = D6;
	ptrWorkArma->strNome = "Adaga Assassina de demonios";
	ptrWorkArma->nlvl = 3;
	ptrWorkArma->nDanoExtra = 50;

	ptrWorkArma->nCodigo = 11;
	ptrWorkArma->nDanoArma = D10;
	ptrWorkArma->strNome = "Machado Destruidor de Almas";
	ptrWorkArma->nlvl = 3;
	ptrWorkArma->nDanoExtra = 60;

	ptrWorkArma->nCodigo = 12;
	ptrWorkArma->nDanoArma = D20;
	ptrWorkArma->strNome = "Espada do Deus do Trovao";
	ptrWorkArma->nlvl = 3;
	ptrWorkArma->nDanoExtra = 100;

	//Armaduras
	//lvl 1
	*/ptrWorkArmadura->nCAArmadura = 5;
	ptrWorkArmadura->nCodigo = 2;
	ptrWorkArmadura->strNome = "Couro Rasgado";
	ptrWorkArmadura->nlvl = 1;

	/*ptrWorkArmadura->nCodigo = 1;
	ptrWorkArmadura->nCAArmadura = 10;
	ptrWorkArmadura->strNome = "Couro Bom";
	ptrWorkArmadura->nlvl = 1;

	ptrWorkArmadura->nCodigo = 3;
	ptrWorkArmadura->nCAArmadura = 8;
	ptrWorkArmadura->strNome = "Couro Usavel";
	ptrWorkArmadura->nlvl = 1;

	ptrWorkArmadura->nCodigo = 4;
	ptrWorkArmadura->nCAArmadura = 12;
	ptrWorkArmadura->strNome = "Armadura de couro do Batedor";
	ptrWorkArmadura->nlvl = 1;

	//lvl 2
	ptrWorkArmadura->nCAArmadura = 20;
	ptrWorkArmadura->nCodigo = 5;
	ptrWorkArmadura->strNome = "Armadura de Aco";
	ptrWorkArmadura->nlvl = 2;

	ptrWorkArmadura->nCodigo = 6;
	ptrWorkArmadura->nCAArmadura = 25;
	ptrWorkArmadura->strNome = "Armadura de Batalha";
	ptrWorkArmadura->nlvl = 2;

	ptrWorkArmadura->nCodigo = 7;
	ptrWorkArmadura->nCAArmadura = 30;
	ptrWorkArmadura->strNome = "Armadura Sagrada";
	ptrWorkArmadura->nlvl = 2;

	ptrWorkArmadura->nCodigo = 8;
	ptrWorkArmadura->nCAArmadura = 40;
	ptrWorkArmadura->strNome = "Armadura de aco Negro";
	ptrWorkArmadura->nlvl = 2;

	//lvl 3
	ptrWorkArmadura->nCAArmadura = 50;
	ptrWorkArmadura->nCodigo = 9;
	ptrWorkArmadura->strNome = "Armadura de couro de dragao";
	ptrWorkArmadura->nlvl = 3;

	ptrWorkArmadura->nCodigo = 10;
	ptrWorkArmadura->nCAArmadura = 55;
	ptrWorkArmadura->strNome = "Armadura do Dragao da guerra";
	ptrWorkArmadura->nlvl = 3;

	ptrWorkArmadura->nCodigo = 11;
	ptrWorkArmadura->nCAArmadura = 65;
	ptrWorkArmadura->strNome = "Armadura Suprema";
	ptrWorkArmadura->nlvl = 3;

	ptrWorkArmadura->nCodigo = 12;
	ptrWorkArmadura->nCAArmadura = 90;
	ptrWorkArmadura->strNome = "Armadura do Deus do Trovao";
	ptrWorkArmadura->nlvl = 3;
	*/
}

void GerarMonstro(int nCodigo, MONSTRO *ptrWorkMonstro)
{
	switch (nCodigo)
	{
	case 1:
		ptrWorkMonstro->nCA = 5;
		ptrWorkMonstro->nCodigo = 1;
		ptrWorkMonstro->nExp = 3;
		ptrWorkMonstro->nLvl = 1;
		ptrWorkMonstro->nVida = 30;
		ptrWorkMonstro->nDanoArma = D6;
		ptrWorkMonstro->nForca = 3;
		ptrWorkMonstro->nDestreza = 5;
		ptrWorkMonstro->nConstituicao = 2;
		ptrWorkMonstro->strNome = "Goblin";
		break;
	case 2:
		ptrWorkMonstro->nCA = 5;
		ptrWorkMonstro->nCodigo = 2;
		ptrWorkMonstro->nExp = 2;
		ptrWorkMonstro->nLvl = 1;
		ptrWorkMonstro->nVida = 15;
		ptrWorkMonstro->nDanoArma = D4;
		ptrWorkMonstro->nForca = 2;
		ptrWorkMonstro->nDestreza = 8;
		ptrWorkMonstro->nConstituicao = 1;
		ptrWorkMonstro->strNome = "Aranha";
		break;
	case 3:
		ptrWorkMonstro->nCA = 6;
		ptrWorkMonstro->nCodigo = 3;
		ptrWorkMonstro->nExp = 8;
		ptrWorkMonstro->nLvl = 1;
		ptrWorkMonstro->nVida = 60;
		ptrWorkMonstro->nDanoArma = D8;
		ptrWorkMonstro->nForca = 5;
		ptrWorkMonstro->nDestreza = 5;
		ptrWorkMonstro->nConstituicao = 2;
		ptrWorkMonstro->strNome = "Goblin Chefe";
		break;
	case 4:
		ptrWorkMonstro->nCA = 5;
		ptrWorkMonstro->nCodigo = 4;
		ptrWorkMonstro->nExp = 6;
		ptrWorkMonstro->nLvl = 1;
		ptrWorkMonstro->nVida = 30;
		ptrWorkMonstro->nDanoArma = D6;
		ptrWorkMonstro->nForca = 3;
		ptrWorkMonstro->nDestreza = 7;
		ptrWorkMonstro->nConstituicao = 2;
		ptrWorkMonstro->strNome = "Aranha Pintada";
		break;
	case 5:
		ptrWorkMonstro->nCA = 8;
		ptrWorkMonstro->nCodigo = 5;
		ptrWorkMonstro->nExp = 10;
		ptrWorkMonstro->nLvl = 2;
		ptrWorkMonstro->nVida = 70;
		ptrWorkMonstro->nDanoArma = D8;
		ptrWorkMonstro->nForca = 10;
		ptrWorkMonstro->nDestreza = 7;
		ptrWorkMonstro->nConstituicao = 5;
		ptrWorkMonstro->strNome = "Orc";
		break;
	case 6:
		ptrWorkMonstro->nCA = 10;
		ptrWorkMonstro->nCodigo = 6;
		ptrWorkMonstro->nExp = 20;
		ptrWorkMonstro->nLvl = 2;
		ptrWorkMonstro->nVida = 80;
		ptrWorkMonstro->nDanoArma = D8;
		ptrWorkMonstro->nForca = 15;
		ptrWorkMonstro->nDestreza = 8;
		ptrWorkMonstro->nConstituicao = 8;
		ptrWorkMonstro->strNome = "Orc Chefe";
		break;
	case 7:
		ptrWorkMonstro->nCA = 8;
		ptrWorkMonstro->nCodigo = 7;
		ptrWorkMonstro->nExp = 20;
		ptrWorkMonstro->nLvl = 2;
		ptrWorkMonstro->nVida = 100;
		ptrWorkMonstro->nDanoArma = D10;
		ptrWorkMonstro->nForca = 10;
		ptrWorkMonstro->nDestreza = 2;
		ptrWorkMonstro->nConstituicao = 12;
		ptrWorkMonstro->strNome = "Troll";
		break;
	case 8:
		ptrWorkMonstro->nCA = 15;
		ptrWorkMonstro->nCodigo = 8;
		ptrWorkMonstro->nExp = 15;
		ptrWorkMonstro->nLvl = 2;
		ptrWorkMonstro->nVida = 20;
		ptrWorkMonstro->nDanoArma = D20;
		ptrWorkMonstro->nForca = 3;
		ptrWorkMonstro->nDestreza = 8;
		ptrWorkMonstro->nConstituicao = 1;
		ptrWorkMonstro->strNome = "Brxa Aprendiz";
		break;
	case 9:
		ptrWorkMonstro->nCA = 40;
		ptrWorkMonstro->nCodigo = 9;
		ptrWorkMonstro->nExp = 100;
		ptrWorkMonstro->nLvl = 3;
		ptrWorkMonstro->nVida = 50;
		ptrWorkMonstro->nDanoArma = D20;
		ptrWorkMonstro->nForca = 10;
		ptrWorkMonstro->nDestreza = 25;
		ptrWorkMonstro->nConstituicao = 1;
		ptrWorkMonstro->strNome = "Bruxa Ancia";
		break;
	case 10:
		ptrWorkMonstro->nCA = 30;
		ptrWorkMonstro->nCodigo = 10;
		ptrWorkMonstro->nExp = 100;
		ptrWorkMonstro->nLvl = 3;
		ptrWorkMonstro->nVida = 150;
		ptrWorkMonstro->nDanoArma = D10;
		ptrWorkMonstro->nForca = 40;
		ptrWorkMonstro->nDestreza = 15;
		ptrWorkMonstro->nConstituicao = 20;
		ptrWorkMonstro->strNome = "Dragao Jovem";
		break;
	case 11:
		ptrWorkMonstro->nCA = 20;
		ptrWorkMonstro->nCodigo = 11;
		ptrWorkMonstro->nExp = 150;
		ptrWorkMonstro->nLvl = 3;
		ptrWorkMonstro->nVida = 200;
		ptrWorkMonstro->nDanoArma = D6;
		ptrWorkMonstro->nForca = 3;
		ptrWorkMonstro->nDestreza = 5;
		ptrWorkMonstro->nConstituicao = 40;
		ptrWorkMonstro->strNome = "Gigante Maligno";
		break;
	case 12:
		ptrWorkMonstro->nCA = 30;
		ptrWorkMonstro->nCodigo = 12;
		ptrWorkMonstro->nExp = 250;
		ptrWorkMonstro->nLvl = 3;
		ptrWorkMonstro->nVida = 200;
		ptrWorkMonstro->nDanoArma = D10;
		ptrWorkMonstro->nForca = 30;
		ptrWorkMonstro->nDestreza = 30;
		ptrWorkMonstro->nConstituicao = 30;
		ptrWorkMonstro->strNome = "Demonio Guardiao";
		break;
	}
}
