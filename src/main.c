
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "words.h"

struct Pattern
{
    char ch0;
    char ch1;
    char ch2;
    char ch3;
    char ch4;

    char nch0[10];
    char nch1[10];
    char nch2[10];
    char nch3[10];
    char nch4[10];

    char inc[10];

    char exc[30];
};

bool Match(struct Pattern *p, const char *word)
{
    /* Fixed characters */
    if (p->ch0 && word[0] != p->ch0)
    {
        return false;
    }
    if (p->ch1 && word[1] != p->ch1)
    {
        return false;
    }
    if (p->ch2 && word[2] != p->ch2)
    {
        return false;
    }
    if (p->ch3 && word[3] != p->ch3)
    {
        return false;
    }
    if (p->ch4 && word[4] != p->ch4)
    {
        return false;
    }

    for (size_t i = 0, len = strlen(p->nch0); i < len; i++)
    {
        if (word[0] == p->nch0[i])
        {
            return false;
        }
    }

    for (size_t i = 0, len = strlen(p->nch1); i < len; i++)
    {
        if (word[1] == p->nch1[i])
        {
            return false;
        }
    }

    for (size_t i = 0, len = strlen(p->nch2); i < len; i++)
    {
        if (word[2] == p->nch2[i])
        {
            return false;
        }
    }

    for (size_t i = 0, len = strlen(p->nch3); i < len; i++)
    {
        if (word[3] == p->nch3[i])
        {
            return false;
        }
    }

    for (size_t i = 0, len = strlen(p->nch4); i < len; i++)
    {
        if (word[4] == p->nch4[i])
        {
            return false;
        }
    }

    bool includeAll = false;

    for (size_t i = 0, len = strlen(p->inc); i < len; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            if (p->inc[i] == word[j])
            {
                includeAll = true;
            }
        }

        if (!includeAll)
        {
            return false;
        }

        includeAll = false;
    }

    bool excludeAll = true;

    for (size_t i = 0, len = strlen(p->exc); i < len; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            if (p->exc[i] == word[j])
            {
                excludeAll = false;
            }
        }

        if (!excludeAll)
        {
            return false;
        }

        excludeAll = true;
    }

    return true;
}

void AddToPattern(struct Pattern *p, const char *word, const char *result)
{
    for (size_t i = 0; i < 5; i++)
    {
        if (result[i] == 'v')
        {
            *(&p->ch0 + i) = word[i];
        }
        else if (result[i] == 'a')
        {
            size_t incLen = strlen(p->inc);
            p->inc[incLen] = word[i];
            p->inc[incLen + 1] = '\0';

            char *ncharAddr = (char *)&p->nch0 + i * 10;
            size_t ncharLen = strlen(ncharAddr);
            *(ncharAddr + ncharLen) = word[i];
            *(ncharAddr + ncharLen + 1) = '\0';
        }
        else if (result[i] == 'g')
        {
            size_t excLen = strlen(p->exc);
            p->exc[excLen] = word[i];
            p->exc[excLen + 1] = '\0';
        }
    }
}

int main()
{
    struct Pattern p = {
        .ch0 = '\0',
        .ch1 = '\0',
        .ch2 = '\0',
        .ch3 = '\0',
        .ch4 = '\0',

        .nch0 = "",
        .nch1 = "",
        .nch2 = "",
        .nch3 = "",
        .nch4 = "",

        .inc = "",
        .exc = "",
    };

    AddToPattern(&p, "turia", "gvavg");
    AddToPattern(&p, "moles", "ggagg");

    size_t max = 20;
    for (size_t i = 0; i < NUMBER_WORDS; i++)
    {
        if (Match(&p, WORDS[i]))
        {
            printf("%s\n", WORDS[i]);

            max--;
            if (!max)
            {
                break;
            }
        }
    }
    int wait;
    scanf_s("%d", &wait);

    return 0;
}
