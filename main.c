// ascanf() lê e ignora um caractere restante (\n) na stream de entrada

#define ascanf(formato, ...) scanf(formato"%*c", __VA_ARGS__)

// bscanf() coloca um ' ' na stream de entrada, então o buffer não poderá ficar vazio

#define bscanf(...)                                                 \
do {                                                                \
    scanf(__VA_ARGS__);                                             \
    ungetc(' ', stdin);                                             \
    for(int ch = 0; ((ch = fgetc(stdin)) != '\n' && ch != EOF););   \
} while(0)

// sdscanf() usa a função StrDados() para obter a string fonte da qual resgata os dados

#define sdscanf(lista, ...) sscanf(StrDados(lista), __VA_ARGS__)

#include <stdio.h>
#include <windows.h>

char LerChar(void); // Lê um char com PeekConsoleInput() e o retorna
const char* StrDados(const char* lista); // Obtém um string fonte da qual sdscanf() resgata os dados

int main()
{
    int numero;
    char caractere;

    printf("Numero: ");
    ascanf("%d", &numero);
    printf("Caractere: ");
    scanf("%c", &caractere);

    printf("Numero: ");
    bscanf("%d", &numero);
    printf("Caractere: ");
    scanf("%c", &caractere);

    printf("Numero: ");
    sdscanf(" \n", "%d", &numero); // Encerra o input ao teclar um ' ' ou um '\n'
    printf("\nCaractere: ");
    scanf("%*c%c", &caractere);

    return 0;
}

char LerChar(void)
{
	INPUT_RECORD record;
	HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
	int total = 0;
	// Tecla
	char c = 0;

	do {
		FlushConsoleInputBuffer(console);
		WaitForSingleObject(console, INFINITE);

		/* Se PeekConsoleInput() for bem-sucedida,
	    o valor retornado será diferente de zero */
		if(!PeekConsoleInput(console, &record, 1, (LPDWORD)&total))
            return 1;
		if(total > 0)
            if(record.EventType == KEY_EVENT && record.Event.KeyEvent.bKeyDown)
            {
                /* Se o evento de entrada for um evento
                do teclado, retorna o caractere ASCII */
                c = record.Event.KeyEvent.uChar.AsciiChar;
                FlushConsoleInputBuffer(console);
                // Se o caractere for um '\r', retorna um '\n'
                if(c == '\r')
                    c = '\n';
                return c;
            }
	} while(1);
}

const char* StrDados(const char* lista)
{
    // Se lista apontar pra NULL, retorna NULL
    if(lista == NULL) return NULL;

    int aloc = 101;
	char* str = (char*)malloc(aloc);

    int i = 0;
    int ch;

	while((ch = LerChar()) != EOF)
    {
        /* Se ch corresponder com algum caractere apontado por
        lista, o controle é transferido para fora do loop */
        if(ch != '\0' && strchr(lista, ch) != NULL) break;

        if(i == (aloc - 1))
        {
            // Realoca memória se necessário
            aloc += 100;
            str = (char*)realloc(str, aloc);
        }


        if(ch == '\b' && i > 0)
        {
            // Backspace
            printf("\b \b");
            str[--i] = '\0';
        }
        else if(ch != '\0')
        {
            putchar(ch);
            str[i++] = ch;
        }
    }

    str[i] = '\0';

    return str;
}
