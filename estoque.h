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



void func_controle_estoque(int func_controle_estoque_tipo, char func_controle_estoque_codigo[],
							char func_controle_estoque_nome[], float func_controle_estoquePreco,
							char func_controle_estoque_TipoRemedio, int func_controle_estoque_Quantidade)
	{

 		FILE *est_hist = fopen("controle_estoque", "ab+"); 
		int achou_em_estoque = 0;
		// exibicao geral 1
		// exibicao unica	2 
		//compra 3
		//venda 4
		switch(func_controle_estoque_tipo)
		{
			case 1: 	
				system ("cls");
				printf("|------------------------------------------------|\n");
				printf("|--------- 1-Verificar Estoque Atual ----------- |\n");
				printf("|------------------------------------------------|\n");
				
				achou_em_estoque = 1;
				while(!(feof(est_hist)))
				{   	
					fread(&Opera_estoque, sizeof(Controle_Estoque), 1, est_hist);
					if (!(feof(est_hist)))
					{
						printf("ITEM N %d: \n", achou_em_estoque);
						printf("CODIGO: %s\n",Opera_estoque.codigo);
						printf("NOME: %s\n",Opera_estoque.nome);
						printf("PRECO: R$ %.2f\n",Opera_estoque.Preco);
						Opera_estoque.TipoRemedio=='S' || Opera_estoque.TipoRemedio=='s'
						?printf("Obrigatorio Reter a Receita: Sim\n>>>Ao comprar ou vender sera solicitado o CRM do medico! \n"):
						printf("Obrigatorio Reter a Receita: Nao\n");
						printf("Quantidade em estoque: %d\n",Opera_estoque.Quantidade);
						printf("|------------------------------------------------|\n\n");
						achou_em_estoque++;
					}
					else if (achou_em_estoque == 1)
					{
						printf("medicamento nao localizado no estoque!\n\n");
					}
				}
				fclose(est_hist);
				printf("|------------------------------------------------|\n");
				system("pause");
				system ("cls");
			break;
			
			case 2: 	
				system ("cls");
				printf("|------------------------------------------------|\n");
				printf("|----8 - Verificar apenas um item em estoque ----|\n");
				printf("|------------------------------------------------|\n");
				
				achou_em_estoque = 1;
				while(!(feof(est_hist)))
				{   	
					fread(&Opera_estoque, sizeof(Controle_Estoque), 1, est_hist);
					if( (!(feof(est_hist))) && (strcmp (func_controle_estoque_codigo, Opera_estoque.codigo)))
					{
						printf("ITEM N %d: \n", achou_em_estoque);
						printf("CODIGO: %s\n",Opera_estoque.codigo);
						printf("NOME: %s\n",Opera_estoque.nome);
						printf("PRECO: R$ %.2f\n",Opera_estoque.Preco);
						Opera_estoque.TipoRemedio=='S' || Opera_estoque.TipoRemedio=='s'
						?printf("Obrigatorio Reter a Receita: Sim\n>>>Ao comprar ou vender sera solicitado o CRM do medico! \n"):
						printf("Obrigatorio Reter a Receita: Nao\n");
						printf("Quantidade em estoque: %d\n",Opera_estoque.Quantidade);
						printf("|------------------------------------------------|\n\n");
						achou_em_estoque++;
					}
					else if (achou_em_estoque == 1)
					{
						printf("medicamento nao localizado no estoque!\n\n");
					}
				}
				fclose(est_hist);
				printf("|------------------------------------------------|\n");
				system("pause");
				system ("cls");
			break;

			case 3:
				while((!(feof(est_hist)) && (achou_em_estoque == 0)) )
				{  
					fread(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist);
					if((!(feof(est_hist))) && (strcmp (func_controle_estoque_codigo, Opera_estoque.codigo) == 0))
					{
						achou_em_estoque++;
						printf("\nCompra bem sucedida\n\n");
						fclose(est_hist);
						FILE *est_hist = fopen("controle_estoque", "ab+");
						FILE *est_hist_aux = fopen("controle_estoque_aux", "ab+");
						while(!(feof(est_hist)))
						{
							fread(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist);
							if((!(feof(est_hist))) && (strcmp (func_controle_estoque_codigo, Opera_estoque.codigo) == 0))
							{
								Opera_estoque.Quantidade = Opera_estoque.Quantidade + func_controle_estoque_Quantidade;
								fwrite(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist_aux);
							}
							else
							{
								if(!(feof(est_hist)))
								{
									fwrite(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist_aux);
								}
							}
						}
						fclose(est_hist);
						fclose(est_hist_aux);
						
						remove("controle_estoque");
						est_hist = fopen("controle_estoque", "ab+");
						est_hist_aux = fopen("controle_estoque_aux", "ab+");
						
						while(!(feof(est_hist_aux)))
						{
							fread(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist_aux);
							if(!(feof(est_hist_aux)))
							{
								fwrite(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist);
							}
						}
						fclose(est_hist);
						fclose(est_hist_aux);
						
						remove("controle_estoque_aux");		
					}						
				}
				if (achou_em_estoque == 0)
				{		
					achou_em_estoque++;
								
					strcpy(Opera_estoque.codigo, func_controle_estoque_codigo);
					strcpy(Opera_estoque.nome, func_controle_estoque_nome);
					Opera_estoque.TipoRemedio = func_controle_estoque_TipoRemedio;
					
					Opera_estoque.Preco = func_controle_estoquePreco;
					Opera_estoque.Quantidade = func_controle_estoque_Quantidade;

					fwrite(&Opera_estoque, sizeof(Controle_Estoque), 1, est_hist);	
					fclose(est_hist);
					printf("\nCompra bem sucedida\n\n");
				
				}	
				
				
			break;

			//case 4: 	
				//a venda foi implementada no módulo de venda 
			//break;

		}
		
		

	}


void Historico_compra(int Historico_compra_tipo)
{
	int cont_Historico_compra = 0;
	char pesquisa_Historico_compra_cod[10];
	system ("cls");

	FILE *est_his_compra = fopen("historico_de_compras", "ab+");
		
	if (Historico_compra_tipo == 4)
	{
		printf("|------------------------------------------------|\n");
		printf("|          HISTORICO GERAL DE COMPRAS            |\n");
		printf("|------------------------------------------------|\n");
		while(!(feof(est_his_compra)))
		{   
			cont_Historico_compra++;
			
			fread(&Estoque_hist_operacao, sizeof(Historico_estoque_local), 1, est_his_compra);
			if(!(feof(est_his_compra)))
			{
				printf("CODIGO: %s\n",Estoque_hist_operacao.codigo);
				printf("NOME: %s\n",Estoque_hist_operacao.nome);
				printf("PRECO NO DIA: %.2f\n",Estoque_hist_operacao.Preco );
				printf("RETEM RECEITA: %c\n",Estoque_hist_operacao.TipoRemedio);
				printf("CRM: %s\n",Estoque_hist_operacao.crm);
				printf("Quantidade: %d\n",Estoque_hist_operacao.Quantidade );
				
				printf("DATA: %d/%d/%d \n", Estoque_hist_operacao.dia, Estoque_hist_operacao.mes, Estoque_hist_operacao.ano + 1900);
				printf("HORARIO: %d HORAS, %d MINUTOS E %d SEGUNDOS\n", Estoque_hist_operacao.hora,
				Estoque_hist_operacao.minuto, Estoque_hist_operacao.segundo);
				
				printf("Valor total da operacao: RS%.2f\n",Estoque_hist_operacao.Quantidade * Estoque_hist_operacao.Preco);
				printf("|------------------------------------------------|\n");			
			}
		}
	}
	else 
	{
		printf("|------------------------------------------------|\n");
		printf("|        HISTORICO INDIVIDUAL DE COMPRAS         |\n");
		printf("|------------------------------------------------|\n");
		printf("Insira o codigo do item que deseja verificar o historico\n>>>");
		scanf("%s", pesquisa_Historico_compra_cod);
	
		while(!(feof(est_his_compra)))
		{   
			fread(&Estoque_hist_operacao, sizeof(Historico_estoque_local), 1, est_his_compra);
			if((!(feof(est_his_compra))) && (strcmp (pesquisa_Historico_compra_cod, Estoque_hist_operacao.codigo) == 0))
			{
				cont_Historico_compra++;
				printf("CODIGO: %s\n",Estoque_hist_operacao.codigo);
				printf("NOME: %s\n",Estoque_hist_operacao.nome);
				printf("PRECO NO DIA: %.2f\n",Estoque_hist_operacao.Preco );
				printf("RETEM RECEITA: %c\n",Estoque_hist_operacao.TipoRemedio);
				printf("CRM: %s\n",Estoque_hist_operacao.crm);
				printf("Quantidade: %d\n",Estoque_hist_operacao.Quantidade );
				
				printf("DATA: %d/%d/%d \n", Estoque_hist_operacao.dia, Estoque_hist_operacao.mes, Estoque_hist_operacao.ano + 1900);
				printf("HORARIO: %d HORAS, %d MINUTOS E %d SEGUNDOS\n", Estoque_hist_operacao.hora,
				Estoque_hist_operacao.minuto, Estoque_hist_operacao.segundo);
				
				printf("Valor total da operacao: RS%.2f\n",Estoque_hist_operacao.Quantidade * Estoque_hist_operacao.Preco);
				printf("|------------------------------------------------|\n");			
			}//if
		}//while
	}//else
	cont_Historico_compra==0?printf("Sem historico para o produto\n"):printf("  ");
	
	fclose(est_his_compra);	
	system("pause");
}


//void Historico_venda(){}


void Vender_prod()
{
	char func_controle_estoque_codigo[10];
	int achou_em_estoque = 0;
	int venda_quantidade = 0;
	time(&segundos);    
	data_hora_atual = localtime(&segundos);
	
	printf("insira um codigo para a busca >>> ");
	scanf("%s", func_controle_estoque_codigo);
	printf("\n");
	
	printf("quantos itens serao vendidos? >>> ");
	scanf("%d", &venda_quantidade);
	printf("\n\n");
	
	
	FILE *vender = fopen("controle_estoque", "ab+");
	//FILE *vender_aux = fopen("controle_estoque_aux", "ab+");
	//Opera_estoque
	
	while((!(feof(vender)) && (achou_em_estoque == 0)))
		{  
			fread(&Opera_estoque , sizeof(Controle_Estoque), 1, vender);
			if((!(feof(vender))) && (strcmp (func_controle_estoque_codigo, Opera_estoque.codigo) == 0))
			{
				achou_em_estoque++;
				printf("\n ----- localizou ----- \n\n");
				
				
				
				if (Opera_estoque.Quantidade < venda_quantidade)
				{
					printf("\n ----- quantidade em estoque e inferior ao da venda ----- \n ----- favor reiniciar a venda -----\n\n");
					
				}
				else
				{
						fclose(vender);
						FILE *est_hist = fopen("controle_estoque", "ab+");
						FILE *est_hist_aux = fopen("controle_estoque_aux", "ab+");
						while(!(feof(est_hist)))
						{
							fread(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist);
							if((!(feof(est_hist))) && (strcmp (func_controle_estoque_codigo, Opera_estoque.codigo) == 0))
							{
								Opera_estoque.Quantidade = Opera_estoque.Quantidade - venda_quantidade;
								fwrite(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist_aux);
							}
							else
							{
								if(!(feof(est_hist)))
								{
									fwrite(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist_aux);
								}
							}
						}
						fclose(est_hist);
						fclose(est_hist_aux);
						
						remove("controle_estoque");
						est_hist = fopen("controle_estoque", "ab+");
						est_hist_aux = fopen("controle_estoque_aux", "ab+");
						
						while(!(feof(est_hist_aux)))
						{
							fread(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist_aux);
							if(!(feof(est_hist_aux)))
							{
								fwrite(&Opera_estoque , sizeof(Controle_Estoque), 1, est_hist);
							}
						}
						fclose(est_hist);
						fclose(est_hist_aux);
						
						remove("controle_estoque_aux");		
				}
				
				
				system("pause");
				
	
			}						
		}
		if (achou_em_estoque == 0)
		{		
			achou_em_estoque++;
			printf("\n\n ----- produto ainda nao adicionado ao estoque -----");
			system("pause");					
		}	
	
	fclose(vender);
	
}


void Comprar(char estoque_cod[], char estoque_nom[], float estoque_prec,
			char estoque_tiporemedio)
{
	
	time(&segundos);    
	data_hora_atual = localtime(&segundos);
	
	FILE *est_his_compra;
    est_his_compra = fopen("historico_de_compras", "ab+"); 				 
    strcpy(Estoque_hist_operacao.codigo, estoque_cod)       ;
    strcpy(Estoque_hist_operacao.nome, estoque_nom)         ;
    Estoque_hist_operacao.Preco        = estoque_prec       ;
    Estoque_hist_operacao.TipoRemedio  = estoque_tiporemedio;
    
 
    printf("Quantos itens devem ser adicionados ao estoque?\n");
	scanf("%d", &Estoque_hist_operacao.Quantidade);
                        
    Estoque_hist_operacao.dia     = data_hora_atual->tm_mday  ;
    Estoque_hist_operacao.mes     = data_hora_atual->tm_mon   ;
    Estoque_hist_operacao.ano     = data_hora_atual->tm_year  ;
    
    Estoque_hist_operacao.hora    = data_hora_atual->tm_hour  ;
    Estoque_hist_operacao.minuto  = data_hora_atual->tm_min   ;
    Estoque_hist_operacao.segundo = data_hora_atual->tm_sec   ;
     
    if ((estoque_tiporemedio  == 's')||(estoque_tiporemedio  == 'S'))
    {
		//salva quem retem receita
		printf("***Este item exige a retencao de receita***\n");
		printf("*******Digite o CRM para prosseguir:*******\n");
		scanf("%s", Estoque_hist_operacao.crm);
		
		fwrite(&Estoque_hist_operacao, sizeof(Historico_estoque_local), 1, est_his_compra);
	    printf("entrou 1");
	}
	else
	{
		//salva quem nao retem receita
		fwrite(&Estoque_hist_operacao, sizeof(Historico_estoque_local), 1, est_his_compra);
		printf("entrou 0");
	}
	//fclose(est_his_compra);
	
	
	printf("CODIGO: %s\n",Estoque_hist_operacao.codigo);
	printf("NOME: %s\n",Estoque_hist_operacao.nome);
	printf("PRECO: %f\n",Estoque_hist_operacao.Preco );
	printf("RETEM RECEITA: %c\n",Estoque_hist_operacao.TipoRemedio);
	//printf("CÓDIGO: %s\n",Opera_estoque.CRM);
	printf("Total de produtos: %d\n",Estoque_hist_operacao.Quantidade );

		
	
	func_controle_estoque(3, Estoque_hist_operacao.codigo, Estoque_hist_operacao.nome, Estoque_hist_operacao.Preco, Estoque_hist_operacao.TipoRemedio , Estoque_hist_operacao.Quantidade);
	fclose(est_his_compra);	
	system("pause");
}




void buscaitem(int estoque_operacao)
{
	char est_cod[10];
	char est_nom[100];
	float est_prec;
	char est_tiporemedio;
	char estoque_pesquisa_codigo[10];
	
	printf("insira um codigo para a busca: ");
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

			
			switch(estoque_operacao)
			{
									
				case 2 :
						Comprar(est_cod, est_nom , est_prec , est_tiporemedio);

					break;						
			}				
		}
	}
	fclose(Pont_arq_main);
}


int Estoque (void)
{	
	char localllllllll[10];

	int Selecao;
    do
    {
		system ("cls");	
        Selecao = 0;
        //Exibindo o menu
        printf("|-----------------ESTOQUE-----------------|\n");
        printf("|1 - Verificar Estoque Atual              |\n");
        printf("|2 - Adicionar OU comprar medicamentos    |\n");
        printf("|3 - Vender OU remover medicamentos       |\n");
        printf("|4 - historico geral de compras           |\n");
        printf("|5 - historico individual de compras      |\n");
        printf("|6 - historico geral de vendas      ******|\n");
        printf("|7 - historico individual de vendas ******|\n");
        printf("|8 - Verificar apenas um item em estoque  |\n");
        printf("|0 - Voltar ao Menu Inicial               |\n");
        printf("|-----------------------------------------|\n");
        
        scanf("%d",&Selecao);
        
        switch(Selecao){
            case 1 :
				
				strcpy(localllllllll, "aa");
				func_controle_estoque(1, localllllllll, localllllllll, 0, '0' , 0);

            break;				
            case 2 :
				buscaitem(Selecao);
            break;
            
			case 3 :
				Vender_prod();
            break;
            
            case 4 :
				Historico_compra(4);
			break;
			
			case 5 :
				Historico_compra(5);
			break;
			
			case 8 :
				printf("insira um codigo para a busca >>> ");
				scanf("%s", localllllllll);
				printf("\n");
				func_controle_estoque(2, localllllllll, localllllllll, 0, '0' , 0);
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


