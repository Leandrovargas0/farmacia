#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>

struct tm *data_hora_atual;     
time_t segundos;
  

typedef struct {
    char codigo[10];
    char nome[100];
    float Preco;
    char TipoRemedio;
    int Quantidade;
}Controle_Estoque;
Controle_Estoque Opera_estoque;


typedef struct {
    char codigo[10];
    char nome[100];
    float Preco;
    char TipoRemedio;
    char crm[25];
    int Quantidade;
    int dia, mes, ano;
    int hora, minuto, segundo;
}Historico_estoque_local;
Historico_estoque_local Estoque_hist_operacao;


typedef struct {
    char estoquecodigo[10];
    char estoquenome[100];
    float estoquePreco;
    char estoqueTipoRemedio;
}EstruturaRemedio_estoque;
EstruturaRemedio_estoque Estoque_Ler;

//void Historico_compra(){}
//void Historico_venda(){}

int Vender(char estoque_cod[], char estoque_nom[], float estoque_prec,
			char estoque_tiporemedio )
{
	return 0;
}







int Comprar(char estoque_cod[], char estoque_nom[], float estoque_prec,
			char estoque_tiporemedio )
{
	time(&segundos);    
	data_hora_atual = localtime(&segundos);
	
	FILE *est_his_compra;
    est_his_compra = fopen("historico_de_compras", "ab+"); 				 
    strcpy(Estoque_hist_operacao.codigo, estoque_cod)       ;
    strcpy(Estoque_hist_operacao.nome, estoque_nom)         ;
    Estoque_hist_operacao.Preco        = estoque_prec       ;
    Estoque_hist_operacao.TipoRemedio  = estoque_tiporemedio;
    //crm
    Estoque_hist_operacao.Quantidade   = 1                  ;
    
    
    Estoque_hist_operacao.dia     = data_hora_atual->tm_mday  ;
    Estoque_hist_operacao.mes     = data_hora_atual->tm_mon   ;
    Estoque_hist_operacao.ano     = data_hora_atual->tm_year  ;
    
    Estoque_hist_operacao.hora    = data_hora_atual->tm_hour  ;
    Estoque_hist_operacao.minuto  = data_hora_atual->tm_min   ;
    Estoque_hist_operacao.segundo = data_hora_atual->tm_sec   ;
     
    
     
	fwrite(&Estoque_hist_operacao, sizeof(Historico_estoque_local), 1, est_his_compra);
	fclose(est_his_compra);
	
    est_his_compra = fopen("controle_estoque", "ab+"); 
	fread(&Opera_estoque, sizeof(Historico_estoque_local), 2, est_his_compra);
		
	printf("CÓDIGO: %s\n",Estoque_hist_operacao.codigo);
	printf("CÓDIGO: %s\n",Estoque_hist_operacao.nome);
	printf("CÓDIGO: %f\n",Estoque_hist_operacao.Preco );
	printf("CÓDIGO: %c\n",Estoque_hist_operacao.TipoRemedio);
	//printf("CÓDIGO: %s\n",Opera_estoque.CRM);
	printf("CÓDIGO: %d\n",Estoque_hist_operacao.Quantidade );

	fclose(est_his_compra);	
		
		
		
		
	system("pause");
	return 0;
}










void buscaitem(int estoque_operacao)
{
	char est_cod[10];
	char est_nom[100];
	float est_prec;
	char est_tiporemedio;
	char estoque_pesquisa_codigo[10];
	
	printf("insira um código para a busca: ");
	scanf("%s", estoque_pesquisa_codigo);		
	FILE *Pont_arq_main;
    Pont_arq_main = fopen("arquivo", "ab+");  
    
	while(!(feof(Pont_arq_main)))
	{	
		fread(&Estoque_Ler, sizeof(EstruturaRemedio_estoque), 1, Pont_arq_main);
		if ((!(feof(Pont_arq_main)) && (strcmp (estoque_pesquisa_codigo, Estoque_Ler.estoquecodigo) == 0)))
		{
			strcpy(est_cod, Estoque_Ler.estoquecodigo);
			strcpy(est_nom, Estoque_Ler.estoquenome);
			est_prec        = Estoque_Ler.estoquePreco;
			est_tiporemedio = Estoque_Ler.estoqueTipoRemedio;

			
			switch(estoque_operacao){
				case 1 :			
					printf("|-----------------------------------------|\n");
					printf("|1 - Verificar Estoque Atual de um produto|\n");
					printf("|-----------------------------------------|\n");
					system("pause");
					break;				
				case 2 :
					Comprar(est_cod, est_nom , est_prec , est_tiporemedio);
					break;
				case 3 :
					Vender(est_cod, est_nom , est_prec , est_tiporemedio);
					break;
			}//switch				
		}//if
	}//while
	system("pause");
	fclose(Pont_arq_main);
}


int Estoque (void)
{	

	int Selecao;
    do
    {
		system ("cls");	
        Selecao = 0;
        //Exibindo o menu
        printf("|-----------------ESTOQUE-----------------|\n");
        printf("|1 - Verificar Estoque Atual              |\n");
        printf("|2 - Adicionar OU comprar medicamentos****|\n");
        printf("|3 - Vender OU remover medicamentos       |\n");
        printf("|4 - historico de compras                 |\n");
        printf("|5 - historico de vendas                  |\n");
        printf("|0 - Voltar ao Menu Inicial               |\n");
        printf("|-----------------------------------------|\n");
        scanf("%d",&Selecao);
        
        switch(Selecao){
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
	
	
/*	
struct tm {
int tm_sec; //representa os segundos de 0 a 59
int tm_min; //representa os minutos de 0 a 59
int tm_hour; //representa as horas de 0 a 24
int tm_mday: //dia do mês de 1 a 31
int tm_mon; //representa os meses do ano de 0 a 11
int tm_year; //representa o ano a partir de 1900
int tm_wday; //dia da semana de 0 (domingo) até 6 (sábado)
int tm_yday; // dia do ano de 1 a 365
int tm_isdst; //indica horário de verão se for diferente de zero
};
*/		










/*	
	FILE *Pont_estoque;
    Pont_estoque = fopen("controle_estoque", "ab+"); 
    
    time(&segundos);    
	data_hora_atual = localtime(&segundos);
					 
    strcpy(Opera_estoque.codigo, estoque_cod)       ;
    strcpy(Opera_estoque.nome, estoque_nom)         ;
    Opera_estoque.Preco        = estoque_prec       ;
    Opera_estoque.TipoRemedio  = estoque_tiporemedio;
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
	* 
*/

