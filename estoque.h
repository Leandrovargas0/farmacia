#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>


typedef struct {
    char codigo[10];
    char nome[100];
    float Preco;
    char TipoRemedio;
    //char CRM[25];
    int Quantidade;
}Controle_Estoque;
Controle_Estoque Opera_estoque;



typedef struct {
    char estoquecodigo[10];
    char estoquenome[100];
    float estoquePreco;
    char estoqueTipoRemedio;
    //char estoqueCRM[25];
}EstruturaRemedio_estoque;
EstruturaRemedio_estoque Estoque_Ler;

//void Historico_compra(){}
//
//void Historico_venda(){}

int Vender(char estoque_cod[], char estoque_nom[], float estoque_prec,
			char estoque_tiporemedio )
{
	return 0;
}

int Comprar(char estoque_cod[], char estoque_nom[], float estoque_prec,
			char estoque_tiporemedio )
{
	FILE *Pont_estoque;
    Pont_estoque = fopen("controle_estoque", "ab+"); 
    
    strcpy(Opera_estoque.codigo, estoque_cod)       ;
    strcpy(Opera_estoque.nome, estoque_nom)         ;
    Opera_estoque.Preco        = estoque_prec       ;
    Opera_estoque.TipoRemedio  = estoque_tiporemedio;
    //strcpy(Opera_estoque.CRM, estoque_crm)          ;
    Opera_estoque.Quantidade   = 1                  ;
	fwrite(&Opera_estoque, sizeof(Controle_Estoque), 1, Pont_estoque);
	fclose(Pont_estoque);
	
    Pont_estoque = fopen("controle_estoque", "ab+"); 
	fread(&Opera_estoque, sizeof(Controle_Estoque), 2, Pont_estoque);
	
	
	printf("CÓDIGO: %s\n",Opera_estoque.codigo);
	printf("CÓDIGO: %s\n",Opera_estoque.nome);
	printf("CÓDIGO: %f\n",Opera_estoque.Preco );
	printf("CÓDIGO: %c\n",Opera_estoque.TipoRemedio);
	//printf("CÓDIGO: %s\n",Opera_estoque.CRM);
	printf("CÓDIGO: %d\n",Opera_estoque.Quantidade );

	
	fclose(Pont_estoque);	
	system("pause");
	
	
	return 0;
}


void buscaitem(int estoque_operacao)
{
	//int estoque_cont = 1; 
	char est_cod[10];
	char est_nom[100];
	float est_prec;
	char est_tiporemedio;
	//char est_crm[25];
	
	
	char estoque_pesquisa_codigo[10];
	printf("insira um código para a busca: ");
	scanf("%s", estoque_pesquisa_codigo);
	
			
	FILE *Pont_arq_main;
    Pont_arq_main = fopen("arquivo", "ab+"); 
    
    
	while(!(feof(Pont_arq_main)))
	{	
		fread(&Estoque_Ler, sizeof(EstruturaRemedio_estoque), 1, Pont_arq_main);
		strcpy(est_cod, Estoque_Ler.estoquecodigo);
		printf("%s --- \n", est_cod);
		if ((strcmp (estoque_pesquisa_codigo, Estoque_Ler.estoquecodigo) == 0) && (!(feof(Pont_arq_main)))
			){
			strcpy(est_cod, Estoque_Ler.estoquecodigo);
			strcpy(est_nom, Estoque_Ler.estoquenome);
			est_prec        = Estoque_Ler.estoquePreco;
			est_tiporemedio = Estoque_Ler.estoqueTipoRemedio;
			
				
			if (estoque_operacao == 1)
			{	
				printf("|-----------------------------------------|\n");
				printf("|1 - Verificar Estoque Atual de um produto|\n");
				printf("|-----------------------------------------|\n");
				system("pause");
			}
			
			if (estoque_operacao == 2)
			{
				printf("|-----------------------------------------|\n");
				printf("|----------------entrou 2-----------------|\n");
				printf("|-----------------------------------------|\n");
				system("pause");
				Comprar(est_cod, est_nom , est_prec , est_tiporemedio);
			}
			if (estoque_operacao == 3)
			{
				Vender(est_cod, est_nom , est_prec , est_tiporemedio);

			}
		}
	}
	system("pause");
	fclose(Pont_arq_main);
	

	
}


int Estoque (void)
{
	printf("Bem vindo ao modulo de estoque!\n");
	system("pause");
	system ("cls");	
	
	int Selecao;
    do
    {
		system ("cls");	
        Selecao = 0;
        //Exibindo o menu
        printf("Sistema de Gerenciamento de Farmacias:\n");
        printf("Digite o codigo referente a operacao que deseja executar:\n");
        printf("1 - Verificar Estoque Atual\n");
        printf("2 - Adicionar / comprar medicamentos\n");
        printf("3 - Vender / remover medicamentos\n");
        printf("4 - historico de compras\n");
        printf("5 - historico de vendas\n");
        printf("0 - Voltar ao Menu Inicial\n");

        //Lendo a operação
        scanf("%d",&Selecao);
        
        switch(Selecao)
        {
            case 1 :
				buscaitem(Selecao);
            break;				
            case 2 :
				buscaitem(Selecao);
            break;
            
			case 3 :
				buscaitem(Selecao);
            break;
        }
		
	}while(Selecao!=0);
	system ("cls");	
	return 0;
	
	
}


