#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct args_verificacao_coluna {
    int linha;
    int coluna;
};



#define MAX_SIZE 9
#define MIN_SUBGRID_SIZE 3
#define MAX_SIZE_ROW_COL 9

int verificar_tamanho_segunda_linha(char *nome_arquivo);

int verificar_tamanho_sudoku(char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char buffer[255];

    // Lê a primeira linha (tamanho do Sudoku)
    fgets(buffer, 255, arquivo);

    // Verificar se há algum número menor que 9 na primeira linha
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == '\n') break;
        if(i % 2 == 0 && (buffer[i] - '0' < 9)) {
            
            exit(EXIT_FAILURE);
            return 0;
        }
    }

    fclose(arquivo);

    if (!verificar_tamanho_segunda_linha(nome_arquivo)) {
        exit(EXIT_FAILURE);
    }

    return 1;
}

int verificar_tamanho_segunda_linha(char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char buffer[255];

    // Pula a primeira linha
    fgets(buffer, 255, arquivo);

    // Lê a segunda linha
    fgets(buffer, 255, arquivo);

    for(int i = 0; i <= strlen(buffer); i++) {
        if(buffer[i] == '\n') break;
        if(i % 2 == 0 && (buffer[i] - '0' < 3)) {
            
            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

void *threads_linha3(void *nome_arquivo) {
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as duas primeiras linhas
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);

    // Lê a terceira linha e armazena os valores no array sudoku
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == '\n') break;
        if(i % 2 == 0) {
            sudoku[2][i/2] = buffer[i] - '0';
        }
    }

    fclose(arquivo);

    // Verifica se há números repetidos na terceira linha
    int repetido = 0;
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = i+1; j < MAX_SIZE; j++) {
            if(sudoku[2][i] == sudoku[2][j]) {
                
                repetido = 1;
            }
        }
    }

    if(!repetido) {
        
    }

    return NULL;
}

void *threads_linha4(void *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as três primeiras linhas
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);

    // Lê a quarta linha e armazena os valores no array sudoku
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == '\n') break;
        if(i % 2 == 0) {
            sudoku[3][i/2] = buffer[i] - '0';
        }
    }

    fclose(arquivo);

    // Verifica se há números repetidos na quarta linha
    int repetido = 0;
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = i+1; j < MAX_SIZE; j++) {
            if(sudoku[3][i] == sudoku[3][j]) {
                printf("Numero repetido na quarta linha: %d\n", sudoku[3][i]);
                repetido = 1;
            }
        }
    }

    if(!repetido) {
        
    }

    return NULL;
}

void *threads_linha5(void *nome_arquivo) {
   
 FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as primeiras quatro linhas
    for (int i = 0; i < 4; i++) {
        fgets(buffer, 255, arquivo);
    }
    
    // Lê a quinta linha e armazena os valores no array sudoku
    if (fgets(buffer, 255, arquivo) == NULL) {
        printf("Erro ao ler a quinta linha do arquivo.\n");
        fclose(arquivo);
        return NULL;
    }
    for (int i = 0; i < MAX_SIZE; i++) {
        if (buffer[i*2] == '\n') break;
        sudoku[4][i] = buffer[i*2] - '0';
    }

    fclose(arquivo);

    // Verifica se há números repetidos na quinta linha do sudoku
    int contador_numeros[MAX_SIZE] = {0};
    int flag_repetido = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        int numero_atual = sudoku[4][i];
        if (contador_numeros[numero_atual - 1] == 1) {
            
            flag_repetido = 1;
        } else {
            contador_numeros[numero_atual - 1] = 1;
        }
    }

    if (!flag_repetido) {
        printf("Não há números repetidos na quinta linha.\n");
    }

    return NULL;
}


void *threads_linha6(void *nome_arquivo) {
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as primeiras cinco linhas
    for(int i=0; i<5; i++){
        fgets(buffer, 255, arquivo);
    }
    
    // Lê a sexta linha e armazena os valores no array sudoku
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == '\n') break;
        if(i % 2 == 0) {
            sudoku[5][i/2] = buffer[i] - '0';
        }
    }

    fclose(arquivo);

    // Verifica se há números repetidos na sexta linha do sudoku
    int contador_numeros[MAX_SIZE_ROW_COL] = {0};
    for(int i = 0; i < MAX_SIZE_ROW_COL; i++) {
        int numero_atual = sudoku[5][i];
        if(contador_numeros[numero_atual - 1] == 1) {
           
        } else {
            contador_numeros[numero_atual - 1] = 1;
        }
    }

    return NULL;
}

void *threads_linha7(void *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as primeiras seis linhas
    for(int i = 0; i < 6; i++) {
        fgets(buffer, 255, arquivo);
    }

    // Lê a sétima linha e armazena os valores no array sudoku
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == '\n') break;
        if(i % 2 == 0) {
            sudoku[6][i/2] = buffer[i] - '0';
        }
    }

    fclose(arquivo);

    // Verifica se há números repetidos na sétima linha
    int contador_numeros[MAX_SIZE_ROW_COL] = {0};
    int numero_atual;
    int tem_repeticao = 0;
    for(int i = 0; i < MAX_SIZE_ROW_COL; i++) {
        numero_atual = sudoku[6][i];
        if(contador_numeros[numero_atual - 1] == 1) {
            
            tem_repeticao = 1;
        } else {
            contador_numeros[numero_atual - 1] = 1;
        }
    }
    if (!tem_repeticao) {
        
    }

    return NULL;
}

void *threads_linha8(void *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as sete primeiras linhas
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);

    // Lê a oitava linha e armazena os valores no array sudoku
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == '\n') break;
        if(i % 2 == 0) {
            sudoku[7][i/2] = buffer[i] - '0';
        }
    }

    fclose(arquivo);

    // Verifica se há números repetidos na oitava linha
    int repetido = 0;
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = i+1; j < MAX_SIZE; j++) {
            if(sudoku[7][i] == sudoku[7][j]) {
                
                repetido = 1;
            }
        }
    }

    if(!repetido) {
        
    }

    return NULL;
}

void *threads_linha9(void *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as primeiras oito linhas
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);

    // Lê a nona linha e armazena os valores no array sudoku
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == '\n') break;
        if(i % 2 == 0) {
            sudoku[8][i/2] = buffer[i] - '0';
        }
    }

    fclose(arquivo);

    // Verifica se há números repetidos na nona linha
    int numeros_repetidos[MAX_SIZE_ROW_COL] = {0};
    for(int i = 0; i < MAX_SIZE; i++) {
        if(numeros_repetidos[sudoku[8][i] - 1]) { // número já encontrado anteriormente
            
        } else {
            numeros_repetidos[sudoku[8][i] - 1] = 1;
        }
    }

    return NULL;
}

void *threads_linha10(void *nome_arquivo) {
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as primeiras nove linhas
    for(int i=0; i<9; i++) {
        fgets(buffer, 255, arquivo);
    }

    // Lê a décima linha e armazena os valores no array sudoku
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == '\n') break;
        if(i % 2 == 0) {
            sudoku[9][i/2] = buffer[i] - '0';
        }
    }

    fclose(arquivo);

    // Verifica se há números repetidos na décima linha do sudoku
    int contador_numeros[MAX_SIZE_ROW_COL] = {0};
    for(int i = 0; i < MAX_SIZE_ROW_COL; i++) {
        int numero_atual = sudoku[9][i];
        if(contador_numeros[numero_atual - 1] == 1) {
            printf("O número %d está repetido na décima linha.\n", numero_atual);
        } else {
            contador_numeros[numero_atual - 1] = 1;
        }
    }

    return NULL;
}

void *threads_linha11(void *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as primeiras dez linhas
    for(int i = 0; i < 10; i++) {
        fgets(buffer, 255, arquivo);
    }

    // Lê a décima primeira linha e armazena os valores no array sudoku
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < strlen(buffer); i++) {
        if(buffer[i] == '\n') break;
        if(i % 2 == 0) {
            sudoku[10][i/2] = buffer[i] - '0';
        }
    }

    fclose(arquivo);

    // Verifica se há números repetidos na décima primeira linha do sudoku
    int contador_numeros[MAX_SIZE] = {0};
    for(int i = 0; i < MAX_SIZE; i++) {
        int numero_atual = sudoku[10][i];
        if(contador_numeros[numero_atual - 1] == 1) {
            
        } else {
            contador_numeros[numero_atual - 1] = 1;
        }
    }

    return NULL;
}



void *verificar_coluna(void *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as primeiras duas linhas
    fgets(buffer, 255, arquivo);
    fgets(buffer, 255, arquivo);

    // Lê as linhas 3, 4 e 5 até o terceiro número e armazena os valores no array sudoku
    for (int i = 2; i < 5; i++) {
        fgets(buffer, 255, arquivo);
        for(int j = 0; j < 3; j++) {
            int num = buffer[j*2] - '0';
            sudoku[i][j] = num;
        }
    }

    fclose(arquivo);

    // Verifica se há números repetidos nas linhas 3, 4 e 5
    for (int i = 2; i < 5; i++) {
      int existem_repetidos = 0;
      for(int j = 0; j < 3; j++) {
          for(int k = j+1; k < 3; k++) {
              if(sudoku[i][j] == sudoku[i][k]) {
                  
                  existem_repetidos = 1;
              }
          }
      }
      
      if(!existem_repetidos) {
          printf("Nenhum número repetido na subgrade %d.\n", i+1);
      }
    }

    return NULL;
}


void *verificar_2_coluna(void *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Ler as primeiras cinco linhas do arquivo
    for(int i = 0; i < 5; i++) {
        fgets(buffer, 255, arquivo);
    }
    
    // Lê a sexta linha e armazena os valores no array sudoku, parando no terceiro número
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < MAX_SIZE; i++) {
        if(i >= 3) break;
        if(buffer[i*2] == '\n') break;
        if(buffer[i*2+1] == ' ') i++; // ignora os espaços entre os números
        sudoku[5][i] = buffer[i*2] - '0';
    }

    // Lê a sétima linha e armazena os valores no array sudoku, parando no terceiro número
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < MAX_SIZE; i++) {
        if(i >= 3) break;
        if(buffer[i*2] == '\n') break;
        if(buffer[i*2+1] == ' ') i++; // ignora os espaços entre os números
        sudoku[6][i] = buffer[i*2] - '0';
    }

    // Lê a oitava linha e armazena os valores no array sudoku, parando no terceiro número
    fgets(buffer, 255, arquivo);
    for(int i = 0; i < MAX_SIZE; i++) {
        if(i >= 3) break;
        if(buffer[i*2] == '\n') break;
        if(buffer[i*2+1] == ' ') i++; // ignora os espaços entre os números
        sudoku[7][i] = buffer[i*2] - '0';
    }

    fclose(arquivo);

    // Verifica se há números repetidos na coluna dos terceiros números
    for(int i = 0; i < 3; i++) {
        int numero_atual = sudoku[5][i*3+2];
        int repetido = 0;
        for(int j = 6; j <= 8; j++) {
            if(sudoku[j][i*3+2] == numero_atual) {
                
                repetido = 1;
                break;
            }
        }
        if(!repetido) {
            printf("Nenhum número repetido na coluna dos terceiros números.\n");
        }
    }

    return NULL;
}

void *verificar_repeticoes_9a11(void *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    char buffer[255];
    int sudoku[MAX_SIZE][MAX_SIZE];

    // Pula as oito primeiras linhas
    for(int i = 0; i < 8; i++) {
        fgets(buffer, 255, arquivo);
    }

    // Lê as três últimas linhas e armazena os valores no array sudoku
    for(int i = 8; i < MAX_SIZE; i++) {
        fgets(buffer, 255, arquivo);
        for(int j = 0; j < MAX_SIZE-2; j += 2) {
            sudoku[i][j/2] = buffer[j] - '0';
        }
    }

    fclose(arquivo);

    // Verifica se há números repetidos nas três últimas linhas do sudoku
    int repetido = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < MAX_SIZE-2; j++) {
            for(int k = j+1; k < MAX_SIZE-2; k++) {
                if(sudoku[i+8][j] == sudoku[i+8][k]) {
                    
                    repetido = 1;
                }
            }
        }
    }

    if(!repetido) {
        printf("Nenhum número repetido nas últimas três linhas.\n");
    }

    return NULL;
}


int main(int argc, char* argv[]) {
    
    pthread_t thread1, thread2, thread3, thread4, thread5, thread6, thread7,thread8,thread9,thread10;

    if (argc != 2){
        printf("\nInvalid number of parameters\n");
        exit(EXIT_FAILURE);
    }
    
    if (!verificar_tamanho_sudoku(argv[1])) {
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&thread1, NULL, threads_linha3, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }

    if(pthread_create(&thread2, NULL, threads_linha4, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }
    
    if(pthread_create(&thread3, NULL, threads_linha5, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }

    if(pthread_create(&thread4, NULL, threads_linha6, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }

    if(pthread_create(&thread5, NULL, threads_linha7, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }

    if(pthread_create(&thread6, NULL, threads_linha8, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }
    if(pthread_create(&thread7, NULL, threads_linha9, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }
    if(pthread_create(&thread8, NULL, threads_linha10, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }
    if(pthread_create(&thread9, NULL, threads_linha11, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }
    
    

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    pthread_join(thread6, NULL);
    pthread_join(thread7, NULL);
    pthread_join(thread8, NULL);
    pthread_join(thread9, NULL);    
    
     
    struct args_verificacao_coluna args;
    args.linha = 3;
    args.coluna = 0;
    pthread_t thread11;
    if(pthread_create(&thread11, NULL, verificar_coluna, &args)) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }
    
    
    
    if(pthread_create(&thread10, NULL, verificar_2_coluna, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }
   
    pthread_join(thread10, NULL);
    
    
    pthread_t thread12;
    if(pthread_create(&thread12, NULL, verificar_repeticoes_9a11, argv[1])) {
        fprintf(stderr, "Erro criando a thread.\n");
        return 1;
    }
    
    


    FILE *arquivo;
    int caractere;

    arquivo = fopen(argv[1], "r");

    if (arquivo == NULL) { // verifica se ocorreu um erro na abertura do arquivo
        printf("Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    while ((caractere = fgetc(arquivo)) != EOF) { // lê cada caractere do arquivo até chegar ao fim
        printf("%c", caractere);
    }

    fclose(arquivo);

    return 0;
}

