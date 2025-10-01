# Guia de Instalação e Configuração

## 🎯 Objetivos deste Guia
Este documento fornece instruções detalhadas para compilar, executar e configurar o Sistema de Vendas Simplificado em diferentes ambientes.

## 📋 Pré-requisitos

### Sistema Operacional
- ✅ Windows (7, 8, 10, 11)
- ✅ Linux (Ubuntu, Debian, CentOS, etc.)
- ✅ macOS (10.12+)
- ✅ Qualquer sistema com navegador web (GDB Online)

### Compilador C
- **GCC** (GNU Compiler Collection) - Recomendado
- **Clang** - Alternativa
- **MSVC** (Visual Studio) - Windows
- **TDM-GCC** - Windows alternativo

## 💻 Opção 1: GDB Online (Mais Fácil)

### Vantagens
- ✅ Não requer instalação
- ✅ Funciona em qualquer navegador
- ✅ Interface amigável
- ✅ Debugger integrado

### Passos
1. Acesse: https://www.onlinegdb.com/
2. Selecione **C** como linguagem
3. Cole o código do arquivo `main.c`
4. Clique em **Run**
5. Interaja com o programa no console

### Captura de Tela
```
┌─────────────────────────────────┐
│ GDB Online - C Compiler         │
├─────────────────────────────────┤
│ [Code Editor]                   │
│ #include <stdio.h>              │
│ ...                            │
├─────────────────────────────────┤
│ [Console Output]                │
│ === SISTEMA DE VENDAS ===       │
│ Bem-vindo ao nosso sistema!     │
└─────────────────────────────────┘
```

## 🐧 Opção 2: Linux/Unix

### Instalação do GCC (Ubuntu/Debian)
```bash
# Atualizar repositórios
sudo apt update

# Instalar build-essential (inclui GCC)
sudo apt install build-essential

# Verificar instalação
gcc --version
```

### Instalação do GCC (CentOS/RHEL)
```bash
# Instalar grupo de desenvolvimento
sudo yum groupinstall "Development Tools"

# Ou no CentOS 8+
sudo dnf groupinstall "Development Tools"

# Verificar instalação
gcc --version
```

### Compilação e Execução
```bash
# Navegar para o diretório do projeto
cd "/caminho/para/Trabalho do Valval"

# Compilar o programa
gcc -o sistema_vendas main.c

# Executar
./sistema_vendas

# Ou compilar e executar em uma linha
gcc main.c && ./a.out
```

### Opções de Compilação Avançadas
```bash
# Com avisos detalhados
gcc -Wall -Wextra -o sistema_vendas main.c

# Com informações de debug
gcc -g -Wall -o sistema_vendas main.c

# Otimizado para produção
gcc -O2 -Wall -o sistema_vendas main.c

# Compatibilidade C99
gcc -std=c99 -Wall -o sistema_vendas main.c
```

## 🍎 Opção 3: macOS

### Instalação do Compilador

#### Método 1: Xcode Command Line Tools
```bash
# Instalar ferramentas de linha de comando
xcode-select --install

# Verificar instalação
gcc --version
```

#### Método 2: Homebrew
```bash
# Instalar Homebrew (se não tiver)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Instalar GCC
brew install gcc

# Verificar instalação
gcc-11 --version  # ou versão instalada
```

### Compilação e Execução
```bash
# Compilar
gcc -o sistema_vendas main.c

# Executar
./sistema_vendas
```

## 🪟 Opção 4: Windows

### Método 1: MinGW-w64

#### Instalação
1. Baixe MinGW-w64: https://www.mingw-w64.org/downloads/
2. Instale seguindo o assistente
3. Adicione ao PATH: `C:\mingw64\bin`

#### Verificação
```cmd
gcc --version
```

#### Compilação
```cmd
# Abrir prompt de comando na pasta do projeto
cd "C:\caminho\para\Trabalho do Valval"

# Compilar
gcc -o sistema_vendas.exe main.c

# Executar
sistema_vendas.exe
```

### Método 2: Visual Studio

#### Instalação
1. Baixe Visual Studio Community (gratuito)
2. Instale com workload "Desktop development with C++"

#### Uso
1. Criar novo projeto "Console App"
2. Substituir conteúdo por `main.c`
3. Compilar com Ctrl+F5

### Método 3: Code::Blocks

#### Instalação
1. Baixe Code::Blocks: http://www.codeblocks.org/
2. Escolha versão com MinGW incluído
3. Instale seguindo assistente

#### Uso
1. File → New → Project → Console Application → C
2. Cole o código do `main.c`
3. Build → Build and run (F9)

## 🛠️ Configurações Opcionais

### Variáveis de Ambiente
```bash
# Linux/macOS (.bashrc)
export CC=gcc
export CFLAGS="-Wall -Wextra -std=c99"

# Windows (System Properties)
CC=gcc
CFLAGS=-Wall -Wextra -std=c99
```

### Makefile (Avançado)
```makefile
# Criar arquivo 'Makefile'
CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g
TARGET=sistema_vendas
SOURCE=main.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: clean
```

#### Uso do Makefile
```bash
# Compilar
make

# Limpar arquivos gerados
make clean
```

## 🐛 Troubleshooting

### Problema: "gcc: command not found"
**Solução**: Instalar compilador conforme seção específica do SO

### Problema: "Permission denied" (Linux/macOS)
```bash
# Dar permissão de execução
chmod +x sistema_vendas
```

### Problema: Caracteres especiais não aparecem
**Causa**: Codificação do terminal
**Solução Windows**:
```cmd
chcp 65001  # UTF-8
```

### Problema: Programa fecha imediatamente
**Causa**: Sistema não pausa no final
**Solução**: Adicionar pausa antes do return
```c
// No final da função main(), antes do return 0;
printf("\nPressione Enter para sair...");
getchar();
```

### Problema: Scanf não funciona corretamente
**Causa**: Buffer de entrada com lixo
**Solução**: Já implementado no código com limpeza de buffer

## 📁 Estrutura de Arquivos Recomendada

```
projeto-vendas/
├── src/
│   └── main.c              # Código-fonte principal
├── docs/
│   ├── README.md           # Documentação principal
│   ├── DOCUMENTACAO_TECNICA.md
│   └── INSTALACAO.md       # Este arquivo
├── build/                  # Arquivos compilados
│   └── sistema_vendas      # Executável
└── tests/                  # Testes (futuro)
    └── test_vendas.c
```

## 🚀 Scripts de Automatização

### Script de Compilação (Linux/macOS)
```bash
#!/bin/bash
# compile.sh
echo "Compilando Sistema de Vendas..."
gcc -Wall -Wextra -std=c99 -o sistema_vendas main.c

if [ $? -eq 0 ]; then
    echo "✅ Compilação bem-sucedida!"
    echo "Execute: ./sistema_vendas"
else
    echo "❌ Erro na compilação!"
    exit 1
fi
```

### Script de Compilação (Windows)
```batch
@echo off
REM compile.bat
echo Compilando Sistema de Vendas...
gcc -Wall -Wextra -std=c99 -o sistema_vendas.exe main.c

if %errorlevel% equ 0 (
    echo ✅ Compilação bem-sucedida!
    echo Execute: sistema_vendas.exe
) else (
    echo ❌ Erro na compilação!
    pause
    exit /b 1
)
```

## 🧪 Verificação da Instalação

### Teste Rápido
```bash
# Executar o programa
./sistema_vendas

# Verificar se aparece:
# === SISTEMA DE VENDAS SIMPLIFICADO ===
# Bem-vindo ao nosso sistema!
```

### Checklist de Funcionalidades
- [ ] Menu de produtos aparece corretamente
- [ ] Consegue adicionar produtos ao carrinho
- [ ] Visualiza carrinho com formatação
- [ ] Aplica desconto para compras > R$ 50
- [ ] Trata entradas inválidas sem crash
- [ ] Finaliza compra com sucesso

## 📞 Suporte

### Problemas Comuns
1. **Compilação**: Verificar instalação do GCC
2. **Execução**: Verificar permissões do arquivo
3. **Interface**: Verificar codificação do terminal
4. **Performance**: Normal em hardware moderno

### Recursos Adicionais
- 📖 [Tutorial C](https://www.learn-c.org/)
- 🔧 [GCC Manual](https://gcc.gnu.org/onlinedocs/)
- 💬 [Stack Overflow - C Tag](https://stackoverflow.com/questions/tagged/c)

---

*Guia criado para facilitar a instalação e uso do Sistema de Vendas Simplificado*