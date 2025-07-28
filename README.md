# Best-Scanf-Usage-in-C
Custom macros that specifically enhance and secure keyboard input reading, offering better alternatives to traditional scanf().

---

## 1. Segue abaixo uma breve introdução sobre alguns conceitos:

### **O que são dados formatados?**
- **Definição:** Organização de informações conforme especificações pré-definidas (geralmente para processamento computacional).
- **Em C:** Funções como `scanf()` foram projetadas para ler entrada formatada (*scan formatted input*).

---

### **Problemas com `scanf()`**
- **Objetivo original:** Ler entrada formatada (ex: arquivos estruturados), **não** entrada do teclado (que é livre).
- **Riscos:**
  - Não valida a entrada — usuário pode digitar qualquer coisa (105+ teclas de liberdade).
  - Pode corromper memória se a entrada não corresponder ao esperado.
  - Retorna um `int` (número de itens lidos) — ignorar esse retorno é um erro comum.
- **Uso prático:**
  - Pode ser útil em casos controlados, mas **não** é adequado para aplicações robustas que exigem validação.

---

### **"Lixo" no teclado?**
- Não existe "lixo" — a entrada é *free form*: o programa deve tratar qualquer input do usuário.
- O teclado permite qualquer combinação de teclas — a responsabilidade de filtrar é do desenvolvedor.

---

### **`fflush(stdin)` é inválido**
- `fflush()` só é definido para streams de **saída** (ex: `stdout`).
- Usar em `stdin` gera *undefined behavior* (UB) — pode funcionar em alguns compiladores, mas é não-portável.

---

### **`setbuf(stdin, NULL)` ou `setbuf(stdin, 0)` não resolvem**
- `setbuf()` não foi projetado para limpar buffers de entrada.
- Buffers de entrada são gerenciados pelo sistema — tentativas de "zerá-los" são ineficazes.
- Necessidade disso geralmente indica mistura inadequada de operações de entrada/saída.

---

## 2. Abaixo se encontram as descrições das macros que melhoram especificamente a leitura da entrada do teclado, oferecendo melhores alternativas à scanf() tradicional:

---

### **`ascanf()` - Alternative scanf**
- **Contexto:** Lê e ignora um caractere residual (geralmente `\n`) após a leitura.
- **Funcionamento:**
  - Usa `%*c` no fim da string de especificadores de formato para ler e descartar o próximo caractere, após a leitura do que se realmente pretendia ler.
- **Limitação:** Só remove um caractere — seu uso é destinado a remover o `\n` restante na stdin após uma leitura com a `scanf()`.

---

### **`bscanf()` - Better scanf**
- **Contexto:** `scanf()` deixa resíduos (como `\n`) no buffer de entrada, podendo causar problemas em leituras subsequentes.
- **Funcionamento:**
  - Adiciona um espaço (`' '`) via `ungetc()` para evitar buffer vazio.
  - Lê e descarta todos os caracteres até encontrar `\n` ou `EOF` (usando `fgetc()`).
- **Limitação:** Propósito similar à `ascanf()`, mas com um funcionamento aprimorado. Não há de fato uma limitação agravante, desconsiderando o fato do uso de `ungetc()` na stdin ser "contraintuitivo e incomum".

---

### **`sdscanf()` - String data scanf**
- **Contexto:** Lê dados formatados diretamente de uma string gerada por `StrDados()`. Esta função captura a entrada do teclado até um caractere delimitador que, diferente da `scanf()` que espera um Enter, pode assumir quaisquer caracteres passados como parâmetro.
- **Funcionamento:**
  - **`StrDados(lista)`**:
    - Lê caracteres do teclado (`LerChar()`) até encontrar um caractere presente em `lista` (delimitadores).
  - **`sdscanf()`**: Encapsula `sscanf()` para extrair dados da string retornada por `StrDados()`.
- **Limitação:** Depende da WinAPI, pois `LerChar()` lê um caractere com `PeekConsoleInput()` (sem a necessidade do Enter) e o retorna. Outra forma de fazer isso seria com `getch()` da `conio.h`, mas esta biblioteca não é portável e não faz parte de padrão nenhum. Além disso, diferente da `ascanf()` e `bscanf`, a `sdscanf()` não consome resíduos, pois este não é seu propósito.
