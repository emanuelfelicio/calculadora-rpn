#include <stdio.h>
#include <string.h>
#define STACK_SIZE 1024
double stack[STACK_SIZE];
int stackpointer = 0;

enum Erro
{
    YES,
    NO,
};

// permitir numeros grandes: 120
// permmitir decimais 4.5
/*tratar operador ou palavras desconhecidas junto a um argumento 120+.3 340+ 10f  ; a ideia é se o primeiro caractere argv[i][0]
for um operador faço o operação caso seja um numero inválido retorna que erro de numero inválido e encerro operação.
*/

int main(int argc, char **argv)
{
    double my_atof(const char *digit);

    if (argc > 1 && strcmp(argv[1], "expr") == 0)
    {

        for (int i = 2; i < argc; i++)
        {
            // tratar corretamente o operador, para tal deve ter apenas um argumento (sterlenght == 1) e ser + - / *
            if (argv[i])
            {
            }
        }
    }
    else
    {
    }
}

// void getline()
// {
// }
/* aqui para um endereço de memória que é um valor geralmente em hexadecimal #0x7ffe ; por ser uma passagem de valor apenas uma
    copia do endereço é passado , dessa maneira ao sair da função o valor continuará apontando para o mesmo endereço
*/
/* void strreverse(char *digit)
{
    char *leftptr = digit;

    while (*digit)
    {
        digit++;
    }
    digit--;

    while (leftptr < digit)
    {
        char temp;
        temp = *leftptr;
        *leftptr = *digit;
        *digit = temp;

        leftptr++;
        digit--;
    }
} */

int my_isdigit(const char *digit)
{
    int value = *digit - '0';
    if (value >= 0 && value <= 9)
    {
        return 1;
    }

    return 0;
}

double my_atof(const char *digit)
{
    double result = 0.0;
    double fraction = 0.0;
    int sign = 1;

    if (*digit == '-')
    {
        digit++;
        sign = -1;
    }
    else if (*digit == '+')
    {
        digit++;
        sign = 1;
    }

    while (my_isdigit(digit) && *digit != '.')
    {
        result = result * 10.0 + (*digit - '0');
        digit++;
    }

    if (*digit++ == '.')
    {
        double divisor = 10.0;
        while (my_isdigit(digit))
        {
            fraction += (*digit - '0') / divisor;
            divisor *= 10.0;
            digit++;
        }
    }
    if (*digit != '\0')
    {
        printf("ERROR :NOT A NUMBER");
        return 0;
    }

    result += fraction;
    result *= sign;
    return result;
}

void push(int value)
{
    if (stackpointer < STACK_SIZE)
    {
        stack[stackpointer++] = value;
    }
}

double pop()
{
    if (stackpointer > 0)
    {
        return stack[--stackpointer];
    }

    printf("error: stack vazia");
    return -1;
}