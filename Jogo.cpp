#include "Meu.h"

void main()
{
	int nExp,
		nEvento,
		nTesouro,
		nDungLvl,
		nLocal,
		nCodigo;
	
	bool flgFim = false,
		flgIniciativa;

	char cWork[50];
	HEROI stHeroi,
		*ptrstHeroi = &stHeroi;
	MONSTRO	stMonstro;


	ARMADURA stArmadura,
	*ptrstArmadura = &stArmadura;
	ARMA stArma,
	*ptrstArma = &stArma;
	ITEM stItem;

	Teste(&stHeroi, &stMonstro, &stItem, &stArma, &stArmadura);
	




	cout << "A princesa foi sequestrada pelo maligno Dragao UltimoChefe." << endl 
		<< "Ele a levou para o see lar nas montanhas." << endl
		<< "Agora cabe a voce, o maior heroi da terra, salva-la antes que ele cumpra o ritual" << endl
		<< "que destruira o mundo" << endl;
	getchar();
	cout << "Voce chegou no primeiro andar da montanha, agora tera que lutar ate o ultimo" << endl
		<< "onde o dragão esta mantendo a princesa e fazendo o ritual";
	cout << "\nVoce entrou na caverna prepare-se para enfrentar muitos monstros durante seu caminho" << endl;
	getchar();

	do
	{
		for (nDungLvl = 1; nDungLvl <= TAMANHODUNGEON; nDungLvl++)
		{
			if (nDungLvl == TAMANHODUNGEON && nLocal == nDungLvl * TAMANHODUNGEON)
			{
				cout << "Voce finalmente chegou ao topo da montanha onde a princesa esta presa" << endl
					<< "Ao entrar ve o Dragao UltimoChefe parado dentro de um circulo de magia" << endl
					<< "Quando voce olha para o ceu e possivel ver um enorme portal" << endl
					<< "Esse e o portal da destruicao, quando estiver terminado nao restara nada vivo nesse planeta" << endl
					<< "Voce percebe que soh falta uma coisa para o ritual se completar..." << endl
					<< "Agora eh sua ultima chance de salvar o planeta e a princesa" << endl
					<< "Agora eh a hora de voce provar que realmente e o maior heroi do planeta que esta destinado a salvar tudo e todos" << endl
					<< "O Dragao olha para voce e fala: " << endl
					<< "		Nunca irah me impedir heroi irei mata-lo depois matarei a princesa e entao destruiuirei o planeta inteiro HUAHUAHUAHUAHUAHUA!!!" << endl
					<< "Nesse momento voce desembainha a sua arma e o combate comeca..." << endl;
				getchar();

				stMonstro.nCA = 50;
				stMonstro.nCodigo = 666;
				stMonstro.nExp = 10000;
				stMonstro.nLvl = 1000;
				stMonstro.nVida = 10000;
				stMonstro.nDanoArma = D20;
				stMonstro.nForca = 100;
				stMonstro.nDestreza = 100;
				stMonstro.nConstituicao = 100;
				stMonstro.strNome = "Dragao Maligno Ultimo Chefe";

				cout << "O monstro " << stMonstro.strNome << " ira destruir o mundo!" << endl
					<< "Prepare-se para o combate!" << endl;
				flgIniciativa = Iniciativa(&stHeroi, &stMonstro);
				if (Luta(&stHeroi, &stMonstro, &stItem, flgIniciativa, stHeroi.nDanoArma, stMonstro.nDanoArma, stHeroi.nVida) == true)
				{
					cout << "Voce eliminou  Dragao Maligno Ultimo Chefe com sucesso!!" << endl;
					cout << "Voce ganhou " << stMonstro.nExp << " Pontos de experiencia" << endl;
					stHeroi.nExp += stMonstro.nExp;

					cout << "O Dragao Maligno Ultimo Chefe gritou de dor enquanto morria" << endl
						<< "Ele jamais tinha pensado que um mero humano conseguirua mata-lo" << endl
						<< "Voce conseguiu resgatar a princesa e retornar a cidade" << endl
						<< "La uma festa foi feita ao seu retorno, onde voce foi reconhecido como o salvador de todo o planeta" << endl
						<< "Após isso voce se casou com a princesa e assim voces viveram felizez para sempre" << endl
						<< "Game Over - Final Bom" << endl;
					getchar();
					return;
				}
			}

			for (nLocal = 1; nLocal <= nDungLvl * TAMANHODUNGEON; nLocal++)
			{
				cout << "Level " << nDungLvl << " de " << TAMANHODUNGEON << " da Dungeon" << endl;
				cout << "Parte " << nLocal << " de " << nDungLvl * TAMANHODUNGEON << " do Level" << endl;
				nEvento = RolagemDados(D10);
				if (nEvento < 3)
				{
					nTesouro = RolagemDados(D6);
					if (nTesouro < 4)
					{
						ptrstArmadura->nCodigo = RolagemDados(D4) + ((nDungLvl -1) *4);
						cout << "Parabens voce achou a armadura " << stArmadura.strNome << "!!" << endl;

						if (CompararItens(stHeroi.nCodigoArmadura, stArmadura.nCodigo) == true)
							break;
						else
						{
							if (stHeroi.nCAArmadura >= stArmadura.nCAArmadura)
							{
								cout << "Essa armadura é inferior a sua atual, por isso sera descartada" << endl;
							}
							else
							{
								cout << "Ela foi equipada.";
								stHeroi.nCodigoArmadura = stArmadura.nCodigo;
								stHeroi.nCAArmadura = stArmadura.nCAArmadura;
								cout << stArmadura.strNome << "CA: " << stArmadura.nCAArmadura;
							}
							getchar();
						}

					}
					else
					{

						ptrstArma->nCodigo = RolagemDados(D4) + ((nDungLvl - 1) * 4);
						cout << "Parabens voce achou a arma " << stArma.strNome << "!!" << endl;
						if (CompararItens(stHeroi.nCodigoArma, stArma.nCodigo) == true)
							break;
						else
						{
							if (stHeroi.nDanoArma + stHeroi.nDanoExtra >= stArma.nDanoArma + stArma.nDanoExtra)
							{
								cout << "Essa arma é inferior a sua atual, por isso sera descartada" << endl;
							}
							else
							{
								cout << "Ela foi equipada.";
								stHeroi.nCodigoArma = stArma.nCodigo;
								stHeroi.nDanoArma = stArma.nDanoArma;
								stHeroi.nDanoExtra = stArma.nDanoExtra;
								cout << stArma.strNome << " Dano: " << stArma.nDanoArma << "Dano Extra: " << stArma.nDanoExtra;

								
							}
							getchar();
						}
					}

				}
				else
				{
					nCodigo = RolagemDados(D4) + ((nDungLvl - 1) * 4);
					GerarMonstro(nCodigo, &stMonstro);
					cout << "Um monstro " << stMonstro.strNome << " apareceu em seu caminho" << endl
						<< "Prepare-se para o combate!" << endl;
					flgIniciativa = Iniciativa(&stHeroi, &stMonstro);
					if (Luta(&stHeroi, &stMonstro, &stItem, flgIniciativa, stHeroi.nDanoArma, stMonstro.nDanoArma, stHeroi.nVida) == true)
					{
						cout << "Voce eliminou  monstro com sucesso!!" << endl;
						cout << "Voce ganhou " << stMonstro.nExp << " Pontos de experiencia" << endl;
						stHeroi.nExp += stMonstro.nExp;
						if (stHeroi.nExp > stHeroi.nLvl * DEFICULLVL)
						{
							cout << "Parabens vc passou level!!" << endl;
							stHeroi.nLvl ++;
							cout << "Seu level atual e " << stHeroi.nLvl << endl;
							cout << "Voce ganhou +" << BONUSDELVL <<" pontos em todos os seus atributos" << endl;
							stHeroi.nDestreza += BONUSDELVL;
							stHeroi.nForca += BONUSDELVL;
							stHeroi.nConstituicao += BONUSDELVL;
							getchar();


						}
						cout << "Pressione qualquer tecla para continuar" << endl;
						getchar();
					}
					
					else
					{
						cout << "Game Over" << endl;
						getchar();
						return;
					}// if else Luta

				}// if else Evento

			}//For nLocal
		}//for DungLvl
	} while (flgFim == false);


}// main
