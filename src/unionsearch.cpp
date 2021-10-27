#include <iostream>
#include <stdio.h>
#include <stdlib.h>

const int w = 8, h = 8;
int input[w][h] =   {
                    {1,0,0,0,1,0,0,1},
                    {1,1,0,1,1,1,1,0},
                    {0,1,0,0,0,0,0,1},
                    {1,1,1,1,0,1,0,1},
                    {0,0,0,0,0,0,1,0},
                    {0,0,1,0,0,1,0,0},
                    {0,1,0,0,1,1,1,0},
                    {1,0,1,1,0,1,0,1}};
int component[w*h];

void doUnion(int a, int b)
{
// get the root component of a and b, and set the one's parent to the other
while (component[a] != a)
    a = component[a];
while (component[b] != b)
    b = component[b];
    component[b] = a;
}

void unionCoords(int x, int y, int x2, int y2)
{
if (y2 < h && x2 < w && input[x][y] && input[x2][y2] && y2 > 0 && x2 > 0)
    doUnion(x*h + y, x2*h + y2);
}

int main()
{
int i, j;
for (i = 0; i < w*h; i++)
    component[i] = i;

for (int x = 0; x < w; x++)
{
for (int y = 0; y < h; y++)
{
    unionCoords(x, y, x+1, y);
    unionCoords(x, y, x, y+1);
    unionCoords(x, y, x+1, y+1);
    unionCoords(x, y, x-1, y+1);
    unionCoords(x, y, x+1, y-1);
    unionCoords(x, y, x-1, y-1);
}
}



// print the array
for (int x = 0; x < w; x++)
{
    for (int y = 0; y < h; y++)
    {
        if (input[x][y] == 0)
        {
            printf("%4d ",input[x][y]);
            continue;
        }
        int c = x*h + y;
        while (component[c] != c) c = component[c];
        printf("%4d ", component[c]);

    }
    printf("\n");
}
}