//Grupo 1
//Nomes:
//Igor Vinícius Gonçalves de Souza
//Kailainy Santos Souza
//Leticia de Fátima Sierra Bugin
//Luan Cecon Moreton
//Vinícius Leal Pereira
//Lucas Abreu Accarini

//

#include <stdio.h>
#include <stdlib.h> //Precisa para usar atoi
#include <string.h>
#include <ctype.h>  //Precisa para usar isalpha(), isdigit() e isspace()

//Definir um limite de medicamentos
#define maximo 50

//Definir medicamento
typedef struct {
    int id;
    int lote;
    char nome[20];
    char desc[100];
    char fabr[10];
    char validade[10];
    float preco;
    int quantidade;
} Medicamento;

//Função para salvar os medicamentos em um arquivo
void salvarMeds(Medicamento medicamentos[], int count) {
    FILE *file = fopen("medicamentos.dat", "wb"); //Abre o arquivo 
    if (file != NULL) {
        fwrite(&count, sizeof(int), 1, file); //Escreve o número de medicamentos
        fwrite(medicamentos, sizeof(Medicamento), (size_t)count, file); //Salva os medicamentos
        fclose(file);
        printf("Medicamento salvos com sucesso!\n");
    } else {
        printf("Erro ao salvar os medicamentos!\n");
    }
}

//Carregar os medicamentos do arquivo
int carregarMeds(Medicamento medicamentos[]) {
    int count = 0;
    FILE *file = fopen("medicamentos.dat", "rb"); //Abrir o arquivo
    if (file != NULL) {
        fread(&count, sizeof(int), 1, file); //Ler o número de medicamentos
        fread(medicamentos, sizeof(Medicamento), (size_t)count, file); //Ler os medicamentos
        fclose(file);
        printf("Medicamentos carregados com sucesso!\n");
    } else {
        printf("Nenhum medicamento salvo encontrado.\n");
    }
    return count; //Retorna o número de medicamentos
}

// Função para verificar se o input contém apenas letras e espaços
int verificarTexto(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isalpha(input[i]) && !isspace(input[i])) {
            return 0;  // Se encontrar algo que não seja letra ou espaço, retorna 0 (inválido)
        }
    }
    return 1;  // Se o input for válido, retorna 1
}

int isNumeric(const char *str) {
    // Verifica se cada caractere da string é um dígito
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0; // Se algum caractere não for um número, retorna falso
        }
    }
    return 1; // Se todos os caracteres forem dígitos, retorna verdadeiro
}

// Função para validar a data no formato DD/MM/YYYY
int validarData(char *data) {
    if (strlen(data) != 10) return 0; // Verifica se a data tem 10 caracteres

    // Verifica o formato
    if (data[2] != '/' || data[5] != '/') return 0;

    // Extrai dia, mês e ano
    int dia = atoi(&data[0]);
    int mes = atoi(&data[3]);
    int ano = atoi(&data[6]);

    // Verifica se o dia, mês e ano estão em intervalos válidos
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || ano < 1900) return 0;

    // Verifica meses com 30 dias
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return 0;

    // Verifica fevereiro e ano bissexto
    if (mes == 2) {
        if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
            if (dia > 29) return 0; // Ano bissexto
        } else {
            if (dia > 28) return 0; // Ano comum
        }
    }

    return 1; // Data válida
}

//1 Cadastrar
void cadastrarMed(Medicamento medicamentos[], int *count) {
    if (*count < maximo) {
        Medicamento m;
        m.id = *count + 1;

        printf("\nNome do medicamento: ");
        scanf(" %[^\n]", m.nome);

        // Validação do lote
        char loteStr[10];
        do {
            printf("\nLote (número): ");
            scanf("%s", loteStr);
            if (!isNumeric(loteStr)) {
                printf("O lote deve conter apenas números. Tente novamente.\n");
            }
        } while (!isNumeric(loteStr));
        m.lote = atoi(loteStr);  // Converte para inteiro

        printf("\nDescrição do medicamento: ");
        scanf(" %[^\n]", m.desc);

        printf("\nFabricante: ");
        scanf(" %[^\n]", m.fabr);

        // Validação da validade
        do {
            printf("\nValidade (DD/MM/YYYY): ");
            scanf("%10s", m.validade);
            if (!validarData(m.validade)) {
                printf("Data inválida. Tente no formato DD/MM/YYYY.\n");
            }
        } while (!validarData(m.validade));

        // Validação do preço
        do {
            printf("\nPreço: ");
            if (scanf("%f", &m.preco) != 1 || m.preco <= 0) {
                printf("O preço deve ser um número positivo. Tente novamente.\n");
                while (getchar() != '\n'); // Limpa o buffer de entrada
            }
        } while (m.preco <= 0);

        // Validação da quantidade
        char quantidadeStr[10];
        do {
            printf("\nQuantidade (número): ");
            scanf("%s", quantidadeStr);
            if (!isNumeric(quantidadeStr)) {
                printf("A quantidade deve conter apenas números. Tente novamente.\n");
            }
        } while (!isNumeric(quantidadeStr));
        m.quantidade = atoi(quantidadeStr);  // Converte para inteiro

        medicamentos[*count] = m; // Adiciona à lista
        (*count)++;

        salvarMeds(medicamentos, *count); // Salva os medicamentos
    } else {
        printf("Número máximo de medicamentos atingido.");
    }
}


// 2 Procurar
void procurarMed(Medicamento medicamentos[], int count) {

    char medBusca[20]; // Array para armazenar o nome do medicamento a ser procurado
    int medEncontrado = 0;  // Verifica se o medicamento foi encontrado
    Medicamento* encontrados = (Medicamento*) malloc(count * sizeof(Medicamento));  // Lista temporária de medicamentos encontrados
    int encontradosCount = 0;  // Contador de medicamentos encontrados


    //criar uma lista temporaria para receber o medicamento encontrado e depois jogar ele no print

    printf("\nDigite o nome, ID, fabricante ou lote do medicamento que deseja procurar: ");
    scanf(" %[^\n]", medBusca);

    for (int i = 0; i < count; i++) {
        if (
            strcmp(medicamentos[i].nome, medBusca) == 0 || 
            medicamentos[i].id == atoi(medBusca) ||
            strcmp(medicamentos[i].fabr, medBusca) == 0 || 
            medicamentos[i].lote == atoi(medBusca)
        ){
            //Adiciona a uma lista temporária
            encontrados[encontradosCount] = medicamentos[i];
            encontradosCount++;
            medEncontrado = 1; // Marca que pelo menos um medicamento foi encontrado
        }
    }
    // Se pelo menos um medicamento foi encontrado, imprime todos eles
    if (medEncontrado) {
        for (int i = 0; i < encontradosCount; i++) {
            printf("\nID: %d\n", encontrados[i].id);
            printf("\nLote: %d\n", encontrados[i].lote);
            printf("\nNome: %s\n", encontrados[i].nome);
            printf("\nDescrição: %s\n", encontrados[i].desc);
            printf("\nFabricante: %s\n", encontrados[i].fabr);
            printf("\nValidade: %s\n", encontrados[i].validade);
            printf("\nPreço: %.2f\n", encontrados[i].preco);
            printf("\nQuantidade: %d\n", encontrados[i].quantidade);
            printf("\n---------------------------------------------\n\n");
        }
    } else {
        printf("\nNenhum medicamento encontrado!\n");
    }

    free(encontrados);  // Libera a memória alocada para a lista temporária
}

//3 Mostrar
void mostrarTodos(Medicamento medicamentos[], int count) {
    // Verifica se existe medicamento cadastrado
    if (count == 0) {
        printf("\nNenhum medicamento cadastrado.\n");
        return;
    }
    printf("\nMedicamentos\n");
    for (int i = 0; i < count; i++)
    {
        printf("\n\n");
        printf("ID: %d\n", medicamentos[i].id);
        printf("Lote: %d\n", medicamentos[i].lote);
        printf("Nome: %s\n", medicamentos[i].nome);
        printf("Descrição: %s\n", medicamentos[i].desc);
        printf("Fabricante: %s\n", medicamentos[i].fabr);
        printf("Validade: %s\n", medicamentos[i].validade);
        printf("Preço: %.2f\n", medicamentos[i].preco);
        printf("Quantidade: %d\n", medicamentos[i].quantidade);
    }

}

//4 Editar
void editarMeds(Medicamento medicamentos[], int count){
    int id;
    printf("\n------------------------------------------------\n");
    printf("\nDigite o ID do medicamento que deseja editar: ");
    scanf("%d", &id);

    int sel2;

    for (int i = 0; i < count; i++) {
        if (medicamentos[i].id == id) {
            printf("\n------------------------------------------------\n");
            printf("\nMedicamento encontrado:\n");
            printf("ID: %d\n", medicamentos[i].id);
            printf("Lote: %d\n", medicamentos[i].lote);
            printf("Nome: %s\n", medicamentos[i].nome);
            printf("Descrição: %s\n", medicamentos[i].desc);
            printf("Fabricante: %s\n", medicamentos[i].fabr);
            printf("Validade: %s\n", medicamentos[i].validade);
            printf("Preço: %.2f\n", medicamentos[i].preco);
            printf("Quantidade: %d\n", medicamentos[i].quantidade);
        do
        {
            printf("\n------------------\n");
            printf("\nEdição\n");
            printf("\n------------------\n");

            printf("\n1. Editar lote\n");
            printf("\n2. Editar nome\n");
            printf("\n3. Editar descrição\n");
            printf("\n4. Editar fabricação\n");
            printf("\n5. Editar validade\n");
            printf("\n6. Editar preço\n");
            printf("\n7. Editar quantidade\n");

            printf("\n0. Salvar e sair\n\n");

            printf("Seleção: ");
            scanf("%d", &sel2);

            switch (sel2)
            {
                case 1: {  // Alterar o lote do medicamento
                    int lote;
                    printf("Novo Lote (apenas números): ");
                    while (scanf("%d", &lote) != 1 || lote < 0) {
                        printf("O lote deve conter apenas números positivos. Tente novamente: ");
                        while (getchar() != '\n'); // Limpar buffer
                    }
                    medicamentos[i].lote = lote;
                    break;
                }
                case 2:  // Alterar o nome do medicamento
                    printf("Novo Nome: ");
                    scanf(" %[^\n]", medicamentos[i].nome);
                    break;

                case 3:  // Alterar a descrição do medicamento
                    printf("Nova Descrição: ");
                    scanf(" %[^\n]", medicamentos[i].desc);
                    break;

                case 4:  // Alterar o fabricante do medicamento
                    printf("Novo Fabricante: ");
                    scanf(" %[^\n]", medicamentos[i].fabr);
                    break;

                case 5: {  // Alterar a validade do medicamento
                    do {
                        printf("Nova Validade (DD/MM/YYYY): ");
                        scanf("%10s", medicamentos[i].validade);
                        if (!validarData(medicamentos[i].validade)) {
                            printf("Data inválida. Tente no formato DD/MM/YYYY.\n");
                        }
                    } while (!validarData(medicamentos[i].validade));
                    break;
                }

                case 6: {  // Alterar o preço do medicamento
                    float preco;
                    printf("Novo Preço: ");
                    while (scanf("%f", &preco) != 1 || preco <= 0) {
                        printf("O preço deve ser um número positivo. Tente novamente: ");
                        while (getchar() != '\n'); // Limpar buffer
                    }
                    medicamentos[i].preco = preco;
                    break;
                }

                case 7: {  // Alterar a quantidade do medicamento
                    int quantidade;
                    printf("Nova Quantidade (apenas números): ");
                    while (scanf("%d", &quantidade) != 1 || quantidade < 0) {
                        printf("A quantidade deve conter apenas números positivos. Tente novamente: ");
                        while (getchar() != '\n'); // Limpar buffer
                    }
                    medicamentos[i].quantidade = quantidade;
                    break;
                }
                case 0:
                    printf("Saindo da edição...\n");
                    break;

                default:
                    printf("Opção inválida. Tente novamente.\n");
            }
        } while (sel2 != 0);
        
        salvarMeds(medicamentos, count); // Salva os medicamentos após a edição
            printf("Medicamento editado com sucesso!\n");
            return;
        }
    }
    printf("Medicamento não encontrado!\n");
    return;
}

// 5 Deletar
void deletarMed(Medicamento medicamentos[], int *count) {
    char nome[20]; // Array para armazenar o nome do medicamento a ser removido
    int relacao = -1; // Índice começando com -1 para indicar que o medicamento não foi encontrado
    printf("\nDigite o nome do medicamento que deseja deletar: ");
    scanf(" %[^\n]", nome);

    // Busca o medicamento
    for (int i = 0; i < *count; i++) {
        if (strcmp(medicamentos[i].nome, nome) == 0) {
            relacao = i;
            break;
        }
    }
    
    // Verifica se o medicamento foi encontrado
    if (relacao == -1) {
        printf("\nMedicamento não encontrado.\n");
        return;
    }
    
    // Remove o medicamento do Array
    for (int i = relacao; i < *count - 1; i++) {
        medicamentos[i] = medicamentos[i + 1];
    }

    (*count)--;
    salvarMeds(medicamentos, *count); // Salva o array atulizado
    printf("\nMedicamento deletado com sucesso!\n");
    return;
}

int main() {
    Medicamento medicamentos[maximo]; // Array de medicamentos
    int count = carregarMeds(medicamentos);
    int selecao;

    do
    {
        printf("\n------------------\n");
        printf("\nFarmácia\n");
        printf("\n------------------\n");

        printf("\n1. Criar Medicamento\n");
        printf("\n2. Procurar Medicamento\n");
        printf("\n3. Mostrar todos os Medicamentos\n");
        printf("\n4. Editar Medicamento\n");
        printf("\n5. Deletar Medicamento\n");
        printf("\n------------------\n");

        printf("\n0. Sair\n\n");

        printf("Seleção: ");
        scanf("%d", &selecao);

        switch (selecao)
        {
        case 1:
            cadastrarMed(medicamentos, &count);
            break;

        case 2:
            procurarMed(medicamentos, count);
            break;

        case 3:
            mostrarTodos(medicamentos, count);
            break;

        case 4:
            editarMeds(medicamentos, count);
            break;

        case 5:
            deletarMed(medicamentos, &count);
            break;

        case 0:
            break;

        default:
            printf("Opção inválida");
        }
    } while (selecao != 0);
    return 0;
}
