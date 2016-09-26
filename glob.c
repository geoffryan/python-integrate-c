#include "glob.h"

int glob = 0;

void setglob(void)
{
    glob = 17;
}

void setglobexact(int i)
{
    glob = i;
}
