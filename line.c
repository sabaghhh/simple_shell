#include "shell.h"
/**
 * _Buff - assigns value for getline
 * @buffPtr: a buffer
 * @s_assign: The string to assign.
 * @buffSize: buffer size
 * @strSize: string size
 */

void _Buff(char **buffPtr, char *s_assign, size_t *buffSize, size_t strSize)
{

if (*buffSize < strSize)
{
if (strSize > 120)
*buffSize = strSize;
else
*buffSize = 120;
*buffPtr = s_assign;
}

else if (*buffPtr == NULL)
{
if (strSize > 120)
*buffSize = strSize;
else
*buffSize = 120;
*buffPtr = s_assign;
}

else
{
_str_cpy(*buffPtr, s_assign);
free(s_assign);
}

}


/**
 * allocateM - allocates memory.
 * @existing: the existing buffer.
 * @prevSize: the previous size of the buffer.
 * @newSize: the new size of the buffer.
 * Return: buffer or NULL.
 */

void *allocateM(void *existing, unsigned int prevSize, unsigned int newSize)
{
unsigned int i;
char *bufferCopy, *buf;
void *newBuffer;

if (!existing)
{
newBuffer = malloc(newSize);
if (newBuffer == NULL)
return (NULL);
return (newBuffer);
}

if (newSize == prevSize)
return (existing);

if (newSize == 0 && existing)
{
free(existing);
return (NULL);
}

bufferCopy = existing;
newBuffer = malloc(sizeof(bufferCopy) * newSize);

if (!newBuffer)
{
free(existing);
return (NULL);
}

buf = newBuffer;
i = 0;
while (i < prevSize && i < newSize)
{
buf[i] = *bufferCopy++;
i++;
}
free(existing);
return (newBuffer);
}


/**
 * _get_line - get the input line
 * @outputString: pointer to buffere to where input is stored
 * @outputSize: size of the buffer
 * @inputFile: the input
 * Return: size of line
 */
ssize_t _get_line(char **outputString, size_t *outputSize, FILE *inputFile)
{
ssize_t reValue;
static ssize_t callCount;
char *lineBuffer, currentChar = 'x';
int readResult = 1;

if (callCount == 0)
fflush(inputFile);
else
return (-1);

callCount = 0;
lineBuffer = malloc(sizeof(char) * 120 + 1);
if (lineBuffer == NULL)
return (-1);
while (currentChar != '\n')
{
readResult = read(STDIN_FILENO, &currentChar, 1);
if (readResult == -1 || (readResult == 0 && callCount == 0))
{
free(lineBuffer);
return (-1);
}
if (readResult == 0 && callCount != 0)
{
callCount++;
break;
}
if (callCount >= 120)
lineBuffer = allocateM(lineBuffer, callCount, callCount + 1);
*(lineBuffer + callCount) = currentChar;
callCount++;
}
lineBuffer[callCount] = '\0';
_Buff(outputString, lineBuffer, outputSize, callCount);
reValue = callCount;
if (readResult != 0)
callCount = 0;
return (reValue);
}

/**
 * _read_line - reads line.
 *
 * Return: the read line.
 */
char *_read_line(void)
{
char *line = NULL;

size_t i = 0;


if (_get_line(&line, &i, stdin) == -1)
{
if (feof(stdin))
{
free(line);
exit(EXIT_SUCCESS);
}
else
{
free(line);
perror("Error");
exit(EXIT_FAILURE);
}
}
return (line);
}



/**
 * _split_line - parse the input line.
 * @line: line of commands.
 * Return: Nothing.
 */

char **_split_line(char *line)
{
char **tokens, *token;

int i = 0;
int buff = 64;
const char *delim = " \t\r\n\a\"";

tokens = malloc(buff * sizeof(char));
if (!tokens)
{
perror("Error: Memory allocation failed\n");
exit(EXIT_FAILURE);
}
token = strtok(line, delim);
while (token)
{
if (token[0] == '#')
break;
tokens[i] = token;
if (i >= buff)
{
buff += buff;
tokens = realloc(tokens, (buff)*(sizeof(char *)));
if (tokens)
{
perror("Error: Memory reallocation failed");
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, delim);
i++;
}
tokens[i] = NULL;
return (tokens);
}
