# Gerenciamento de Medicamentos 💊

Projeto acadêmico desenvolvido como parte do curso de **Análise e Desenvolvimento de Sistemas** na **Universidade São Francisco (USF)**. O objetivo é criar um programa simples em linguagem C para gerenciamento de medicamentos de uma farmácia. O programa permite cadastrar, buscar, listar, editar e excluir medicamentos de um sistema.

---

## 🛠️ Funcionalidades

1. **Cadastrar Medicamento**  
   Permite cadastrar medicamentos, solicitando informações como:
   - Nome
   - Lote
   - Descrição
   - Fabricante
   - Validade (formato DD/MM/YYYY)
   - Preço
   - Quantidade

2. **Procurar Medicamento**  
   Busca medicamentos pelo **nome**, **ID**, **fabricante** ou **lote**, retornando os resultados correspondentes.

3. **Listar Medicamentos**  
   Exibe todos os medicamentos cadastrados no sistema.

4. **Editar Medicamento**  
   Permite alterar informações de medicamentos já cadastrados, como:
   - Lote
   - Nome
   - Descrição
   - Fabricante
   - Validade
   - Preço
   - Quantidade

5. **Excluir Medicamento**  
   Remove medicamentos do sistema pelo nome.

---

## 🧩 Estrutura de Dados

### Tipo `Medicamento`

```c
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
```

---

## 📂 Arquivos Utilizados

- **`medicamentos.dat`**  
  Arquivo binário utilizado para armazenar os dados dos medicamentos. O programa lê e grava os dados nesse arquivo para manter a persistência das informações entre execuções.

---

## 🧪 Validações Implementadas

- **Campos numéricos** (lote, preço, quantidade): aceitam apenas números positivos.
- **Data de validade**: verificação do formato `DD/MM/YYYY` e checagem de validade lógica (ex.: fevereiro com 29 dias apenas em anos bissextos).
- **Texto**: validação para garantir que nomes e descrições contenham apenas caracteres alfabéticos e espaços.

---

## 🚀 Como Usar

### Requisitos

- Compilador C (ex.: GCC)
- Sistema operacional com suporte a terminal

### Compilação e Execução

1. Compile o programa:

   ```bash
   gcc -o farmacia farmacia.c
   ```

2. Execute o programa:

   ```bash
   ./farmacia
   ```

---

## 📖 Estrutura do Menu

- **1. Criar Medicamento**: Adicionar um novo medicamento ao sistema.
- **2. Procurar Medicamento**: Localizar medicamentos pelo nome, ID, fabricante ou lote.
- **3. Mostrar Todos os Medicamentos**: Exibir a lista completa de medicamentos cadastrados.
- **4. Editar Medicamento**: Alterar os detalhes de um medicamento existente.
- **5. Deletar Medicamento**: Remover um medicamento cadastrado.
- **0. Sair**: Encerrar o programa.

---

## 👥 Autores

Projeto desenvolvido pelo **Grupo 1**:

- **Igor Vinícius Gonçalves de Souza**
- **Kailainy Santos Souza**
- **Leticia de Fátima Sierra Bugin**
- **Luan Cecon Moreton**
- **Vinícius Leal Pereira**
- **Lucas Abreu Accarini**

---

## 🏫 Contexto Acadêmico

Este programa foi criado como projeto para a disciplina **Análise e Desenvolvimento de Sistemas** no curso da **Universidade São Francisco (USF)**. Ele demonstra o uso de:

- Estruturas (`struct`) para modelar dados
- Manipulação de arquivos para persistência de dados
- Validações básicas de entrada do usuário
- Gerenciamento de memória dinâmica com `malloc` e `free`

---

## 📜 Licença

Este projeto foi desenvolvido para fins acadêmicos e é de uso livre para aprendizado e melhoria.
