/*
SISTEMA DE VENDAS SIMPLIFICADO
Sistema de ponto de venda com carrinho, estoque e validação
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constantes do sistema
#define MAX_PRODUTOS 4
#define OPCAO_SAIR 5
#define MAX_NOME 30
#define MAX_CARRINHO 20

// Estrutura do produto
typedef struct {
    char nome[MAX_NOME];
    float preco;
    int estoque;
} Produto;

// Estrutura do item no carrinho
typedef struct {
    char nome[MAX_NOME];
    int quantidade;
    float preco;
    float subtotal;
} ItemCarrinho;

// Protótipos das funções
void exibirMenu(Produto produtos[]);
int obterOpcao();
int obterQuantidade(int estoqueDisponivel);
void adicionarAoCarrinho(ItemCarrinho carrinho[], int* numItens, Produto produto, int quantidade);
void exibirCarrinho(ItemCarrinho carrinho[], int numItens);
float calcularTotal(ItemCarrinho carrinho[], int numItens);
void finalizarCompra(ItemCarrinho carrinho[], int numItens, float total);
void limparTela();
void pausar();

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
    int quantidadeDesejada = 0;
    
    printf("\n=== SISTEMA DE VENDAS SIMPLIFICADO ===\n");
    printf("Bem-vindo ao nosso sistema!\n");
    
    // Loop principal
    while (opcaoEscolhida != OPCAO_SAIR) {
        limparTela();
        exibirMenu(produtos);
        
        printf("6 - Ver carrinho\n");
        printf("7 - Limpar carrinho\n");
        printf("------\n");
        
        opcaoEscolhida = obterOpcao();
        
        // Seleção de produtos (1-4)
        if (opcaoEscolhida >= 1 && opcaoEscolhida <= 4) {
            if (produtos[opcaoEscolhida - 1].estoque > 0) {
                quantidadeDesejada = obterQuantidade(produtos[opcaoEscolhida - 1].estoque);
                
                if (quantidadeDesejada > 0) {
                    adicionarAoCarrinho(carrinho, &numItensCarrinho, produtos[opcaoEscolhida - 1], quantidadeDesejada);
                    produtos[opcaoEscolhida - 1].estoque -= quantidadeDesejada;
                    
                    printf("\n*** Item adicionado ao carrinho! ***\n");
                    printf("Produto: %s\n", produtos[opcaoEscolhida - 1].nome);
                    printf("Quantidade: %d\n", quantidadeDesejada);
                    printf("Subtotal: R$ %.2f\n", quantidadeDesejada * produtos[opcaoEscolhida - 1].preco);
                }
            } else {
                printf("\n*** PRODUTO FORA DE ESTOQUE! ***\n");
            }
            
        // Finalizar compra (5)
        } else if (opcaoEscolhida == 5) {
            if (numItensCarrinho > 0) {
                float total = calcularTotal(carrinho, numItensCarrinho);
                finalizarCompra(carrinho, numItensCarrinho, total);
                
                numItensCarrinho = 0; // Limpar carrinho
                
                printf("\nDeseja fazer uma nova compra? (1-Sim, 0-Nao): ");
                int continuar;
                if (scanf("%d", &continuar) == 1 && continuar == 1) {
                    opcaoEscolhida = 0;
                } else {
                    opcaoEscolhida = OPCAO_SAIR;
                }
            } else {
                printf("\n*** Carrinho vazio! Adicione itens primeiro. ***\n");
            }
            
        // Ver carrinho (6)
        } else if (opcaoEscolhida == 6) {
            exibirCarrinho(carrinho, numItensCarrinho);
            
        // Limpar carrinho (7)
        } else if (opcaoEscolhida == 7) {
            if (numItensCarrinho > 0) {
                printf("\nTem certeza que deseja limpar o carrinho? (1-Sim, 0-Nao): ");
                int confirma;
                if (scanf("%d", &confirma) == 1 && confirma == 1) {
                    // Restaurar estoque dos itens removidos
                    for (int i = 0; i < numItensCarrinho; i++) {
                        for (int j = 0; j < MAX_PRODUTOS; j++) {
                            if (strcmp(carrinho[i].nome, produtos[j].nome) == 0) {
                                produtos[j].estoque += carrinho[i].quantidade;
                                break;
                            }
                        }
                    }
                    numItensCarrinho = 0;
                    printf("\n*** Carrinho limpo! ***\n");
                }
            } else {
                printf("\n*** Carrinho ja esta vazio! ***\n");
            }
            
        // Opção inválida
        } else if (opcaoEscolhida != OPCAO_SAIR) {
            printf("\n*** OPCAO INVALIDA! Tente novamente. ***\n");
        }
        
        if (opcaoEscolhida != OPCAO_SAIR) {
            pausar();
        }
    }
    
    printf("\n=== OBRIGADO POR USAR NOSSO SISTEMA! ===\n");
    return 0;
}

// ===================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ===================================================================

void exibirMenu(Produto produtos[])
{
    printf("\n===== MENU DE PRODUTOS =====\n");
    
    for (int i = 0; i < MAX_PRODUTOS; i++) {
        char status[15];
        
        if (produtos[i].estoque > 0) {
            sprintf(status, "(%d em estoque)", produtos[i].estoque);
        } else {
            strcpy(status, "(SEM ESTOQUE)");
        }
        
        printf("%d - %s: R$ %.2f %s\n", 
               i + 1, produtos[i].nome, produtos[i].preco, status);
    }
    
    printf("5 - Finalizar compra\n");
}

int obterOpcao()
{
    int opcao;
    printf("\nDigite sua opcao: ");
    
    while (scanf("%d", &opcao) != 1) {
        printf("ERRO: Digite apenas numeros!\n");
        printf("Digite sua opcao: ");
        while (getchar() != '\n');
    }
    
    return opcao;
}

int obterQuantidade(int estoqueDisponivel)
{
    int quantidade;
    
    printf("\nEstoque disponivel: %d unidades\n", estoqueDisponivel);
    
    do {
        printf("Digite a quantidade desejada (1-%d): ", estoqueDisponivel);
        
        if (scanf("%d", &quantidade) != 1) {
            printf("ERRO: Digite apenas numeros!\n");
            while (getchar() != '\n');
            continue;
        }
        
        if (quantidade < 1) {
            printf("ERRO: Quantidade deve ser pelo menos 1!\n");
        } else if (quantidade > estoqueDisponivel) {
            printf("ERRO: Quantidade maior que estoque disponivel!\n");
        } else {
            return quantidade;
        }
    } while (1);
}

void adicionarAoCarrinho(ItemCarrinho carrinho[], int* numItens, Produto produto, int quantidade)
{
    if (*numItens >= MAX_CARRINHO) {
        printf("ERRO: Carrinho cheio!\n");
        return;
    }
    
    // Verificar se produto já existe no carrinho
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(carrinho[i].nome, produto.nome) == 0) {
            carrinho[i].quantidade += quantidade;
            carrinho[i].subtotal = carrinho[i].quantidade * carrinho[i].preco;
            return;
        }
    }
    
    // Adicionar novo item
    strcpy(carrinho[*numItens].nome, produto.nome);
    carrinho[*numItens].quantidade = quantidade;
    carrinho[*numItens].preco = produto.preco;
    carrinho[*numItens].subtotal = quantidade * produto.preco;
    
    (*numItens)++;
}

void exibirCarrinho(ItemCarrinho carrinho[], int numItens)
{
    if (numItens == 0) {
        printf("\n*** CARRINHO VAZIO ***\n");
        return;
    }
    
    printf("\n======= SEU CARRINHO =======\n");
    printf("PRODUTO             QTD   PRECO   SUBTOTAL\n");
    printf("----------------------------------------\n");
    
    float total = 0.0;
    for (int i = 0; i < numItens; i++) {
        printf("%-18s  %3d  %6.2f  %8.2f\n",
               carrinho[i].nome, carrinho[i].quantidade,
               carrinho[i].preco, carrinho[i].subtotal);
        
        total += carrinho[i].subtotal;
    }
    
    printf("----------------------------------------\n");
    printf("TOTAL:                        R$ %.2f\n", total);
    printf("===============================\n");
}

float calcularTotal(ItemCarrinho carrinho[], int numItens)
{
    float total = 0.0;
    
    for (int i = 0; i < numItens; i++) {
        total += carrinho[i].subtotal;
    }
    
    return total;
}

void finalizarCompra(ItemCarrinho carrinho[], int numItens, float total)
{
    printf("\n===== RESUMO DA COMPRA =====\n");
    exibirCarrinho(carrinho, numItens);
    
    // Aplicar desconto para compras acima de R$ 50
    float desconto = 0.0;
    if (total >= 50.0) {
        desconto = total * 0.05;
        printf("\n*** PARABENS! Desconto de 5%% aplicado! ***\n");
        printf("Desconto: R$ %.2f\n", desconto);
        total = total - desconto;
    }
    
    printf("\n*** VALOR FINAL: R$ %.2f ***\n", total);
    printf("*** COMPRA FINALIZADA COM SUCESSO! ***\n");
    printf("*** OBRIGADO PELA PREFERENCIA! ***\n");
}

void limparTela()
{
    printf("\n\n\n");
}

void pausar()
{
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
    getchar();
}

/*
TODO: Melhorias futuras:
- Salvar carrinho em arquivo
- Histórico de compras
- Mais produtos no catálogo
- Interface gráfica
- Sistema de usuários/login
*/