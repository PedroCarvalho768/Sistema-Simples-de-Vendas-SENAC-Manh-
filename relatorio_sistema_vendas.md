# Sistema de Vendas Simplificado: Implementação de um Ponto de Venda com Controle de Estoque

**Autor:** Estudante de Programação  
**Data:** Outubro de 2025  
**Disciplina:** Programação em C  
**Ambiente de Desenvolvimento:** GDB Online  

---

## Resumo

Este trabalho apresenta o desenvolvimento de um sistema de vendas simplificado implementado na linguagem C, utilizando o ambiente de desenvolvimento GDB Online. O sistema foi projetado para gerenciar um catálogo de produtos, controlar estoque em tempo real, implementar um carrinho de compras funcional e processar vendas com desconto automático. A aplicação demonstra conceitos fundamentais de programação estruturada, incluindo uso de estruturas de dados, validação robusta de entrada, modularização através de funções e tratamento de erros.

**Palavras-chave:** Sistema de Vendas, Programação C, Controle de Estoque, Carrinho de Compras, GDB Online

---

## 1. Introdução

O desenvolvimento de sistemas de ponto de venda (PDV) é uma aplicação prática importante no ensino de programação, pois envolve diversos conceitos fundamentais da ciência da computação. Este projeto implementa um sistema simplificado que simula as operações básicas de uma loja, incluindo gerenciamento de produtos, controle de estoque, carrinho de compras e processamento de vendas.

O objetivo principal deste trabalho é demonstrar a aplicação prática de conceitos de programação estruturada em C, desenvolvendo uma solução completa e funcional que pode ser executada no ambiente GDB Online, proporcionando uma experiência de desenvolvimento acessível e colaborativa.

### 1.1 Objetivos

- **Objetivo Geral:** Desenvolver um sistema de vendas funcional em linguagem C
- **Objetivos Específicos:**
  - Implementar gerenciamento de produtos com controle de estoque
  - Criar um sistema de carrinho de compras interativo
  - Desenvolver validação robusta de entrada de dados
  - Aplicar desconto automático baseado no valor da compra
  - Demonstrar boas práticas de programação estruturada

---

## 2. Metodologia

### 2.1 Ambiente de Desenvolvimento

O desenvolvimento foi realizado utilizando o **GDB Online**, um ambiente de desenvolvimento integrado (IDE) baseado em web que oferece:

- Compilador C/C++ online
- Debugger integrado
- Interface amigável para desenvolvimento
- Execução em tempo real
- Compartilhamento fácil de código

### 2.2 Abordagem de Desenvolvimento

O projeto seguiu a metodologia de programação estruturada, dividindo o problema em módulos menores e implementando cada funcionalidade de forma incremental:

1. **Análise de Requisitos:** Definição das funcionalidades do sistema
2. **Design da Arquitetura:** Estruturação do código em módulos
3. **Implementação:** Desenvolvimento das funções e estruturas
4. **Teste e Validação:** Verificação do funcionamento correto
5. **Documentação:** Elaboração da documentação técnica

---

## 3. Arquitetura do Sistema

### 3.1 Estruturas de Dados

O sistema utiliza duas estruturas principais para organizar os dados:

#### 3.1.1 Estrutura Produto
```c
typedef struct {
    char nome[MAX_NOME];
    float preco;
    int estoque;
} Produto;
```

Esta estrutura armazena as informações essenciais de cada produto:
- **nome:** Identificação do produto (até 30 caracteres)
- **preco:** Valor unitário do produto
- **estoque:** Quantidade disponível para venda

#### 3.1.2 Estrutura ItemCarrinho
```c
typedef struct {
    char nome[MAX_NOME];
    int quantidade;
    float preco;
    float subtotal;
} ItemCarrinho;
```

Esta estrutura representa um item no carrinho de compras:
- **nome:** Nome do produto selecionado
- **quantidade:** Quantidade escolhida pelo cliente
- **preco:** Preço unitário (cópia do produto)
- **subtotal:** Valor total do item (quantidade × preço)

### 3.2 Constantes do Sistema

```c
#define MAX_PRODUTOS 4      // Número máximo de produtos no catálogo
#define OPCAO_SAIR 5        // Código para finalizar o programa
#define MAX_NOME 30         // Tamanho máximo para nomes
#define MAX_CARRINHO 20     // Capacidade máxima do carrinho
```

---

## 4. Funcionalidades Implementadas

### 4.1 Catálogo de Produtos

O sistema oferece um catálogo fixo com 4 produtos:

| ID | Produto      | Preço   | Estoque Inicial |
|----|--------------|---------|-----------------|
| 1  | Refrigerante | R$ 5,00 | 20 unidades     |
| 2  | Chocolate    | R$ 7,50 | 15 unidades     |
| 3  | Biscoito     | R$ 4,00 | 25 unidades     |
| 4  | Sanduíche    | R$ 12,00| 10 unidades     |

### 4.2 Menu Principal

O sistema apresenta um menu interativo com as seguintes opções:

1. **Seleção de Produtos (1-4):** Permite adicionar produtos ao carrinho
2. **Finalizar Compra (5):** Processa a venda e aplica descontos
3. **Ver Carrinho (6):** Exibe o conteúdo atual do carrinho
4. **Limpar Carrinho (7):** Remove todos os itens e restaura o estoque

### 4.3 Gerenciamento de Carrinho

O carrinho de compras oferece as seguintes funcionalidades:

- **Adição de Produtos:** Adiciona itens com validação de estoque
- **Combinação Automática:** Produtos duplicados são automaticamente combinados
- **Visualização Detalhada:** Exibe produtos, quantidades, preços e subtotais
- **Cálculo Automático:** Calcula o total da compra em tempo real

### 4.4 Sistema de Desconto

O sistema implementa um desconto promocional automático:
- **Condição:** Compras acima de R$ 50,00
- **Desconto:** 5% sobre o valor total
- **Aplicação:** Automática durante a finalização

### 4.5 Controle de Estoque

- **Atualização em Tempo Real:** O estoque é reduzido imediatamente após adicionar ao carrinho
- **Validação de Disponibilidade:** Impede vendas de produtos sem estoque
- **Restauração Inteligente:** Produtos retornam ao estoque quando o carrinho é limpo
- **Indicadores Visuais:** Mostra status do estoque no menu

---

## 5. Validação e Tratamento de Erros

### 5.1 Validação de Entrada

O sistema implementa validação robusta para todas as entradas do usuário:

```c
int obterOpcao()
{
    int opcao;
    printf("\nDigite sua opcao: ");
    
    while (scanf("%d", &opcao) != 1) {
        printf("ERRO: Digite apenas numeros!\n");
        printf("Digite sua opcao: ");
        while (getchar() != '\n');  // Limpar buffer
    }
    
    return opcao;
}
```

### 5.2 Tratamento de Erros

- **Entrada Não Numérica:** Detecta e trata caracteres inválidos
- **Valores Fora do Range:** Valida limites de quantidade e opções
- **Estoque Insuficiente:** Impede vendas acima do disponível
- **Carrinho Cheio:** Controla limite máximo de itens
- **Buffer Overflow:** Limpa buffer de entrada para evitar problemas

---

## 6. Resultados e Discussão

### 6.1 Funcionalidades Testadas

Todos os recursos do sistema foram testados extensivamente:

✅ **Adição de Produtos:** Funcionamento correto com validação de estoque  
✅ **Carrinho de Compras:** Adição, visualização e limpeza funcionais  
✅ **Controle de Estoque:** Atualização em tempo real e restauração  
✅ **Sistema de Desconto:** Aplicação automática para compras elegíveis  
✅ **Validação de Entrada:** Tratamento robusto de entradas inválidas  
✅ **Interface de Usuario:** Menu intuitivo e mensagens claras  

### 6.2 Desempenho

O sistema demonstrou desempenho satisfatório no ambiente GDB Online:
- **Tempo de Resposta:** Instantâneo para todas as operações
- **Uso de Memória:** Eficiente com estruturas estáticas
- **Estabilidade:** Nenhum crash ou comportamento inesperado observado

### 6.3 Usabilidade

A interface de usuário foi projetada para ser intuitiva:
- **Menu Claro:** Opções bem organizadas e numeradas
- **Feedback Visual:** Confirmações e status em tempo real
- **Mensagens de Erro:** Claras e direcionais
- **Fluxo Lógico:** Sequência natural de operações

---

## 7. Código-Fonte Principal

### 7.1 Função Principal
```c
int main()
{
    // Inicialização dos produtos
    Produto produtos[MAX_PRODUTOS] = {
        {"Refrigerante", 5.00, 20},
        {"Chocolate", 7.50, 15},
        {"Biscoito", 4.00, 25},
        {"Sanduiche", 12.00, 10}
    };
    
    // Variáveis de controle
    ItemCarrinho carrinho[MAX_CARRINHO];
    int numItensCarrinho = 0;
    int opcaoEscolhida = 0;
    
    // Loop principal do sistema
    while (opcaoEscolhida != OPCAO_SAIR) {
        exibirMenu(produtos);
        opcaoEscolhida = obterOpcao();
        
        // Processamento das opções...
    }
    
    return 0;
}
```

### 7.2 Funções Auxiliares Principais

- **`exibirMenu()`:** Apresenta o catálogo com status de estoque
- **`obterOpcao()`:** Captura entrada do usuário com validação
- **`adicionarAoCarrinho()`:** Gerencia a adição de produtos
- **`exibirCarrinho()`:** Mostra conteúdo do carrinho formatado
- **`finalizarCompra()`:** Processa venda com desconto automático

---

## 8. Conclusões

O desenvolvimento do Sistema de Vendas Simplificado alcançou todos os objetivos propostos, demonstrando a aplicação prática de conceitos fundamentais de programação em C. O uso do ambiente GDB Online facilitou o desenvolvimento e permitiu testes em tempo real.

### 8.1 Contribuições

Este projeto contribui para o aprendizado de:
- **Programação Estruturada:** Organização clara do código em funções
- **Estruturas de Dados:** Uso eficiente de structs e arrays
- **Validação de Entrada:** Técnicas para entrada robusta de dados
- **Gerenciamento de Estado:** Controle de estoque e carrinho em memória
- **Interface de Usuário:** Design de menus intuitivos em console

### 8.2 Limitações Identificadas

- **Persistência:** Dados são perdidos ao encerrar o programa
- **Catálogo Fixo:** Não permite adição dinâmica de produtos
- **Usuário Único:** Não suporta múltiplos usuários simultâneos
- **Interface Textual:** Limitada a interface de console

### 8.3 Trabalhos Futuros

Melhorias possíveis para versões futuras:

- **Persistência em Arquivo:** Salvar dados em arquivos texto
- **Catálogo Dinâmico:** Permitir adição/remoção de produtos
- **Histórico de Vendas:** Implementar relatórios de vendas
- **Interface Gráfica:** Migrar para interface visual
- **Sistema de Usuários:** Implementar login e permissões
- **Banco de Dados:** Integração com SQLite ou similar

---

## 9. Referências

1. **Kernighan, B. W.; Ritchie, D. M.** *The C Programming Language*. 2ª ed. Prentice Hall, 1988.

2. **Deitel, H. M.; Deitel, P. J.** *C: Como Programar*. 6ª ed. Pearson, 2011.

3. **GDB Online.** *Online Compiler and Debugger for C/C++*. Disponível em: https://www.onlinegdb.com/

4. **Schildt, H.** *C Completo e Total*. 3ª ed. Makron Books, 1997.

5. **Ziviani, N.** *Projeto de Algoritmos com Implementações em Pascal e C*. 3ª ed. Cengage Learning, 2010.

---

## Anexos

### Anexo A - Código Completo

O código-fonte completo do sistema está disponível no arquivo `main.c`, contendo todas as 311 linhas de implementação com comentários explicativos.

### Anexo B - Capturas de Tela

*[Aqui seriam incluídas capturas de tela do sistema funcionando no GDB Online]*

### Anexo C - Casos de Teste

| Teste | Entrada | Resultado Esperado | Status |
|-------|---------|-------------------|--------|
| T001  | Opção 1, Qty 2 | Adicionar 2 Refrigerantes | ✅ Passou |
| T002  | Opção 6 | Exibir carrinho | ✅ Passou |
| T003  | Compra > R$ 50 | Aplicar desconto 5% | ✅ Passou |
| T004  | Entrada inválida | Solicitar nova entrada | ✅ Passou |
| T005  | Quantidade > estoque | Mostrar erro | ✅ Passou |

---

*Documento gerado em Outubro de 2025*  
*Ambiente: GDB Online*  
*Linguagem: C (C99)*
