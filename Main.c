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
}EstruturaRemedio;


/*É usado dentro */
EstruturaRemedio Ler;
EstruturaRemedio Excluir;


/*Apenas exibe todos registros*/	
void ImprimeTodosRegistros(){
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
        	Ler.TipoRemedio=='S'?printf("Obrigatorio Reter a Receita: Sim\nCRM do Médico: \n\n"):printf("Obrigatorio Reter a Receita: Não\n\n");
			cont++;
		}
		else if (cont == 1)
		{
			printf("Arquivo sem nenhum registro de medicamento!\n\n");
		}
    }
    fclose(Arquivo);
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
	
	char confirma;
	printf("Confirma exclusão dos registros demonstrados?\n");
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
				
		printf("Registros Excluidos com Sucesso!\n");
	}
	else
	{
		remove("arquivo_aux");
		printf("OPERACAO CANCELADA!");
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
    			//Abre o Arquivo
            	Pont_Arq = fopen("arquivo", "ab+");
				
				//LIMPA A TELA
            	system ("cls");
            	
            	//REFERENCIA O REGISTRO, VEJA O INICIO
            	EstruturaRemedio Cadastrar;
            	
				
		       	printf("Cadastrar Registros de Medicamentos\n");
            	
            	//Solicita as Informacoes para Cadastrar
                printf("Digite o codigo do Novo Medicamento:\n");
                scanf("%s", Cadastrar.codigo);
 	
                printf("Digite o Nome do Novo Medicamento:\n");
                scanf("%s", Cadastrar.nome);
				
                printf("Digite o Preco do Novo Medicamento:\n");
                scanf("%f", &Cadastrar.Preco);

                printf("Necessita a Retencao da Receita?\nS - Sim \nN - Nao\n");
                scanf("%s", &Cadastrar.TipoRemedio);
                Cadastrar.TipoRemedio = toupper(Cadastrar.TipoRemedio); 
               
                if(Cadastrar.TipoRemedio != 0){
					//guarda na última posicao do arquivo
                	fwrite(&Cadastrar, sizeof(EstruturaRemedio), 1, Pont_Arq);
				}

                fclose(Pont_Arq);
            break;

            case 2:
            	system ("cls");
				int Op=0;
				char confirma ='N';
				printf("Excluir Registros de Medicamentos\n");
				printf("1 - Excluir todos os Registros.\n");
				printf("2 - Excluir Registros por Codigo.\n");
				printf("3 - Excluir Registros por Nome.\n");
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
						printf("Digite o codigo que deseja excluir:");
						scanf("%s",pesquisa);
						ExcluiRegistro(1,pesquisa);
						
						break;			
					case 3:
						printf("Digite o nome que deseja excluir:");
						scanf("%s",pesquisa);
						ExcluiRegistro(2,pesquisa);
					default:
						printf("Codigo digitado é invalido, favor refazer a operao!\n\n");
						
				}
                break;
            case 3:
            	
            	printf("Digite o Codigo ou Nome do medicamento que deseja editar:\n");
            	char Pesquisa[100];
            	scanf("%s", Pesquisa);
        	    Pont_Arq = fopen("arquivo", "ab+");
        	    //fseek(Pont_Arq, 0, SEEK_SET);
    			while(!(feof(Pont_Arq)))
    			{  	
					fread(&Ler, sizeof(EstruturaRemedio), 1, Pont_Arq);
					if((strcmp (Ler.codigo, Pesquisa) == 0))
					{
						printf("Atencao! Voce esta prestes a editar o Seguinte Registro:\n");
						printf("CoDIGO: %s\n",Ler.codigo);
						printf("NOME: %s\n",Ler.nome);
						printf("PRECO: R$ %.2f\n",Ler.Preco);
						Ler.TipoRemedio=='S'?printf("Obrigatorio Reter a Receita: Sim\n\n"):printf("Obrigatorio Reter a Receita: Nao\n\n");
						EstruturaRemedio Cadastrar;
				
						//Solicita as Informações para Cadastrar
                		printf("Digite o Novo Codigo do Medicamento:\n");
                		scanf("%s", Cadastrar.codigo);
						//Cadastrar.codigo = toupper(Cadastrar.codigo); 
				
                		printf("Digite o Novo Nome do Medicamento:\n");
                		scanf("%s", Cadastrar.nome);
						//Cadastrar.nome = toupper(Cadastrar.nome); 
				
                		printf("Digite o Preço do Novo Medicamento:\n");
                		scanf("%f", &Cadastrar.Preco);

                		printf("Necessita a RetenÃ§Ã£o da Receita?\nS - Sim \nN - Nao\n");
                		scanf("%s", &Cadastrar.TipoRemedio);
                		Cadastrar.TipoRemedio = toupper(Cadastrar.TipoRemedio); 
	                	fwrite(&Cadastrar, sizeof(EstruturaRemedio), 1, Pont_Arq);	
	                	fseek(Pont_Arq, 0, SEEK_SET);
					}
				}
				fclose(Pont_Arq);
                break;
                
            case 4:       
                printf("OPCAO 4\n");
               // Pesquisa_medicamento();
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
