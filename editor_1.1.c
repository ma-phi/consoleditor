#include<termios.h>
#include<unistd.h>

/* Global variable to save states of the raw struct */
struct termios orig_termios;

/* TCSAFLUSH waits for pending output to be written to the terminal */
void disable_raw_mode()
{
    tcsetattr(STDIN_FILENO ,TCSAFLUSH, &orig_termios);
}

void enable_raw_mode()
{
    /* structure to hold states as a buffer */
    struct termios raw;

    /* to write in raw : then setattr writes the changes to terminal */
    tcgetattr(STDIN_FILENO, &raw);
    atexit(disable_raw_mode);

    /* invert local echo flags of terminal */
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO);

    /*  */
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(void)
{
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c !='q');
    return 0;
    /* Set raw mode functions for start and exit of the function */
    /* Disable flags for the local terminal at program instace */
}