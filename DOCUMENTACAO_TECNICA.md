# Documentação Técnica - API e Estrutura Interna

## 📋 Índice
- [Visão Geral da Arquitetura](#visão-geral-da-arquitetura)
- [Estruturas de Dados](#estruturas-de-dados)
- [API das Funções](#api-das-funções)
- [Fluxo de Execução](#fluxo-de-execução)
- [Gerenciamento de Memória](#gerenciamento-de-memória)
- [Estados do Sistema](#estados-do-sistema)
- [Algoritmos Utilizados](#algoritmos-utilizados)

## 🏗️ Visão Geral da Arquitetura

### Padrão Arquitetural
O sistema segue o padrão **Programação Estruturada** com as seguintes características:
- Separação clara entre dados e funções
- Modularização através de funções específicas
- Controle de fluxo através de estruturas condicionais e loops
- Validação centralizada de entrada

### Diagrama de Componentes
```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Interface     │    │   Lógica de     │    │   Estruturas    │
│   do Usuário    │◄──►│   Negócio       │◄──►│   de Dados      │
│                 │    │                 │    │                 │
│ • exibirMenu()  │    │ • main()        │    │ • Produto       │
│ • obterOpcao()  │    │ • validações    │    │ • ItemCarrinho  │
│ • pausar()      │    │ • calculos      │    │ • Arrays        │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

## 📊 Estruturas de Dados

### Produto
```c
typedef struct {
    char nome[MAX_NOME];    // 30 bytes
    float preco;            // 4 bytes
    int estoque;            // 4 bytes
} Produto;                  // Total: 38 bytes
```

**Campos:**
- `nome`: String terminada em null para identificação
- `preco`: Valor monetário com precisão de 2 casas decimais
- `estoque`: Quantidade inteira não-negativa

**Invariantes:**
- `preco >= 0.0`
- `estoque >= 0`
- `nome[0] != '\0'` (não pode ser vazio)

### ItemCarrinho
```c
typedef struct {
    char nome[MAX_NOME];    // 30 bytes
    int quantidade;         // 4 bytes
    float preco;            // 4 bytes
    float subtotal;         // 4 bytes
} ItemCarrinho;             // Total: 42 bytes
```

**Campos:**
- `nome`: Cópia do nome do produto (para consistência)
- `quantidade`: Quantidade selecionada pelo usuário
- `preco`: Cópia do preço unitário (snapshot)
- `subtotal`: Valor calculado (quantidade × preço)

**Invariantes:**
- `quantidade > 0`
- `preco >= 0.0`
- `subtotal == quantidade * preco`

## 🔧 API das Funções

### Grupo: Interface do Usuário

#### `void exibirMenu(Produto produtos[])`
**Propósito**: Apresenta o menu de produtos com informações de estoque
**Pré-condições**: 
- `produtos` deve ser um array válido de tamanho `MAX_PRODUTOS`
**Pós-condições**: 
- Menu formatado é exibido no stdout
- Estado do sistema não é alterado

**Complexidade**: O(n) onde n = MAX_PRODUTOS

#### `int obterOpcao()`
**Propósito**: Captura entrada numérica do usuário com validação
**Pré-condições**: stdin disponível
**Pós-condições**: 
- Retorna inteiro válido
- Buffer de entrada limpo
**Tratamento de Erros**: Loop até entrada válida

**Algoritmo**:
```c
1. Solicitar entrada
2. WHILE scanf falha:
   a. Exibir mensagem de erro
   b. Limpar buffer
   c. Solicitar novamente
3. Retornar valor válido
```

#### `int obterQuantidade(int estoqueDisponivel)`
**Propósito**: Captura quantidade com validação de range
**Pré-condições**: `estoqueDisponivel > 0`
**Pós-condições**: Retorna valor no range [1, estoqueDisponivel]
**Validações**:
- Entrada numérica
- Valor >= 1
- Valor <= estoqueDisponivel

### Grupo: Gerenciamento do Carrinho

#### `void adicionarAoCarrinho(ItemCarrinho carrinho[], int* numItens, Produto produto, int quantidade)`
**Propósito**: Adiciona produto ao carrinho ou atualiza quantidade existente
**Pré-condições**:
- `carrinho` é array válido
- `numItens` ponteiro válido
- `*numItens < MAX_CARRINHO`
- `quantidade > 0`

**Pós-condições**:
- Item adicionado ou quantidade atualizada
- `*numItens` incrementado (se novo item)
- Subtotal recalculado

**Algoritmo**:
```c
1. Verificar limite do carrinho
2. FOR cada item existente:
   IF nome == produto.nome:
     a. Atualizar quantidade
     b. Recalcular subtotal
     c. RETURN
3. Adicionar novo item
4. Incrementar numItens
```

**Complexidade**: O(n) onde n = número de itens no carrinho

#### `void exibirCarrinho(ItemCarrinho carrinho[], int numItens)`
**Propósito**: Exibe conteúdo do carrinho em formato tabular
**Pré-condições**: 
- `carrinho` é array válido
- `numItens >= 0`
**Pós-condições**: Tabela formatada exibida

**Formato de Saída**:
```
PRODUTO             QTD   PRECO   SUBTOTAL
----------------------------------------
Refrigerante         2    5.00     10.00
Chocolate            1    7.50      7.50
----------------------------------------
TOTAL:                            R$ 17.50
```

#### `float calcularTotal(ItemCarrinho carrinho[], int numItens)`
**Propósito**: Calcula valor total dos itens
**Pré-condições**: 
- `carrinho` é array válido
- `numItens >= 0`
**Pós-condições**: Retorna soma dos subtotais
**Complexidade**: O(n)

### Grupo: Processamento de Vendas

#### `void finalizarCompra(ItemCarrinho carrinho[], int numItens, float total)`
**Propósito**: Processa finalização com aplicação de desconto
**Pré-condições**:
- `carrinho` válido e não-vazio
- `total >= 0`
**Pós-condições**: 
- Resumo da compra exibido
- Desconto aplicado se elegível
- Valor final calculado

**Lógica de Desconto**:
```c
IF total >= 50.0:
    desconto = total * 0.05  // 5%
    total_final = total - desconto
ELSE:
    total_final = total
```

### Grupo: Utilitários

#### `void limparTela()`
**Propósito**: Simula limpeza de tela
**Implementação**: 3 quebras de linha (`\n\n\n`)

#### `void pausar()`
**Propósito**: Pausa execução aguardando Enter
**Implementação**: 
```c
1. Limpar buffer de entrada
2. Aguardar nova linha
```

## 🔄 Fluxo de Execução

### Máquina de Estados
```
[INICIO] → [MENU] → [ACAO] → [VALIDACAO] → [EXECUCAO] → [CONFIRMACAO] → [MENU]
                       ↓
                   [FINALIZAR] → [FIM]
```

### Loop Principal
```c
1. Inicializar produtos com valores padrão
2. Inicializar carrinho vazio
3. Exibir mensagem de boas-vindas
4. WHILE opcao != OPCAO_SAIR:
   a. Exibir menu
   b. Obter opção do usuário
   c. SWITCH opcao:
      - Produtos (1-4): Adicionar ao carrinho
      - Finalizar (5): Processar venda
      - Ver carrinho (6): Exibir conteúdo
      - Limpar (7): Esvaziar carrinho
   d. Pausar para confirmação
5. Exibir mensagem de despedida
```

## 💾 Gerenciamento de Memória

### Alocação de Memória
```c
// Stack allocation (automática)
Produto produtos[MAX_PRODUTOS];        // 4 × 38 = 152 bytes
ItemCarrinho carrinho[MAX_CARRINHO];   // 20 × 42 = 840 bytes
// Variáveis locais                    // ~50 bytes
// Total aproximado:                   // ~1042 bytes
```

### Características:
- **Tipo**: Alocação estática na stack
- **Vantagens**: Rápida, sem vazamentos, automática
- **Limitações**: Tamanho fixo, limitada pela stack

### Estratégias de Otimização:
- Arrays de tamanho fixo para previsibilidade
- Strings com tamanho máximo definido
- Reutilização de variáveis locais

## 📈 Estados do Sistema

### Estado do Produto
```c
typedef enum {
    PRODUTO_DISPONIVEL,     // estoque > 0
    PRODUTO_ESGOTADO       // estoque == 0
} EstadoProduto;
```

### Estado do Carrinho
```c
typedef enum {
    CARRINHO_VAZIO,        // numItens == 0
    CARRINHO_PARCIAL,      // 0 < numItens < MAX_CARRINHO
    CARRINHO_CHEIO         // numItens == MAX_CARRINHO
} EstadoCarrinho;
```

### Transições de Estado

#### Produto: Disponível → Esgotado
```c
// Quando: estoque atual - quantidade solicitada == 0
produtos[i].estoque -= quantidade;
if (produtos[i].estoque == 0) {
    // Estado: PRODUTO_ESGOTADO
}
```

#### Carrinho: Vazio → Parcial → Cheio
```c
// Adição de item
if (numItens == 0) {
    // Estado: CARRINHO_VAZIO → CARRINHO_PARCIAL
} else if (numItens == MAX_CARRINHO - 1) {
    // Estado: CARRINHO_PARCIAL → CARRINHO_CHEIO
}
```

## 🧮 Algoritmos Utilizados

### Busca Linear no Carrinho
```c
// Complexidade: O(n)
for (int i = 0; i < *numItens; i++) {
    if (strcmp(carrinho[i].nome, produto.nome) == 0) {
        // Produto encontrado
        return;
    }
}
```

### Cálculo de Total
```c
// Complexidade: O(n)
float total = 0.0;
for (int i = 0; i < numItens; i++) {
    total += carrinho[i].subtotal;
}
```

### Restauração de Estoque
```c
// Complexidade: O(n × m) onde n = itens carrinho, m = produtos
for (int i = 0; i < numItensCarrinho; i++) {
    for (int j = 0; j < MAX_PRODUTOS; j++) {
        if (strcmp(carrinho[i].nome, produtos[j].nome) == 0) {
            produtos[j].estoque += carrinho[i].quantidade;
            break;  // Otimização: sair do loop interno
        }
    }
}
```

## 🔍 Análise de Complexidade

### Complexidade Temporal
| Operação | Melhor Caso | Caso Médio | Pior Caso |
|----------|-------------|------------|-----------|
| Adicionar ao carrinho | O(1) | O(n) | O(n) |
| Exibir carrinho | O(n) | O(n) | O(n) |
| Calcular total | O(n) | O(n) | O(n) |
| Limpar carrinho | O(n×m) | O(n×m) | O(n×m) |

### Complexidade Espacial
- **Espaço**: O(1) - constante
- **Justificativa**: Arrays de tamanho fixo

## 🛡️ Invariantes do Sistema

### Invariantes Globais
1. `0 <= numItensCarrinho <= MAX_CARRINHO`
2. `produtos[i].estoque >= 0` para todo i
3. `carrinho[i].subtotal == carrinho[i].quantidade * carrinho[i].preco`

### Invariantes de Loop
```c
// Loop principal
while (opcaoEscolhida != OPCAO_SAIR) {
    // Invariante: sistema em estado consistente
    // Pré-condição: menu válido exibido
    // Pós-condição: ação executada ou erro tratado
}
```

## 📋 Checklist de Qualidade

### ✅ Implementado
- [x] Validação de entrada robusta
- [x] Tratamento de erros
- [x] Modularização clara
- [x] Documentação de código
- [x] Casos de teste básicos
- [x] Interface consistente

### 🔄 Melhorias Futuras
- [ ] Testes unitários automatizados
- [ ] Logging de operações
- [ ] Configuração externa
- [ ] Persistência de dados
- [ ] Internacionalização

---

*Esta documentação técnica complementa o relatório principal e serve como referência para desenvolvedores.*