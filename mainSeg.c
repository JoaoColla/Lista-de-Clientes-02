#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_LIN 150
#define MAX_NOME 100

typedef struct Pessoa{
    char nome [MAX_NOME];
    long int rg;
} Pessoa;


int particiona (Pessoa **lista_organiazada, int baixo, int alto, int *comparacao, int *movimentacao){

    Pessoa pivo = *lista_organiazada[(baixo + alto)/2];
    int i = baixo -1;
    int j = alto + 1;

    while (true){
        do{
            i++;
           ( *comparacao)++;
        } while (lista_organiazada[i]->rg < pivo.rg);

        do{
            j--;
            (*comparacao)++;
        } while (lista_organiazada[j]->rg > pivo.rg);

        (*comparacao)++;
        if (i >= j){
            return j;
        }

        (*movimentacao) += 3;
        Pessoa *aux = lista_organiazada[i];
        lista_organiazada[i] = lista_organiazada[j];
        lista_organiazada[j] = aux;
        
    }
}

void quikSort (Pessoa **arr, int baixo, int alto, int *comparacao, int *movimentacao){
    if (baixo < alto){
        int p = particiona(arr, baixo, alto, comparacao, movimentacao);

        quikSort(arr, baixo, p, comparacao, movimentacao);
        quikSort(arr, p+1, alto, comparacao, movimentacao);
    }

}

void merge(Pessoa **arr, int l, int m, int r, int *comparacao, int *movimentacao) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Pessoa **L = (Pessoa **) malloc(n1 * sizeof(Pessoa *));
    Pessoa **R = (Pessoa **) malloc(n2 * sizeof(Pessoa *));

    if (L == NULL || R == NULL) {
        printf("Erro de alocacao de memoria no merge.\n");
        if (L) free(L);
        if (R) free(R);
        return;
    }

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        (*comparacao)++;
        if (L[i]->rg <= R[j]->rg) {
            arr[k++] = L[i++];
            (*movimentacao)++;
        } else {
            arr[k++] = R[j++];
            (*movimentacao)++;
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
        (*movimentacao)++;
    }

    while (j < n2) {
        arr[k++] = R[j++];
        (*movimentacao)++;
    }

    free(L);
    free(R);
}

void mergeSort(Pessoa **arr, int l, int r, int *comparacao, int *movimentacao) {
    (*comparacao)++;
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, comparacao, movimentacao);
        mergeSort(arr, m + 1, r, comparacao, movimentacao);
        merge(arr, l, m, r, comparacao, movimentacao);
    }
}

int main(){

    int i=0, num_vagas, num_pessoas=0, opcao, organizado = 0;
    char linha [MAX_LIN], nome [MAX_NOME];
    long int rg;

    Pessoa *listaPessoas;

    FILE *arq = fopen("C://Users//joaod//MINHAS PASTAS//UTFPR//2 Periodo//Estrutura de Dados-01//Lista de Clientes 02//NomeRG100M.txt", "r");

    if (arq == NULL){
        printf("Erro abrindo o arquivo");
        return 1;
    }

    printf("Quantas pessoas serao registradas? ");
    scanf("%d", &num_vagas);

    listaPessoas = (Pessoa *) malloc(num_vagas * sizeof(Pessoa));

    if (listaPessoas == NULL){
        printf("Erro alocando memoria");
        fclose(arq);
        return 0;
    }

    rewind(arq);

    for (i=0; i<num_vagas && fgets(linha, MAX_LIN, arq); i++){

        if (sscanf (linha, "%[^,], %ld", nome, &rg) == 2 && nome[0] != '\0'){
            strcpy(listaPessoas[num_pessoas].nome, nome);
            listaPessoas[num_pessoas].rg = rg;

            num_pessoas++;
        }
    }

    fclose(arq);

    int comparacao = 0, movimentacao = 0, listaCriada = 0;
    double tempo = 0;
    Pessoa **lista_organiazada = NULL;

    printf("\nEscolha uma opcao pelo numero:\n"
    "[ 1 ] - Inserir no inicio da lista\n"
    "[ 2 ] - Inserir no fim da lista\n"
    "[ 3 ] - Inserir na posicao N da lista\n"
    "[ 4 ] - Retirar um no do inicio da lista\n"
    "[ 5 ] - Retirar um no no fim da lista\n"
    "[ 6 ] - Retirar um no na posição N\n"
    "[ 7 ] - Procurar um no com o campo RG\n"
    "[ 8 ] - Mostrar a lista na tela\n"
    "[ 9 ] - Salvar a lista em um arquivo\n"
    "[ 10 ] - Ler a lista de um arquivo\n"
    "[ 11 ] - Sair do sistema\n\n"
    "[ 12 ] - Ordenar\n\n");
    scanf("%d", &opcao);

    while (opcao != 11){

            if(opcao == 1){

                comparacao = 0;
                movimentacao = 0;

                comparacao ++;
                if (num_pessoas >= num_vagas) {

                printf("Lista cheia.\n");
                    opcao=0;
                    continue;
                }

                printf("Nome: ");
                scanf("%s", nome);
                printf("Rg: ");
                scanf("%ld", &rg);

                clock_t inicioTempo = clock();

                for (i=num_pessoas; i>0; i--, comparacao ++){
                    movimentacao ++;
                    listaPessoas[i] = listaPessoas[i-1];
                }

                strcpy(listaPessoas[0].nome, nome);
                listaPessoas[0].rg = rg;

                num_pessoas ++;

                clock_t fimTempo = clock();

                tempo = (double)(fimTempo-inicioTempo) / CLOCKS_PER_SEC;

                printf("Nome: %s  |Rg: %ld  |C: %d  |M  %d  |Tempo: %.12f |Posicao: %d\n", nome, rg, comparacao, movimentacao, tempo, 0);

            }else if(opcao == 2){

                comparacao = 0;
                movimentacao = 0;


                comparacao ++;
                if (num_pessoas >= num_vagas) {

                printf("Lista cheia.\n");
                    opcao=0;
                    continue;
                }

                printf("Nome: ");
                scanf("%s", nome);
                printf("Rg: ");
                scanf("%ld", &rg);

                clock_t inicioTempo = clock();

                strcpy(listaPessoas[num_pessoas].nome, nome);
                listaPessoas[num_pessoas].rg = rg;

                num_pessoas ++;

                clock_t fimTempo = clock();

                tempo = (double)(fimTempo-inicioTempo) / CLOCKS_PER_SEC;


                printf("Nome: %s  |Rg: %ld  |C: %d  |M  %d  |Tempo: %.12f |Posicao: %d\n", nome, rg, comparacao, movimentacao, tempo, num_pessoas-1);

            }else if(opcao == 3){

                comparacao = 0;
                movimentacao = 0;


                comparacao ++;
                if (num_pessoas >= num_vagas) {

                printf("Lista cheia.\n");
                    opcao=0;
                    continue;
                }

                int posicao;
                printf("posicao: ");
                scanf("%d", &posicao);
                printf("Nome: ");
                scanf("%s", nome);
                printf("Rg: ");
                scanf("%ld", &rg);

                comparacao++;
                if(posicao < 0 || posicao > num_pessoas){
                    printf("posicao invalida.");
                    continue;
                }

                clock_t inicioTempo = clock();

                for (i=num_pessoas; i>posicao; i--, comparacao ++){
                    movimentacao++;

                    listaPessoas[i] = listaPessoas[i-1];
                }

                strcpy(listaPessoas[posicao].nome, nome);
                listaPessoas[posicao].rg = rg;

                num_pessoas++;

                clock_t fimTempo = clock();
                tempo = (double)(fimTempo-inicioTempo) / CLOCKS_PER_SEC;


                printf("Nome: %s  |Rg: %ld  |C: %d  |M  %d  |Tempo: %.12f |Posicao: %d\n", nome, rg, comparacao, movimentacao, tempo, posicao);

            }else if(opcao == 4){
                comparacao = 0;
                movimentacao = 0;

                comparacao ++;
                if (num_pessoas == 0){
                    printf("Numero insuficiente de pessoas.");
                    opcao=0;
                    continue;
                }

                clock_t inicioTempo = clock();

                strcpy(nome, listaPessoas[0].nome);
                rg = listaPessoas[0].rg;

                for (i=0; i<num_pessoas-1; i++, comparacao ++){
                    movimentacao ++;

                    listaPessoas[i] = listaPessoas[i+1];
                }

                num_pessoas --;

                clock_t fimTempo = clock();

                tempo = (double) (fimTempo - inicioTempo) / CLOCKS_PER_SEC;

                printf("Nome: %s  |Rg: %ld  |C: %d  |M  %d  |Tempo: %.12f |Posicao: %d\n", nome, rg, comparacao, movimentacao, tempo, 0);
            }else if (opcao == 5){
                comparacao = 0;
                movimentacao = 0;

                comparacao ++;
                if (num_pessoas == 0){
                    printf("Numero insuficiente de pessoas.");
                    opcao=0;
                    continue;
                }

                clock_t inicioTempo = clock();

                strcpy(nome, listaPessoas[num_pessoas-1].nome);
                rg = listaPessoas[num_pessoas-1].rg;

                num_pessoas --;

                clock_t fimTempo = clock();

                tempo = (double) (fimTempo - inicioTempo) / CLOCKS_PER_SEC;

                printf("Nome: %s  |Rg: %ld  |C: %d  |M  %d  |Tempo: %.12f |Posicao: %d\n", nome, rg, comparacao, movimentacao, tempo, num_pessoas);

            }else if (opcao == 6){

                comparacao = 0;
                movimentacao = 0;

                int posicao;
                printf("posicao: ");
                scanf("%d", &posicao);

                comparacao++;
                if (posicao < 0 || posicao >= num_pessoas){
                    printf("posicao invalida.");
                    continue;
                }

                clock_t inicioTempo = clock();

                strcpy(nome, listaPessoas[posicao].nome);
                rg = listaPessoas[posicao].rg;

                for (i=posicao; i<num_pessoas-1; i++, comparacao ++){
                    movimentacao++;

                    listaPessoas[i] = listaPessoas[i+1];
                }

                num_pessoas--;

                clock_t fimTempo = clock();

                tempo = (double) (fimTempo - inicioTempo) / CLOCKS_PER_SEC;

                printf("Nome: %s  |Rg: %ld  |C: %d  |M  %d  |Tempo: %.12f |Posicao: %d\n", nome, rg, comparacao, movimentacao, tempo, posicao);

            }else if(opcao == 7){
                int opcao3 = 0;

                printf("\nEscolha uma opcao pelo numero:\n"
                "[ 1 ] - Busca Sequencial\n"
                "[ 2 ] - Busca Binaria\n\n");
                scanf("%d", &opcao3);

                if (opcao3 == 1){

                    int encontrado = false;
    
                    comparacao = 0;
                    movimentacao = 0;
    
                    printf("Insira o RG para a busca: ");
                    scanf("%ld", &rg);
                    clock_t inicioTempo = clock();
    
    
                    for (i=0; i<num_pessoas && encontrado == false; i++, comparacao++){
    
                        comparacao++;
                        if (listaPessoas[i].rg == rg){
                            clock_t fimTempo = clock();
                            tempo = (double) (fimTempo - inicioTempo) / CLOCKS_PER_SEC;
    
                            printf("Nome: %s  |Rg: %ld  |C: %d  |M  %d  |Tempo: %.12f |Posicao: %d\n", listaPessoas[i].nome, listaPessoas[i].rg, comparacao, movimentacao, tempo, i);
    
                            encontrado = true;
                        }
                    }
                    comparacao++;
                    if (encontrado == false){
                        printf("Pessoa nao encontrada na lista.");
                    }


                }else if(opcao3 == 2){

                    if (organizado == 0){
                        printf("Organize a lista primeiro.\n");
                        continue;
                    }
    
                    comparacao = 0;
                    movimentacao = 0;

    
                    printf("Insira o RG para a busca: ");
                    scanf("%ld", &rg);
                    clock_t inicioTempo = clock();

                    int baixo = 0;
                    int alto = num_pessoas - 1;
                    int encontrado = 0;

                    while (baixo <= alto) {
                        int meio = baixo + (alto - baixo) / 2;
                        
                        comparacao++;
                        if (lista_organiazada[meio]->rg == rg) {
                            clock_t fimTempo = clock();
                            tempo = (double)(fimTempo - inicioTempo) / CLOCKS_PER_SEC;

                            printf("Nome: %s | Rg: %ld | C: %d | M: %d | Tempo: %.12f | Posicao: %d\n",
                                   lista_organiazada[meio]->nome,
                                   lista_organiazada[meio]->rg,
                                   comparacao, movimentacao, tempo, meio);
                            encontrado = 1;
                            break;
                        }

                        comparacao+=2;
                        if (lista_organiazada[meio]->rg < rg) {
                            comparacao-=1;
                            baixo = meio + 1;
                        } else {
                            alto = meio - 1;
                        }
                    }

                    comparacao++;
                    if (!encontrado) {
                        printf("Pessoa nao encontrada na lista.\n");
                    }
                }

            }else if(opcao == 8){

                for(i=0; i<num_pessoas; i++, comparacao++){
                    printf("Nome: %s  |Rg: %ld\n", listaPessoas[i].nome, listaPessoas[i].rg);
                }


            }else if(opcao == 9){

                FILE *arq_saida = fopen("lista_saida.txt", "w");

                comparacao++;
                if (arq_saida == NULL){
                    printf("Erro abindo o arquivo.");
                    return 1;
                }

                for (i=0; i<num_pessoas; i++, comparacao++){
                    fprintf(arq_saida, "%s, %ld \n", listaPessoas[i].nome, listaPessoas[i].rg);
                }
                fclose(arq_saida);

            }else if(opcao==10){
                char caminho[200];

                printf("Qual e o caminho do arquivo? ");
                scanf("%s", caminho);

                FILE *arq = fopen(caminho, "r");

                if (arq == NULL){
                    printf("Erro abrindo o arquivo");
                    return 1;
                }

                for (i=num_pessoas; i<num_vagas && fgets(linha, MAX_LIN, arq); i++){

                    if (sscanf (linha, "%[^,], %ld", nome, &rg) == 2 && nome[0] != '\0'){
                        strcpy(listaPessoas[num_pessoas].nome, nome);
                        listaPessoas[num_pessoas].rg = rg;

                        num_pessoas++;
                    }
                }

                fclose(arq);
            }else if(opcao == 12){
                int opcao2;
                printf("\nEscolha o metodo:\n"
                    "[ 1 ] - Selection Sort\n"
                    "[ 2 ] - Insertion Sort\n"
                    "[ 3 ] - Bubble Sort\n"
                    "[ 4 ] - Shell Sort\n"
                    "[ 5 ] - Quick Sort\n"
                    "[ 6 ] - Merge Sort\n\n"
                    "[ 7 ] - Exibir a lista organizada\n"
                    "[ 8 ] - Limpar ordenacao\n"
                    "[ 9 ] - Apagar lista ordenada\n");
                
                scanf("%d", &opcao2);

                if (listaCriada == 0){
                    lista_organiazada = (Pessoa **) malloc (num_pessoas * sizeof(Pessoa *));
                    listaCriada = 1;
                    for(i=0; i<num_pessoas; i++){
                        lista_organiazada[i] = &listaPessoas[i];
                    }
                }
                
                
                if(opcao2 == 8){
                    for(i=0; i<num_pessoas; i++){
                        lista_organiazada[i] = &listaPessoas[i];
                    }
                    organizado = 0;

                }else if(opcao2 == 9){
                    free(lista_organiazada);
                    listaCriada = 0;
                    
                } else if(opcao2 == 7){
                    for (i=0; i<num_pessoas; i++){
                        printf("%d - %15s - %15ld\n", i+1, lista_organiazada[i]->nome, lista_organiazada[i]->rg);
                    }

                }else if (opcao2 == 1){
                    comparacao = 0;
                    movimentacao = 0;
                    Pessoa *aux;
                    clock_t inicioTempo = clock();
    
                    for(i=0; i<num_pessoas-1; i++, comparacao++){
                        int pos_menor = i;
    
                        for(int j=i+1; j<num_pessoas; j++, comparacao++){
    
                            comparacao++;
                            if (lista_organiazada[pos_menor]->rg > lista_organiazada[j]->rg){
                                pos_menor = j;
                            }
                        }
    
                        movimentacao += 3;
                        aux = lista_organiazada[i];
                        lista_organiazada[i] = lista_organiazada[pos_menor];
                        lista_organiazada[pos_menor] = aux;
    
                    }
    
                    
                    clock_t fimTempo = clock();
                    tempo = (double)(fimTempo-inicioTempo) / CLOCKS_PER_SEC;
                    
                    printf("Lista Organizada!, C: %d, M: %d, Tempo: %.12f\n", comparacao, movimentacao, tempo);
                    organizado = 1;

                }else if(opcao2 == 2){
                    comparacao = 0;
                    movimentacao = 0;
                    Pessoa *aux;
                    clock_t inicioTempo = clock();
                    int j;

                    for (i=1; i<num_pessoas; i++, comparacao++){
                        aux = lista_organiazada[i];
                        j = i-1;
                        
                        comparacao+=2;
                        while(j>=0 && lista_organiazada[j]->rg > aux->rg){
                            lista_organiazada[j+1] = lista_organiazada[j];
                            j--;

                            comparacao+=2;
                            movimentacao++;
                        }

                        movimentacao++;
                        lista_organiazada[j+1] = aux;
                    }

                    clock_t fimTempo = clock();
                    tempo = (double)(fimTempo-inicioTempo) / CLOCKS_PER_SEC;
                    
                    printf("Lista Organizada!, C: %d, M: %d, Tempo: %.12f\n", comparacao, movimentacao, tempo);
                    organizado = 1;

                }else if (opcao2 == 3){
                    comparacao = 0;
                    movimentacao = 0;
                    Pessoa *aux;
                    clock_t inicioTempo = clock();

                    for (i=0; i<num_pessoas-1; i++, comparacao++){
                        int trocou = 0;

                        for(int j=0; j<num_pessoas-1-i; j++, comparacao++){

                            comparacao++;
                            if (lista_organiazada[j]->rg > lista_organiazada[j+1]->rg){
                                aux = lista_organiazada[j];
                                lista_organiazada[j] = lista_organiazada[j+1];
                                lista_organiazada[j+1] = aux;
                                movimentacao+=3;

                                trocou =1;
                            }
                    
                        }

                        comparacao++;
                        if (trocou == 0){
                            break;
                        }
                    }

                    clock_t fimTempo = clock();
                    tempo = (double)(fimTempo-inicioTempo) / CLOCKS_PER_SEC;
                    
                    printf("Lista Organizada!, C: %d, M: %d, Tempo: %.12f\n", comparacao, movimentacao, tempo);
                    organizado = 1;
                }else if (opcao2 == 4){
                    int j;
                    comparacao = 0;
                    movimentacao = 0;
                    Pessoa *aux;
                    clock_t inicioTempo = clock();

                    for (int gap = num_pessoas/2; gap > 0; gap /= 2, comparacao++){

                        for (i = gap; i < num_pessoas; i++, comparacao++){
                            aux = lista_organiazada[i];

                            for (j = i; j >= gap && (lista_organiazada[j-gap]->rg > aux->rg) ; j -= gap, comparacao += 2){

                                movimentacao ++;
                                lista_organiazada[j] = lista_organiazada[j-gap];

                            }

                            movimentacao++;
                            lista_organiazada[j] = aux;
                        }
                    }

                    clock_t fimTempo = clock();
                    tempo = (double)(fimTempo-inicioTempo) / CLOCKS_PER_SEC;
                    
                    printf("Lista Organizada!, C: %d, M: %d, Tempo: %.12f\n", comparacao, movimentacao, tempo);
                    organizado = 1;

                }else if (opcao2 == 5){
                    comparacao = 0;
                    movimentacao = 0;

                    clock_t inicioTempo = clock();

                    quikSort(lista_organiazada, 0, num_pessoas-1, &comparacao, &movimentacao);

                    clock_t fimTempo = clock();
                    tempo = (double)(fimTempo-inicioTempo) / CLOCKS_PER_SEC;
                    
                    printf("Lista Organizada!, C: %d, M: %d, Tempo: %.12f\n", comparacao, movimentacao, tempo);
                    organizado = 1;
                }else if (opcao2 == 6){
                    comparacao = 0;
                    movimentacao = 0;

                    clock_t inicioTempo = clock();

                    mergeSort(lista_organiazada, 0, num_pessoas - 1, &comparacao, &movimentacao);

                    clock_t fimTempo = clock();
                    tempo = (double)(fimTempo - inicioTempo) / CLOCKS_PER_SEC;

                    printf("Lista Organizada!, C: %d, M: %d, Tempo: %.12f\n", comparacao, movimentacao, tempo);
                    organizado = 1;
                }
            }
 
            printf("\nEscolha uma opcao pelo numero:\n"
                "[ 1 ] - Inserir no inicio da lista\n"
                "[ 2 ] - Inserir no fim da lista\n"
                "[ 3 ] - Inserir na posicao N da lista\n"
                "[ 4 ] - Retirar um no do inicio da lista\n"
                "[ 5 ] - Retirar um no no fim da lista\n"
                "[ 6 ] - Retirar um no na posição N\n"
                "[ 7 ] - Procurar um no com o campo RG\n"
                "[ 8 ] - Mostrar a lista na tela\n"
                "[ 9 ] - Salvar a lista em um arquivo\n"
                "[ 10 ] - Ler a lista de um arquivo\n"
                "[ 11 ] - Sair do sistema\n\n"
                "[ 12 ] - Ordenar\n\n");
            scanf("%d", &opcao);
            
        }
        
        free(listaPessoas);
        free (lista_organiazada);
        return 0;
    }
