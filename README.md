# Sistema de Vendas Simplificado

![C](https://img.shields.io/badge/language-C-blue.svg)
![License](https://img.shields.io/badge/license-Educational-green.svg)
![Platform](https://img.shields.io/badge/platform-GDB%20Online-orange.svg)

## 📋 Visão Geral

Sistema de ponto de venda (PDV) simplificado desenvolvido em linguagem C para fins educacionais. O sistema implementa funcionalidades essenciais de uma loja virtual, incluindo catálogo de produtos, carrinho de compras, controle de estoque e processamento de vendas com desconto automático.

## ✨ Funcionalidades

- ✅ **Catálogo de Produtos**: 4 produtos pré-definidos com preços e estoque
- ✅ **Carrinho de Compras**: Adição, visualização e remoção de itens
- ✅ **Controle de Estoque**: Atualização em tempo real
- ✅ **Sistema de Desconto**: 5% automático para compras > R$ 50
- ✅ **Validação Robusta**: Tratamento de entradas inválidas
- ✅ **Interface Intuitiva**: Menu interativo e mensagens claras

## 🚀 Como Executar

### Pré-requisitos
- Compilador C (GCC recomendado)
- Terminal/Console
- Ou usar [GDB Online](https://www.onlinegdb.com/)

### Compilação e Execução

```bash
# Compilar o programa
gcc -o sistema_vendas main.c

# Executar o programa
./sistema_vendas
```

### No GDB Online
1. Acesse https://www.onlinegdb.com/
2. Cole o código do arquivo `main.c`
3. Clique em "Run"

## 📖 Como Usar

### Menu Principal
```
===== MENU DE PRODUTOS =====
1 - Refrigerante: R$ 5.00 (20 em estoque)
2 - Chocolate: R$ 7.50 (15 em estoque)
3 - Biscoito: R$ 4.00 (25 em estoque)
4 - Sanduiche: R$ 12.00 (10 em estoque)
5 - Finalizar compra
6 - Ver carrinho
7 - Limpar carrinho
```

### Fluxo de Uso
1. **Adicionar Produtos**: Digite o número do produto (1-4)
2. **Escolher Quantidade**: Informe a quantidade desejada
3. **Ver Carrinho**: Opção 6 para visualizar itens
4. **Finalizar Compra**: Opção 5 para processar a venda
5. **Limpar Carrinho**: Opção 7 para remover todos os itens

## 🏗️ Arquitetura do Código

### Estruturas de Dados

```c
// Produto no catálogo
typedef struct {
    char nome[MAX_NOME];    // Nome do produto
    float preco;            // Preço unitário
    int estoque;            // Quantidade em estoque
} Produto;

// Item no carrinho de compras
typedef struct {
    char nome[MAX_NOME];    // Nome do produto
    int quantidade;         // Quantidade selecionada
    float preco;            // Preço unitário
    float subtotal;         // Valor total do item
} ItemCarrinho;
```

### Constantes do Sistema

| Constante | Valor | Descrição |
|-----------|-------|-----------|
| `MAX_PRODUTOS` | 4 | Número máximo de produtos no catálogo |
| `MAX_CARRINHO` | 20 | Capacidade máxima do carrinho |
| `MAX_NOME` | 30 | Tamanho máximo para nomes |
| `OPCAO_SAIR` | 5 | Código para finalizar programa |

## 📚 Documentação das Funções

### Funções Principais

#### `int main()`
Função principal que controla o fluxo do programa.
- **Responsabilidades**: Inicialização, loop principal, controle de menu
- **Retorno**: `0` em caso de sucesso

#### `void exibirMenu(Produto produtos[])`
Exibe o menu de produtos com preços e status de estoque.
- **Parâmetros**: `produtos[]` - Array de produtos
- **Saída**: Menu formatado no console

#### `int obterOpcao()`
Captura e valida a opção escolhida pelo usuário.
- **Retorno**: Número inteiro válido da opção
- **Validação**: Apenas números inteiros

#### `int obterQuantidade(int estoqueDisponivel)`
Solicita e valida a quantidade desejada pelo usuário.
- **Parâmetros**: `estoqueDisponivel` - Estoque atual do produto
- **Retorno**: Quantidade válida (1 até estoque disponível)
- **Validação**: Range de 1 até estoque disponível

### Funções do Carrinho

#### `void adicionarAoCarrinho(ItemCarrinho carrinho[], int* numItens, Produto produto, int quantidade)`
Adiciona um produto ao carrinho ou atualiza quantidade existente.
- **Parâmetros**:
  - `carrinho[]` - Array do carrinho
  - `numItens` - Ponteiro para número de itens
  - `produto` - Produto a ser adicionado
  - `quantidade` - Quantidade desejada
- **Comportamento**: Combina produtos duplicados automaticamente

#### `void exibirCarrinho(ItemCarrinho carrinho[], int numItens)`
Exibe o conteúdo do carrinho formatado em tabela.
- **Parâmetros**: 
  - `carrinho[]` - Array do carrinho
  - `numItens` - Número de itens no carrinho
- **Saída**: Tabela com produtos, quantidades, preços e total

#### `float calcularTotal(ItemCarrinho carrinho[], int numItens)`
Calcula o valor total dos itens no carrinho.
- **Parâmetros**:
  - `carrinho[]` - Array do carrinho
  - `numItens` - Número de itens
- **Retorno**: Valor total da compra

### Funções de Compra

#### `void finalizarCompra(ItemCarrinho carrinho[], int numItens, float total)`
Processa a finalização da compra com desconto automático.
- **Parâmetros**:
  - `carrinho[]` - Array do carrinho
  - `numItens` - Número de itens
  - `total` - Valor total da compra
- **Desconto**: 5% para compras ≥ R$ 50,00

### Funções Utilitárias

#### `void limparTela()`
Simula limpeza de tela com quebras de linha.

#### `void pausar()`
Pausa a execução aguardando input do usuário.

## 🧪 Casos de Teste

### Cenários de Teste Validados

| ID | Cenário | Entrada | Resultado Esperado | Status |
|----|---------|---------|-------------------|--------|
| T001 | Adicionar produto válido | Opção 1, Qty 2 | 2 Refrigerantes no carrinho | ✅ |
| T002 | Visualizar carrinho | Opção 6 | Exibir conteúdo do carrinho | ✅ |
| T003 | Aplicar desconto | Compra > R$ 50 | Desconto de 5% aplicado | ✅ |
| T004 | Entrada inválida | Letra no menu | Solicitar nova entrada | ✅ |
| T005 | Estoque insuficiente | Qty > estoque | Mostrar erro de estoque | ✅ |
| T006 | Carrinho vazio | Finalizar sem itens | Mensagem de carrinho vazio | ✅ |
| T007 | Limpar carrinho | Confirmar limpeza | Restaurar estoque | ✅ |

## 🔧 Tratamento de Erros

### Validações Implementadas

- **Entrada Não Numérica**: Detecta caracteres inválidos em campos numéricos
- **Valores Fora do Range**: Valida limites de quantidade e opções de menu
- **Estoque Insuficiente**: Impede vendas acima do disponível
- **Carrinho Cheio**: Controla limite máximo de itens (20 itens)
- **Buffer Overflow**: Limpa buffer de entrada para evitar problemas

### Exemplo de Validação
```c
while (scanf("%d", &opcao) != 1) {
    printf("ERRO: Digite apenas numeros!\n");
    printf("Digite sua opcao: ");
    while (getchar() != '\n');  // Limpar buffer
}
```

## 📁 Estrutura do Projeto

```
root/
├── main.c                          # Código-fonte principal
└── README.md                       # Esta documentação
```

## 🛠️ Tecnologias Utilizadas

- **Linguagem**: C (C99)
- **Compilador**: GCC
- **IDE**: GDB Online
- **Bibliotecas**: stdio.h, string.h, stdlib.h

## 📊 Métricas do Código

- **Linhas de Código**: 311
- **Funções**: 9 funções
- **Estruturas**: 2 structs
- **Constantes**: 4 defines
- **Complexidade**: Baixa-Média
Este é um projeto educacional. Sugestões de melhorias são bem-vindas:

1. Fork o projeto
2. Crie uma branch para sua feature
3. Commit suas mudanças
4. Push para a branch
5. Abra um Pull Request

## 📄 Licença

Este projeto é desenvolvido para fins educacionais e está disponível sob licença educacional.

## 📞 Contato

**Autores**: Pedro Henrique Carvalho, Clarissa Pinheiro do Nascimento, Israel Ferreira Dias, Gabriel Gama Baroni, lelê*
**Disciplina**: Estruturas de Dados em C  
**Data**: Outubro de 2025
