# Calculadora RPN (Notação Polonesa Reversa)

Uma calculadora simples que usa notação polonesa reversa, onde os operadores vêm depois dos operandos.

## Pré-requisitos

### Linux/Mac

- GCC ou Clang
- Make

### Windows

Você tem duas opções:

1. **Usando MinGW**:

   - Instale [MinGW](https://www.mingw-w64.org/downloads/)
   - Adicione MinGW ao PATH do Windows
   - Use `mingw32-make` em vez de `make`

2. **Usando WSL (Windows Subsystem for Linux)**:
   - Instale o WSL pelo Microsoft Store (recomendamos Ubuntu)
   - No terminal do WSL, instale as ferramentas:
     ```bash
     sudo apt update
     sudo apt install build-essential
     ```

## Como Funciona

Na notação polonesa reversa, você primeiro digita os números e depois o operador. Por exemplo:

- `4 5 +` significa "4 mais 5"
- `10 5 -` significa "10 menos 5"
- `3 4 *` significa "3 vezes 4"
- `20 2 /` significa "20 dividido por 2"

## Como Compilar

### Linux/Mac

```bash
make build
```

### Windows com MinGW

```cmd
mingw32-make build
```

O executável será criado como `bin\pol.exe`


O executável será criado em `bin/pol` (Linux/Mac/WSL) ou `bin/pol.exe` (Windows/MinGW)

## Como Usar

Execute o programa passando os números e operadores como argumentos:

### Linux/Mac/WSL

```bash
# Exemplos básicos:
./bin/pol 4 5 +     # 4 + 5 = 9
./bin/pol 10 5 -    # 10 - 5 = 5
./bin/pol 3 4 *     # 3 * 4 = 12
./bin/pol 20 2 /    # 20 / 2 = 10

# Expressões mais complexas:
./bin/pol 10 5 3 + -  # 10 - (5 + 3) = 2
```

### Windows (MinGW)

```cmd
# Exemplos básicos:
bin\pol.exe 4 5 +     # 4 + 5 = 9
bin\pol.exe 10 5 -    # 10 - 5 = 5
bin\pol.exe 3 4 *     # 3 * 4 = 12
bin\pol.exe 20 2 /    # 20 / 2 = 10

# Expressões mais complexas:
bin\pol.exe 10 5 3 + -  # 10 - (5 + 3) = 2
```

## Operadores Suportados

- `+` : Adição
- `-` : Subtração
- `*` : Multiplicação
- `/` : Divisão

