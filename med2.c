#include <stdio.h>
#include <string.h>

// Definir um limite de medicamentos
#define maximo 50

// Definir medicamento
typedef struct {
    int id;
    int lote; // falta
    char nome[50];
    char desc[50];
    char fabr[20];     // fabricante - falta
    char validade[10]; // falta
    float preco;
    int quantidade;
} Medicamento;

// Função para salvar os medicamentos em um arquivo
void salvarMeds(Medicamento medicamentos[], int count) {
    FILE *file = fopen("medicamentos.dat", "wb"); // Abre o arquivo
    if (file != NULL) {
        fwrite(&count, sizeof(int), 1, file); // Escreve o número de medicamentos
        fwrite(medicamentos, sizeof(Medicamento), count, file); // Salva os medicamentos
        fclose(file);
        printf("\nMedicamentos salvos com sucesso!\n");
    } else {
        printf("\nErro ao salvar os medicamentos!\n");
    }
}

// Carregar os medicamentos do arquivo
int carregarMeds(Medicamento medicamentos[]) {
    int count = 0;
    FILE *file = fopen("medicamentos.dat", "rb"); // Abrir o arquivo
    if (file != NULL) {
        fread(&count, sizeof(int), 1, file); // Ler o número de medicamentos
        fread(medicamentos, sizeof(Medicamento), count, file); // Ler os medicamentos
        fclose(file);
        printf("\nMedicamentos carregados com sucesso!\n");
    } else {
        printf("\nNenhum medicamento salvo encontrado.\n");
    }
    return count; // Retorna o número de medicamentos
}

// 1 Cadastrar
void cadastrarMed(Medicamento medicamentos[], int *count) {
    // Verificar limite de medicamentos
    if (*count < maximo) {
        Medicamento m;
        m.id = *count + 1;

        printf("\nNome do medicamento: ");
        scanf(" %[^\n]", m.nome); // Permite espaços no nome

        printf("\nDescrição do medicamento: ");
        scanf(" %[^\n]", m.desc); // Permite espaços no texto

        printf("\nPreço: ");
        scanf("%f", &m.preco);

        printf("\nQuantidade: ");
        scanf("%d", &m.quantidade);

        medicamentos[*count] = m; // Adiciona a lista
        (*count)++;

        salvarMeds(medicamentos, *count); // Salva os medicamentos
    } else {
        printf("Número máximo de medicamentos atingido.\n");
    }
}

// 2 Procurar
void procurarMed(Medicamento medicamentos[], int count) {
    char medBusca[50]; // Array para armazenar o nome do medicamento a ser procurado
    int medEncontrado = 0;  // Verifica se o medicamento foi encontrado

    printf("\nDigite o nome do medicamento que deseja procurar: \n");
    scanf(" %[^\n]", medBusca);

    for (int i = 0; i < count; i++) {
        if (strcmp(medicamentos[i].nome, medBusca) == 0) {
            printf("\nMedicamento encontrado!\n");
            printf("\nID: %d\n", medicamentos[i].id);
            printf("\nNome: %s\n", medicamentos[i].nome);
            printf("\nDescrição: %s\n", medicamentos[i].desc);
            printf("\nPreço: %.2f\n", medicamentos[i].preco);
            printf("\nQuantidade: %d\n", medicamentos[i].quantidade);
            
            medEncontrado = 1; // Marca que o medicamento foi encontrado
            break;
        }
    }
    if (!medEncontrado) {
        printf("\nMedicamento não encontrado!\n");
    }
}

// 3 Mostrar
void mostrarTodos(Medicamento medicamentos[], int count) {
    
    // Verifica se existe medicamento cadastrado
    if (count == 0) {
        printf("\nNenhum medicamento cadastrado.\n");
        return;
    }
    printf("\nMedicamentos:\n");
    for (int i = 0; i < count; i++) {
        printf("\n\n");
        printf("ID: %d\n", medicamentos[i].id);
        printf("Nome: %s\n", medicamentos[i].nome);
        printf("Descrição: %s\n", medicamentos[i].desc);
        printf("Preço: %.2f\n", medicamentos[i].preco);
        printf("Quantidade: %d\n", medicamentos[i].quantidade);
    }
}

// 4 Editar
void editarMeds() {
    int sel2;
    do {
        printf("\n------------------\n");
        printf("\nEdição\n");
        printf("\n------------------\n");

        printf("\n1. Editar nome\n");
        printf("\n2. Editar valor\n");
        printf("\n3. Editar descrição\n");
        printf("\n4. Editar quantidade\n");

        printf("\n0. Sair\n\n");

        printf("Seleção: ");
        scanf("%d", &sel2);

        switch (sel2) {
        case 1:
            printf("\nto do1\n");
            break;

        case 2:
            printf("\nto do2\n");
            break;

        case 3:
            printf("\nto do3\n");
            break;

        case 4:
            printf("\nto do4\n");
            break;

        case 0:
            break;

        default:
            printf("Opção inválida");
        }
    } while (sel2 != 0);
    return;
}
 
// 5 Deletar
void deletarMed(Medicamento medicamentos[], int *count) {
    char nome[50]; // Array para armazenar o nome do medicamento a ser removido
    int relacao = -1; // Índice começando com -1 para indicar que o medicamento não foi encontrado
    printf("\nDigite o nome do medicamento que deseja deletar: \n");
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

    do {
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

        switch (selecao) {
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
            editarMeds();
            break;

        case 5:
            deletarMed(medicamentos, &count);
            break;

        case 0:
            break;

        default:
            printf("Opção inválida\n");
        }
    } while (selecao != 0);

    return 0;
}