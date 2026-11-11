
#include <stdio.h>
#include <string.h>

int main()
{
    char data[50], gen[20], temp[50];
    int i, j, n, m;

    printf("Enter data: ");
    scanf("%s", data);

    printf("Enter generator: ");
    scanf("%s", gen);

    n = strlen(data);
    m = strlen(gen);

    strcpy(temp, data);

    for(i = 0; i < m - 1; i++)
        temp[n + i] = '0';

    temp[n + m - 1] = '\0';

    for(i = 0; i < n; i++)
    {
        if(temp[i] == '1')
        {
            for(j = 0; j < m; j++)
            {
                temp[i+j] =
                    (temp[i+j] == gen[j]) ? '0' : '1';
            }
        }
    }

    printf("\nCRC bits: ");
    for(i = n; i < n + m - 1; i++)
        printf("%c", temp[i]);

    printf("\nTransmitted codeword: %s", data);

    for(i = n; i < n + m - 1; i++)
        printf("%c", temp[i]);

    return 0;
}
