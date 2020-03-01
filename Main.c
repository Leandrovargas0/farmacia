/*Bibliotecas Importadas*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include "estoque.h"

/*Definindo os Tipos de Registros*/
typedef struct {
    char codigo[10];
    char nome[100];
    float Preco;
    char TipoRemedio;
}EstruturaRemedio;

/*Declarando os Registros Globais*/
//EstruturaRemedio Cadastrar;
EstruturaRemedio Ler;
EstruturaRemedio Excluir;
	
//--Região dos Metódos Auxiliares--//
/*Método que imprime Todos os Registros*/
void ImprimeTodosRegistros(){
    FILE *Arquivo = fopen("arquivo", "ab+");
    int cont = 1;
    while(!(feof(Arquivo)))
    {   	
    	fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);
    	if (!(feof(Arquivo))){
        	printf("ITEM Nº %d: \n", cont);
        	printf("CÓDIGO: %s\n",Ler.codigo);
        	printf("NOME: %s\n",Ler.nome);
        	printf("PREÇO: R$ %.2f\n\n",Ler.Preco);
			cont++;
		}
		else if (cont == 1){
			printf("Arquivo sem nenhum registro de medicamento!\n\n");
		}
    }
    fclose(Arquivo);
}

/*Método que Exclui Todos*/
void ExcluirTodos(){
	FILE *Pont_Arq;
	Pont_Arq = fopen("arquivo", "wb+");
	printf("Registros Excluidos com Sucesso!\n\n");
	fclose(Pont_Arq);
}

/*Método que Exclui um registro*/
/*1 - Excluir por Código*/
/*2 - Excluir por Nome*/
void ExcluiRegistro(int Tipo, char Pesquisa[]){
	FILE *Arquivo = fopen("arquivo", "ab+");
	fseek(Arquivo, 0, SEEK_END);
	int QTD = ftell (Arquivo);
	QTD = QTD / 120;
	fclose(Arquivo);
	
	EstruturaRemedio NovoArquivo[QTD];
	Arquivo = fopen("arquivo", "ab+");
	int cont = 0;
	switch(Tipo){
		case 1:
		for(int i = 0; i < QTD;i++){
			fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);
			if((Tipo == 1) && (Ler.codigo != Pesquisa)){
				NovoArquivo[i] = Ler;
			}
			else{
				printf("Atenção! Este registro será excluido:");
				printf("CÓDIGO: %s\n",Ler.codigo);
				printf("NOME: %s\n",Ler.nome);
				printf("PREÇO: R$ %.2f\n",Ler.Preco);
				Ler.TipoRemedio=='S'?printf("Obrigatório Reter a Receita: Sim\n-\n\n"):printf("Obrigatório Reter a Receita: Não\n\n");
			}
		}
			break;
		case 2:
		for(int i = 0; i < QTD;i++){
			fread(&Ler, sizeof(EstruturaRemedio), 1, Arquivo);
			if((Tipo == 2) && (Ler.nome != Pesquisa)){
				NovoArquivo[i] = Ler;
			}
			else{
				printf("Atenção! Este registro será excluido:\n");
				printf("CÓDIGO: %s\n",Ler.codigo);
				printf("NOME: %s\n",Ler.nome);
				printf("PREÇO: R$ %.2f\n\n",Ler.Preco);
				Ler.TipoRemedio=='S'?printf("Obrigatório Reter a Receita: Sim\n\n"):printf("Obrigatório Reter a Receita: Não\n\n");
			}
		}
			break;
	}
	fclose(Arquivo);
	int QTD2 = QTD - cont;
	char confirma;
	printf("Confirma exclusão dos registros demonstrados?\n");
	printf("S - Sim\n");
	printf("N - Não\n");
	scanf("%s",&confirma);
	if((confirma == 's')||(confirma == 'S')){
		Arquivo = fopen("arquivo", "wb+");
		
		for(int i = 0; i < QTD2;i++){
			fwrite(&NovoArquivo[i], sizeof(EstruturaRemedio), 1, Arquivo);
		}
		
		printf("Registros Excluidos com Sucesso!");
		fclose(Arquivo);
	}
	else{
		printf("Operação Cancelada com sucesso!");
	}
}

/*Método Principal*/
int main()
{
	setlocale(LC_ALL, NULL);
	system("chcp 1252 > nul");
    FILE *Pont_Arq;

    Pont_Arq = fopen("arquivo", "ab+");
    if (Pont_Arq == NULL){
		//printf("ERRO! O arquivo não foi aberto!\n");
    }
    else {
		//printf("O arquivo foi aberto com sucesso!");
    }
	fclose(Pont_Arq);
	
    //Menu
	int Selecao;
    do{
        Selecao = 0;
        //Exibindo o menu
        printf("Bem Vindos ao cadastro de Medicamentos:\n");
        printf("Digite o codigo referente a operacao que deseja executar.\n");
        printf("1 - Cadastrar Novo Medicamento\n");
        printf("2 - Excluir um Medicamento\n");
        printf("3 - Editar um Medicamento\n");
        printf("4 - Consultar um Medicamento\n");
        printf("5 - Imprimir Todos os Medicamentos\n");
        printf("0 - Sair do Sistema\n");
        scanf("%d",&Selecao);

        switch(Selecao){
            case 1 :
    			//Abre o Arquivo
            	Pont_Arq = fopen("arquivo", "ab+");
            	
            	system ("cls");
            	EstruturaRemedio Cadastrar;
				//fread(&Ler, sizeof(EstruturaRemedio), 2, Pont_Arq);
				
		       	printf("Cadastrar Registros de Medicamentos\n");
            	
            	//Solicita as Informações para Cadastrar
                printf("Digite o Código do Novo Medicamento:\n");
                scanf("%s", Cadastrar.codigo);
				//Cadastrar.codigo = toupper(Cadastrar.codigo); 
				
                printf("Digite o Nome do Novo Medicamento:\n");
                scanf("%s", Cadastrar.nome);
				//Cadastrar.nome = toupper(Cadastrar.nome); 
				
                printf("Digite o Preço do Novo Medicamento:\n");
                scanf("%f", &Cadastrar.Preco);

                printf("Necessita a Retenção da Receita?\nS - Sim \nN - Não\n");
                scanf("%s", &Cadastrar.TipoRemedio);
                Cadastrar.TipoRemedio = toupper(Cadastrar.TipoRemedio); 

               /* if(Cadastrar.TipoRemedio == 'S'){
                    printf("Digite o CRM do Médico que receitou:\n");
                    scanf("%s",Cadastrar.CRM);
                    //Cadastrar.CRM = toupper(Cadastrar.CRM); 
                }*/
                
                if(Cadastrar.TipoRemedio != 0){
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
				printf("2 - Excluir Registros por Código.\n");
				printf("3 - Excluir Registros por Nome.\n");
				scanf("%d",&Op);
				switch(Op){
					char pesquisa[100];
					case 1 :
						printf("Atenção, tal operação excluira os seguintes registros:\n");
						ImprimeTodosRegistros();
						printf("Confirma excluir todos?\n");
						printf("S - Sim\n");
						printf("N - Não\n");
						scanf("%s",&confirma);
						confirma=='S'?ExcluirTodos():printf("Operação Cancelada!\n\n");				
						break;
					case 2 :	
						printf("Digite o código que deseja excluir:");
						scanf("%s",pesquisa);
						ExcluiRegistro(1,pesquisa);
						
						break;			
					case 3:
						printf("Digite o código que deseja excluir:");
						scanf("%s",pesquisa);
						ExcluiRegistro(2,pesquisa);
					default:
						printf("Código digitado é invalido, favor refazer a operação!\n\n");
						
				}
                break;
            case 3:
				system ("cls");
                printf("%d\n",Selecao);
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
                
            case 999:
            	system ("cls");
                Estoque();
                break;
		}
	}
	while(Selecao!=0);
    system("pause");
    return 0;
}
