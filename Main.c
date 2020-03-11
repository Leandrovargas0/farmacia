/*Bibliotecas Importadas*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>


/*importando o modulo estoque*/
#include "estoque.h"


/*Registro*/
typedef struct {
    char codigo[10];
    char nome[100];
    float Preco;
    char TipoRemedio;
    //usamos o crm no estoque
}EstruturaRemedio;


/*É usado dentro */
EstruturaRemedio Ler;


void Pesquisa_medicamento()
{

	printf("|------------------------------------------------|\n");
	printf("|4 - Consultar um Medicamento                    |\n");
	printf("|------------------------------------------------|\n");
	
	char code[10];
	printf("\n>>>Digite o codigo para Uuscar informacoes\n");
	scanf("%s", code);
	

	
    FILE *Arquivo = fopen("arquivo", "ab+");
    int cont = 1;
    while(!(feof(Arquivo)))
    {   	
    	fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);
    	if((strcmp (Ler.codigo, code) == 0) && (!(feof(Arquivo))))
    	{
        	printf("CÓDIGO: %s\n",Ler.codigo);
        	printf("NOME: %s\n",Ler.nome);
        	printf("PREÇO: R$ %.2f\n",Ler.Preco);
        	Ler.TipoRemedio=='S' || Ler.TipoRemedio=='s'
        	?printf("Obrigatorio Reter a Receita: Sim\n>>>Ao comprar ou vender será solicitado o CRM do médico! \n\n"):
        	printf("Obrigatorio Reter a Receita: Não\n\n");			
			cont++;
			printf("\n|===============================================|\n");						
		}
		else if (cont == 1)
		{
			printf("Arquivo sem nenhum registro para o codigo!\n\n");
		}
    }
    fclose(Arquivo);
    printf("\n|============================================|\n");	
	
}



void EditarRegistro(int Tipo, char Pesquisa[])
{	
	int continuar = 0;
	int item_encontrado = 0;
	FILE *Arquivo = fopen("arquivo", "ab+");
	FILE *Arquivo_aux = fopen("arquivo_aux", "ab+");
	switch(Tipo)
	{
		case 1:
    		while(!(feof(Arquivo)))
    		{   	
				fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);
				if((strcmp (Ler.codigo, Pesquisa) == 0) && (!(feof(Arquivo))))
				{
					item_encontrado++;
					printf("\n|------------------------------------------------|\n");
					printf("Atencao! Este registro pode ser editado:\n");
					printf("motivo: possui o Codigo buscado\n");
					printf("CODIGO: %s\n",Ler.codigo);
					printf("NOME: %s\n",Ler.nome);
					printf("PRECO: R$ %.2f\n",Ler.Preco);
					Ler.TipoRemedio=='S'?printf("Obrigatorio Reter a Receita: Sim\n\n"):printf("Obrigatorio Reter a Receita: Nao\n\n");					
					
					printf(">>>Digite 1 para continuar com a edicao\n");
					scanf("%d", &continuar);
					if(continuar == 1)
					{
						printf("\n|para sua seguranca nao permitimos que modifique o codigo|\n");
						printf(">>>Novo nome:");scanf("%s", Ler.nome);printf("\n");
						
						printf(">>>Novo Preco:");scanf("%f", &Ler.Preco);printf("\n");

						printf("Necessita a Retencao da Receita?\nS - Sim \nN - Nao\n");
						scanf("%s", &Ler.TipoRemedio);
						printf("\n");
						fwrite(&Ler, sizeof(EstruturaRemedio), 1, Arquivo_aux);
						
					}
					else {
						item_encontrado= -1;
					}
				
				}
				else
				{
					if(!(feof(Arquivo)))
					{
						fwrite(&Ler, sizeof(EstruturaRemedio), 1, Arquivo_aux);
					}
				}
			}		
			break;
	
		case 2:
			while(!(feof(Arquivo)))
    		{   	
				fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);
				if((strcmp (Ler.nome, Pesquisa) == 0) && (!(feof(Arquivo))))
				{
					item_encontrado++;
					printf("\n|------------------------------------------------|\n");
					printf("Atencao! Este registro pode ser editado:\n");
					printf("motivo: possui o Nome buscado\n");
					printf("CoDIGO: %s\n",Ler.codigo);
					printf("NOME: %s\n",Ler.nome);
					printf("PRECO: R$ %.2f\n",Ler.Preco);
					Ler.TipoRemedio=='S'?printf("Obrigatorio Reter a Receita: Sim\n\n"):printf("Obrigatorio Reter a Receita: Nao\n\n");					
					
					printf(">>>Digite 1 para continuar com a edicao\n");
					scanf("%d", &continuar);
					if(continuar == 1)
					{
						printf("\n|para sua seguranca nao permitimos que modifique o codigo|\n");
						printf(">>>Novo nome:");scanf("%s", Ler.nome);printf("\n");
						
						printf(">>>Novo Preco:");scanf("%f", &Ler.Preco);printf("\n");

						printf("Necessita a Retencao da Receita?\nS - Sim \nN - Nao\n");
						scanf("%s", &Ler.TipoRemedio);
						printf("\n");
						fwrite(&Ler, sizeof(EstruturaRemedio), 1, Arquivo_aux);
						
					}
					else {
						item_encontrado= -1;
					}
				
				}
				else
				{
					if(!(feof(Arquivo)))
					{
						fwrite(&Ler, sizeof(EstruturaRemedio), 1, Arquivo_aux);		
					}	
				}
			}
		break;
	}
	
	fclose(Arquivo);
	fclose(Arquivo_aux);
	
	if (item_encontrado > 0)
	{
		char confirma;
		printf("Confirma Edicao do registro demonstrado?\n");
		printf("S - Sim\n");
		printf("N - Não\n");
		scanf("%s",&confirma);
		
		if((confirma == 's')||(confirma == 'S'))
		{
			remove("arquivo");
			Arquivo = fopen("arquivo", "ab+");
			Arquivo_aux = fopen("arquivo_aux", "ab+");
			while(!(feof(Arquivo_aux)))
			{   	
				fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo_aux);
				if (!(feof(Arquivo_aux)))
				{
					fwrite(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);		
				}	
			}
			fclose(Arquivo);
			fclose(Arquivo_aux);
			
			remove("arquivo_aux");
					
			printf("\n|>>>---------Registro editado com Sucesso---------<<<|\n");
			system("pause");
			system ("cls");
		}
		else
		{
			remove("arquivo_aux");
			printf("\n|>>>---------Operacao cancelada---------<<<|\n");
			system("pause");
			system ("cls");
		}
	}
	if (item_encontrado == 0)
	{
		remove("arquivo_aux");
		printf("\n|>>>---------Item nao cadastrado---------<<<|\n");
		system("pause");
		system ("cls");
	}
	if (item_encontrado < 0)
	{		
		remove("arquivo_aux");
		printf("\n|>>>---------Edicao anulada---------<<<|\n");
		system("pause");
		system ("cls");
	}
	
}


int verificacao_arquivo(char Pesquisa[])
{
	int consulta = 0;
	FILE *Arquivo = fopen("arquivo", "ab+");

	while(!(feof(Arquivo)))
	{   	
		fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);
		if((strcmp (Ler.codigo, Pesquisa) == 0) && (!(feof(Arquivo))))
		{
			consulta++;				
		}
	}	
	fclose(Arquivo);	
	if (consulta == 0)
	{
		return 0;
	}
	else 
	{
		printf("\n >>>>>O codigo digitado, %s, já exite favor inserir outro <<<<\n\n", Pesquisa);
		 system("pause");
		 system ("cls");
		return 1;
	}
}


/*Apenas exibe todos registros*/	
void ImprimeTodosRegistros()
{
	printf("|------------------------------------------------|\n");
	printf("|5 - Modulo para visualizacao de item cadastrados|\n");
	printf("|------------------------------------------------|\n");
	
    FILE *Arquivo = fopen("arquivo", "ab+");
    int cont = 1;
    while(!(feof(Arquivo)))
    {   	
    	fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);
    	if (!(feof(Arquivo)))
    	{
        	printf("ITEM Nº %d: \n", cont);
        	printf("CÓDIGO: %s\n",Ler.codigo);
        	printf("NOME: %s\n",Ler.nome);
        	printf("PREÇO: R$ %.2f\n",Ler.Preco);
        	Ler.TipoRemedio=='S' || Ler.TipoRemedio=='s'
        	?printf("Obrigatorio Reter a Receita: Sim\n>>>Ao comprar ou vender será solicitado o CRM do médico! \n\n"):
        	printf("Obrigatorio Reter a Receita: Não\n\n");
			
			cont++;
		}
		else if (cont == 1)
		{
			printf("Arquivo sem nenhum registro de medicamento!\n\n");
		}
    }
    fclose(Arquivo);
    printf("|------------------------------------------------|\n");
    system("pause");
    system ("cls");
}


/*O nome já diz*/
void ExcluirTodos()
{
	FILE *Pont_Arq;
	Pont_Arq = fopen("arquivo", "wb+");
	printf("Registros Excluidos com Sucesso!\n\n");
	fclose(Pont_Arq);
}


/*EXclui por nome ou por código*/
//FALTA ADICIONAR A SITUAÇÃO DO VALOR NAO ENCONTRADO, PARA NOME E CODIGO
void ExcluiRegistro(int Tipo, char Pesquisa[])
{	
	int item_encontrado = 0;
	FILE *Arquivo = fopen("arquivo", "ab+");
	FILE *Arquivo_aux = fopen("arquivo_aux", "ab+");
	switch(Tipo)
	{
		case 1:
    		while(!(feof(Arquivo)))
    		{   	
				fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);
				if((strcmp (Ler.codigo, Pesquisa) == 0) && (!(feof(Arquivo))))
				{
					item_encontrado++;
					printf("\n|------------------------------------------------|\n");
					printf("Atencao! Este registro sera excluido:\n");
					printf("CODIGO: %s\n",Ler.codigo);
					printf("NOME: %s\n",Ler.nome);
					printf("PRECO: R$ %.2f\n",Ler.Preco);
					Ler.TipoRemedio=='S'?printf("Obrigatorio Reter a Receita: Sim\n\n"):printf("Obrigatorio Reter a Receita: Nao\n\n");					
				}
				else
				{
					if(!(feof(Arquivo)))
					{
						fwrite(&Ler, sizeof(EstruturaRemedio), 1, Arquivo_aux);
					}
				}
			}		
			break;
	
		case 2:
			while(!(feof(Arquivo)))
    		{   	
				fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);
				if((strcmp (Ler.nome, Pesquisa) == 0) && (!(feof(Arquivo))))
				{
					item_encontrado++;
					printf("Atencao! Este registro sera excluido:\n");
					printf("CoDIGO: %s\n",Ler.codigo);
					printf("NOME: %s\n",Ler.nome);
					printf("PRECO: R$ %.2f\n",Ler.Preco);
					Ler.TipoRemedio=='S'?printf("Obrigatorio Reter a Receita: Sim\n\n"):printf("Obrigatorio Reter a Receita: Nao\n\n");					
				}
				else
				{
					if(!(feof(Arquivo)))
					{
						fwrite(&Ler, sizeof(EstruturaRemedio), 1, Arquivo_aux);		
					}	
				}
			}
		break;
	}
	
	fclose(Arquivo);
	fclose(Arquivo_aux);
	
	if (item_encontrado > 0)
	{
		char confirma;
		printf("Confirma exclusão do registro demonstrado?\n");
		printf("S - Sim\n");
		printf("N - Não\n");
		scanf("%s",&confirma);
		
		if((confirma == 's')||(confirma == 'S'))
		{
			remove("arquivo");
			Arquivo = fopen("arquivo", "ab+");
			Arquivo_aux = fopen("arquivo_aux", "ab+");
			while(!(feof(Arquivo_aux)))
			{   	
				fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo_aux);
				if (!(feof(Arquivo_aux)))
				{
					fwrite(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);		
				}	
			}
			fclose(Arquivo);
			fclose(Arquivo_aux);
			
			remove("arquivo_aux");
					
			printf("\n|>>>---------Registros Excluidos com Sucesso---------<<<|\n");
			system("pause");
			system ("cls");
		}
		else
		{
			remove("arquivo_aux");
			printf("\n|>>>---------Operacao cancelada---------<<<|\n");
			system("pause");
			system ("cls");
		}
	}
	if (item_encontrado == 0)
	{
			printf("\n|>>>---------Item nao cadastrado---------<<<|\n");
			system("pause");
			system ("cls");
	}
}

int main()
{
	setlocale(LC_ALL, NULL);
	system("chcp 1252 > nul");
    FILE *Pont_Arq;

    Pont_Arq = fopen("arquivo", "ab+");
    if (Pont_Arq == NULL){
		//printf("ERRO! O arquivo nÃ£o foi aberto!\n");
    }
    else {
		//printf("O arquivo foi aberto com sucesso!");
    }
	fclose(Pont_Arq);
	
	int Selecao;
    do{
		char code[10];
		int retorno_func = 0;
        Selecao = 0;
        printf("Bem Vindos ao cadastro de Medicamentos:\n");
        printf("Digite o codigo referente a operacao que deseja executar.\n");
        printf("1 - Cadastrar Novo Medicamento\n");
        printf("2 - Excluir um Medicamento\n");
        printf("3 - Editar um Medicamento\n");
        printf("4 - Consultar um Medicamento\n");
        printf("5 - Imprimir Todos os Medicamentos\n");
        printf("9 - *** Acesso ao Estoque ***\n");
        printf("0 - Sair do Sistema\n");
        scanf("%d",&Selecao);

        switch(Selecao){
            case 1 :
				system ("cls");
		       	printf("-----Cadastrar Registros de Medicamentos-----\n");
                printf("Digite o codigo do Novo Medicamento:\n");
                scanf("%s", code);
                
                retorno_func = verificacao_arquivo(code);
                if (retorno_func == 0)
                {
					Pont_Arq = fopen("arquivo", "ab+");
					EstruturaRemedio Cadastrar;
					
					strcpy(Cadastrar.codigo, code);
					//scanf("%s", Cadastrar.codigo);
		
					printf("Digite o Nome do Novo Medicamento:\n");
					scanf("%s", Cadastrar.nome);
					
					printf("Digite o Preco do Novo Medicamento:\n");
					scanf("%f", &Cadastrar.Preco);

					printf("Necessita a Retencao da Receita?\nS - Sim \nN - Nao\n");
					scanf("%s", &Cadastrar.TipoRemedio);
					Cadastrar.TipoRemedio = toupper(Cadastrar.TipoRemedio); 
				   
					if(Cadastrar.TipoRemedio != 0){	
						fwrite(&Cadastrar, sizeof(EstruturaRemedio), 1, Pont_Arq);
					}
					fclose(Pont_Arq);
					system("pause");
					system ("cls");
				}
            break;

            case 2:
            	system ("cls");
				printf("|------------------------------------------------|\n");
				printf("|2 - Modulo para exclusao de itens cadastrados   |\n");
				printf("|------------------------------------------------|\n");
				int Op=0;
				char confirma ='N';
				printf("1 - Excluir todos os Registros.\n");
				printf("2 - Excluir Registros por Codigo.\n");
				printf("3 - Excluir Registros por Nome.\n");
				printf("0 - Voltar ao Menu Inicial.\n");
				scanf("%d",&Op);
				switch(Op){
					char pesquisa[100];
					case 1 :
						printf("Atenção, tal operacao excluira os seguintes registros:\n");
						ImprimeTodosRegistros();
						printf("Confirma excluir todos?\n");
						printf("S - Sim\n");
						printf("N - Nao\n");
						scanf("%s",&confirma);
						confirma=='S'?ExcluirTodos():printf("Operacao Cancelada!\n\n");				
						break;
					case 2 :	
						printf("Digite o codigo que deseja excluir: ");
						scanf("%s",pesquisa);
						ExcluiRegistro(1,pesquisa);
						
						break;			
					case 3:
						printf("Digite o nome que deseja excluir:");
						scanf("%s",pesquisa);
						ExcluiRegistro(2,pesquisa);
					default:
						printf(">> menu inicial!\n\n");
						system ("cls");
						
				}
                break;
            case 3:
            	system ("cls");
				printf("|------------------------------------------------|\n");
				printf("|3 - Modulo para edicao de item cadastrado       |\n");
				printf("|------------------------------------------------|\n");
				int Op1=0;
				
				printf("1 - Buscar Registros por Codigo.\n");
				printf("2 - Buscar Registros por Nome.\n");
				printf("0 - Voltar ao Menu Inicial.\n");
				scanf("%d",&Op1);
				switch(Op1){
					char pesquisa[100];
					case 1 :	
						printf("Digite o codigo que deseja editar: ");
						scanf("%s",pesquisa);
						EditarRegistro(1,pesquisa);
						
						break;			
					case 2:
						printf("Digite o nome que deseja editar:");
						scanf("%s",pesquisa);
						EditarRegistro(2,pesquisa);
					default:
						printf(">> menu inicial!\n\n");
						system ("cls");						
				}
                break;    	    
                               
            case 4:       
                printf("OPCAO 4\n");
				Pesquisa_medicamento();
				//char buscainterna_
                system("pause");
                system ("cls");
                break;
            case 5:
            	system ("cls");
                ImprimeTodosRegistros();
                break;
                
            case 9:
            	system ("cls");
                Estoque();
                break;
		}
	}
	while(Selecao!=0);
    system("pause");
    return 0;
}
