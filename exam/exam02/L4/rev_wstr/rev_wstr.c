#include <unistd.h>

int main(int argc, char **argv)
{
    int i = 0;
    int start = 0;
    int end = 0;

    if (argc == 2)
    {
        while (argv[1][i] != '\0')
            i++;
        while (i >= 0)
        {
            while(argv[1][i] == '\0' || argv[1][i] == ' ' || argv[1][i] == '\t')
                i--;
            end = i;
            while (argv[1][i] && argv[1][i] != ' ' && argv[1][i] != '\t')
                i--;
            start = i + 1;
            while (start <= end)
            {
                write (1, &argv[1][start], 1);
                start++;
            }
            int flag = start;
            if (flag != '\0')
                write (1, " ", 1);
        }
    }
    write (1, "\n", 1);
}