#include <gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char* generateSquare(int n);
static void button1_clicked(GtkWidget *widget, gpointer data);
static void button2_clicked(GtkWidget *widget, gpointer data);
static void button3_clicked(GtkWidget *widget, gpointer data);
static void button4_clicked(GtkWidget *widget, gpointer data);
static void button5_clicked(GtkWidget *widget, gpointer data);
static void button6_clicked(GtkWidget *widget, gpointer data);
static void button7_clicked(GtkWidget *widget, gpointer data);
static void button8_clicked(GtkWidget *widget, gpointer data);

GtkTextBuffer *buffer;

//---------------------------------Magic Square ---------------------------------
char* generateSquare(int n){
    int magicSquare[n][n];
    int a; 

    // set all slots as 0
    memset(magicSquare, 0, sizeof(magicSquare));

    // Initialize position for 1
    int i = n/2;
    int j = n-1;

    // One by one put all values in magic square
    for (int num=1; num <= n*n; )
    {
        if (i==-1 && j==n) //3rd condition
        {
            j = n-2;
            i = 0;
        }
        else
        {
            // 1st condition helper if next number
            // goes to out of square's right side
            if (j == n)
                j = 0;

            // 1st condition helper if next number
            // is goes to out of square's upper side
            if (i < 0)
                i=n-1;
        }
        if (magicSquare[i][j]) //2nd condition
        {
            j -= 2;
            i++;
            continue;
        }
        else
            magicSquare[i][j] = num++; //set number

        j++; i--; //1st condition
    }
    
    
    // Print magic square
    printf("The Magic Square for n=%d:\nSum of "
       "each row or column %d:\n\n",  n, n*(n*n+1)/2);
   
    char* matrix  = (char*) malloc(sizeof(char)*10*10*10);
    matrix[0] = '\0';
    for (i=0; i<n; i++)
    {

        for (j=0; j<n; j++) {
        	//a=magicSquare[i][j]+48;
        	//ptr=&a;
        	//gtk_text_buffer_set_text(buffer, "a", -1);
        	char numero[12];
            //printf("%3d ", magicSquare[i][j]);
            sprintf(numero, "  %4d  ", magicSquare[i][j]);
            strcat(matrix, numero);
        }
        strcat(matrix, "\n");
        //printf("\n");
    }
    printf("%s", matrix);

    return matrix;
}

void CriarMMImpar (int* M, const int Dim) { //matriz que cria matriz mágica ímpar
    int i = Dim/2; //índice da linha, começa no valor mediano
    int j = Dim - 1; //índice da matriz, começa na última matriz
    int num = 1; //número a ser inserido, começa em 1

    while(num <= Dim*Dim) { //enquanto num for menor ou igual a Dim ao quadrado

    //Seção - verifica limite
    //essa seção do código verifica se os índices apontam para posições corretas
    //como o algoritmo se baseia em adicionar elementos com base na posição anterior
    //de forma a adicionar o próximo elemento uma linha acima e uma coluna à direita
    //e mover uma coluna à esquerda quando o número anterior for múltiplo da ordem da matriz
    //temos 3 ocasiões de extrapolação de limites
        if (j == -1) //se a coluna extrapolar o limite inferior (uma coluna à esquerda da coluna 0)
            j = Dim - 1; //coluna <--- última coluna
        if (j == Dim) //se a coluna extrapolar o limite superior (uma coluna à direita da última coluna)
            j = 0; //coluna <--- primeira coluna
        if (i == -1) //se a linha extrapolar o limite superior (uma linha acima da primeira linha)
            i = Dim - 1; //linha <--- última linha
    //Fim desta seção

    //Seção - atribui valor
        *(M + i*Dim + j) = num++; //atribui valor a elemento na posição i+1,j+1
        //e incrementa o valor de num em uma unidade

        if ((num - 1)%Dim == 0) { //se o elemento anterior for divisível pela ordem
            j--; //mova uma coluna à esquerda
        } else{ //caso contrário
        //procedimento padrão
        i--; //mova uma linha acima
        j++; //mova uma coluna à direita
        }
    //Fim desta seção
    }
}


char* CriarMMMult4 (int *M, const int Dim) { //matriz que cria matriz mágica múltipla de 4
    int i, j;  //declaração dos índices de linha e coluna

    //atribuindo valores a matriz
    //começando com o valor 1
    for (i = 0; i < Dim; i++)
        for (j = 0; j < Dim; j++)
            *(M + i*Dim + j) = (Dim*i) + j + 1; //M[i][j] = i*N + j + 1

    //divindo matriz em quatro setores
    //parte superior esquerda da matriz
    for (i = 0; i < Dim/4; i++)
        for (j = 0; j < Dim/4; j++)
            *(M + i*Dim + j) = (Dim*Dim + 1) - *(M + i*Dim + j);
            //M[i][j] = (i*i + 1) - M[i][j]

    //parte superior direita da matriz
    for (i = 0; i < Dim/4; i++)
        for (j = 3 * (Dim/4); j < Dim; j++) //fator multiplicativo: 3 * (Dim/4)
            *(M + i*Dim + j) = (Dim*Dim + 1) - *(M + i*Dim + j);
            //M[i][j] = (i*i + 1) - M[i][j]

    //parte inferior esquerda da matriz
    for (i = 3 * Dim/4; i < Dim; i++) //fator multiplicativo: 3 * (Dim/4)
        for (j = 0; j < Dim/4; j++)
            *(M + i*Dim + j) = (Dim*Dim + 1) - *(M + i*Dim + j);
            //M[i][j] = (i*i + 1) - M[i][j]

    //parte inferior direita da matriz
    for (i = 3 * Dim/4; i < Dim; i++) //fator multiplicativo: 3 * (Dim/4)
        for (j = 3 * Dim/4; j < Dim; j++) //fator multiplicativo: 3 * (Dim/4)
            *(M + i*Dim + j) = (Dim*Dim + 1) - *(M + i*Dim + j);
            //M[i][j] = (i*i + 1) - M[i][j]

    //centro da matriz
    for (i = Dim/4; i < 3 * Dim/4; i++)
        for (j = Dim/4; j < 3 * Dim/4; j++)
            *(M + i*Dim + j) = (Dim*Dim + 1) - *(M + i*Dim + j);
            //M[i][j] = (i*i + 1) - M[i][j]
//--------------------------------------------------------------------------
//				Área de testes (print no console)        
//--------------------------------------------------------------------------
	printf("\nImprimindo matriz magica de ordem %i:\n\n", Dim);
	char* matrix  = (char*) malloc(sizeof(char)*10*10*10);
    matrix[0] = '\0';
    for (i = 0; i < Dim; i++) {
        for (j = 0; j < Dim; j++){
        	char numero[12];
            sprintf(numero, "  %3d  ", *(M+i*Dim+j));
            strcat(matrix, numero);
            //printf("%4i", *(M+i*Dim+j));
    	}
    	//printf("\n");
        strcat(matrix, "\n");
    } 
     printf("%s", matrix);

    return matrix;   
}
char* CriarMMParND4 (int* M, const int Dim) {
    int i, j; //índices de linha e coluna
    int grade, nColsEsq, nColsDir, tmp; //valores importantes para seccionar a matriz
    int tamanho = Dim * Dim; //tamanho total da matriz
    int metade_n = Dim/2; //metade da ordem da matriz mágica
    int tamanhosubgrade = tamanho/4; //tamanho de cada subgrade da matriz
    int subgrade[metade_n][metade_n]; CriarMMImpar(&subgrade[0][0], metade_n);
    //cada subgrade se torna uma matriz impar de ordem n/2
    int fatorgrade[] = {0, 2, 3, 1};
    //fator multiplicativo de grades

    for (i = 0; i < Dim; i++) { //varrendo todas as linhas
        for (j = 0; j < Dim; j++) { //e colunas
            grade = (i/metade_n) * 2 + (j/metade_n); 
            *(M + i*Dim + j) = subgrade[i % metade_n][j % metade_n];
            *(M + i*Dim + j) += fatorgrade[grade] * tamanhosubgrade;
        }
    }

    nColsEsq = metade_n/2;
    nColsDir = nColsEsq-1;

    for (i = 0; i < metade_n; i++)
        for (j = 0; j < Dim; j++) {
            if (j < nColsEsq || j >= Dim - nColsDir || (j == nColsEsq && i == nColsEsq)) {

                if (j == 0 && i == nColsEsq)
                    continue;

                tmp = *(M + i*Dim + j);
                *(M + i*Dim + j) = *(M + ((i + metade_n)*Dim) + j);
                *(M + i*Dim + j) = tmp;
            }
        }
//--------------------------------------------------------------------------
//				Área de testes (print no console)        
//--------------------------------------------------------------------------
	printf("\nImprimindo matriz magica de ordem %i:\n\n", Dim);
	char* matrix  = (char*) malloc(sizeof(char)*10*10*10);
    matrix[0] = '\0';
    for (i = 0; i < Dim; i++) {
        for (j = 0; j < Dim; j++){
            char numero[12];
            sprintf(numero, "%4d", *(M+i*Dim+j));
            strcat(matrix, numero);
            //printf("%4i", *(M+i*Dim+j));
        }
       // printf("\n");
        strcat(matrix, "\n");
    }  
     printf("%s", matrix);

    return matrix;    
}
//----------------------------------------------------------------------------
static void button1_clicked(GtkWidget *widget, gpointer data){
	char* matrix = generateSquare(3);
	gtk_text_buffer_set_text(buffer, matrix, -1);

}//fuction when click button1
static void button2_clicked(GtkWidget *widget, gpointer data){
	int b[4][4];
	char*matrix = CriarMMMult4(&b[0][0],4);
	gtk_text_buffer_set_text(buffer, matrix, -1);	
}//fuction when click button2
static void button3_clicked(GtkWidget *widget, gpointer data){
	char* matrix = generateSquare(5);
	gtk_text_buffer_set_text(buffer, matrix, -1);
}//fuction when click button3
static void button4_clicked(GtkWidget *widget, gpointer data){
	int a[6][6];
	char* matrix = CriarMMParND4(&a[0][0],6);
	gtk_text_buffer_set_text(buffer, matrix, -1);	
}//fuction when click button4
static void button5_clicked(GtkWidget *widget, gpointer data){
	char* matrix = generateSquare(7);
	gtk_text_buffer_set_text(buffer, matrix, -1);
}//fuction when click button5
static void button6_clicked(GtkWidget *widget, gpointer data){
	int b[8][8];
	char* matrix = CriarMMMult4(&b[0][0],8);
	gtk_text_buffer_set_text(buffer, matrix, -1);
}//fuction when click button6
static void button7_clicked(GtkWidget *widget, gpointer data){
	char* matrix = generateSquare(9);
	gtk_text_buffer_set_text(buffer, matrix, -1);
}//fuction when click button7
static void button8_clicked(GtkWidget *widget, gpointer data){
	int a[10][10];
	char* matrix = CriarMMParND4(&a[0][0],10);
	gtk_text_buffer_set_text(buffer, matrix, -1);	
}//fuction when click button8


int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv); //initialize the gtk
	GtkWidget *window, *label, *button1, *button2,*button3,*button4,*button5,*button6,*button7,*button8; //declare the needed variables
    GtkWidget *mainbox = gtk_grid_new();
    GtkWidget *text_view;


  

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //create the window
	gtk_window_set_title (GTK_WINDOW (window), "Matriz Mágica");
  	gtk_window_set_default_size (GTK_WINDOW (window), 500, 300);

/*gtk_grid_attach (GtkGrid *grid, GtkWidget *child,
                 gint left,
                 gint top,
                 gint width,
                 gint height)*/

	label=gtk_label_new("Escolha a Matriz Mágica que desja visualizar: ");
	gtk_widget_set_halign (label, GTK_ALIGN_START);
    gtk_grid_attach(GTK_GRID(mainbox), label, 1, 0, 2, 1);


	button1=gtk_button_new_with_label("3 x 3");
	gtk_widget_set_size_request(button1, 20,50);
	gtk_widget_set_halign(button1, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(mainbox), button1, 0, 1, 1, 1);	
	g_signal_connect(button1, "clicked", G_CALLBACK(button1_clicked), NULL);	

	button2=gtk_button_new_with_label("4 x 4");
	gtk_widget_set_size_request(button2, 20,50);
	gtk_widget_set_halign(button2, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(mainbox), button2, 0, 2, 1, 1);
	g_signal_connect(button2, "clicked", G_CALLBACK(button2_clicked), NULL);	

	button3=gtk_button_new_with_label("5 x 5");
	gtk_widget_set_size_request(button3, 20,50);
	gtk_widget_set_halign(button3, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(mainbox), button3, 0, 3, 1, 1);
	g_signal_connect(button3, "clicked", G_CALLBACK(button3_clicked), NULL);	


	button4=gtk_button_new_with_label("6 x 6");
	gtk_widget_set_size_request(button4, 20,50);
	gtk_widget_set_halign(button4, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(mainbox), button4, 0, 4, 1, 1);
	g_signal_connect(button4, "clicked", G_CALLBACK(button4_clicked), NULL);	


	button5=gtk_button_new_with_label("7 x 7");
	gtk_widget_set_size_request(button5, 20,50);
	gtk_widget_set_halign(button5, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(mainbox), button5, 1, 1, 1, 1);
	g_signal_connect(button5, "clicked", G_CALLBACK(button5_clicked), NULL);		

	button6=gtk_button_new_with_label("8 x 8");
	gtk_widget_set_size_request(button6, 20,50);
	gtk_widget_set_halign(button6, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(mainbox), button6, 1, 2, 1, 1);
	g_signal_connect(button6, "clicked", G_CALLBACK(button6_clicked), NULL);	

	button7=gtk_button_new_with_label("9 x 9");
	gtk_widget_set_size_request(button7, 20,50);
	gtk_widget_set_halign(button7, GTK_ALIGN_START);		
	gtk_grid_attach(GTK_GRID(mainbox), button7, 1, 3, 1, 1);
	g_signal_connect(button7, "clicked", G_CALLBACK(button7_clicked), NULL);	

	button8=gtk_button_new_with_label("10 x 10");
	gtk_widget_set_size_request(button8, 20,50);
	gtk_widget_set_halign(button8, GTK_ALIGN_START);
	gtk_grid_attach(GTK_GRID(mainbox), button8, 1, 4, 1, 1);
	g_signal_connect(button8, "clicked", G_CALLBACK(button8_clicked), NULL);	


	text_view = gtk_text_view_new();
	gtk_widget_set_size_request(text_view, 250,300);
	gtk_grid_attach(GTK_GRID(mainbox), text_view, 2, 1, 2, 3);



	/* Obtaining the buffer associated with the widget. */
 	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (text_view));
  	/* Set the default buffer text. */ 
  	//gtk_text_buffer_set_text(buffer, "teste", -1);

   /* char strint[12];
  	for (int i = 0; i < 3; ++i){
  		for (int j = 0; j < 3; ++j){
  			int *aux; int iter;
  			aux=&A[i][j]+48;

  			sprintf(strint, "%d", 187612);
  			gtk_text_buffer_set_text(buffer, strint, -1);

  		}
  	}*/


	//gtk_label_set_text(GTK_LABEL(label), "Daniel");
	g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL); //starts the window
	//g_signal_connect(label,"",G_CALLBACK(NULL),NULL);	 

	//gtk_container_add(GTK_CONTAINER(window),(label,button1));
	gtk_container_add(GTK_CONTAINER(window), mainbox);
	gtk_widget_show_all(window); //we show all widgets
	gtk_main();	//start the main loop
	return 0;
}