#include <stdio.h>
#define N 8
#define Q 4


struct quads {
	int topLeft[Q][Q];
	int topRight[Q][Q];
	int bottomLeft[Q][Q];
	int bottomRight[Q][Q];

	int chessBoard[N][N];
};

void fillChessBoard(int[N][N],int);
void fillQuad(int [Q][Q], int);
void printChessBoard(int[N][N]);
int allSpaceDominated(int[N][N]);
int quadBacktrackingTopRight(struct quads*, int);
int quadBacktrackingTopLeft(struct quads*, int);
void mirrorQuad(int[Q][Q], int[Q][Q]);
void mergeQuads(struct quads*);
void checkMergedQuads(struct quads*);
//void printQuad(int[Q][Q]);  // buvo naudojama debuginimui



void fillChessBoard(int chessBoard[N][N], int n)
{
	int i,j;
	for (i = 0; i<N; i++)
	{
		for (j = 0; j<N; j++)
		{
			chessBoard[i][j] = n;
		}
	}
}

void fillQuad(int quad[Q][Q], int n)
{
	int i,j;
	for (i = 0; i<Q; i++)
	{
		for (j = 0; j<Q; j++)
		{
			quad[i][j] = n;
		}
	}
}

/*void printQuad(int quad[Q][Q])
{
	int i,j;
	for(i = 0; i<Q; i++)
	{
		for(j = 0; j<Q; j++)
		{
			if(quad[i][j] == 'K')
			{
				printf("%c",'K');
			}
			else
			{
				printf("%i",quad[i][j]);
			}
		}
	printf("\n");
	}
	printf("\n");

}
*/

void printChessBoard(int chessBoard[N][N])
{
	int i,j;
	for(i = 0; i<N; i++)
	{
		for(j = 0; j<N; j++)
		{
			if(chessBoard[i][j] == 'K')
			{
				printf("%s"," K ");
			}
			else
			{
				printf("%s"," 0 ");
			}
		}
	printf("\n\n");
	}
	printf("\n");

}

int allSpacesDominated(int chessBoard[N][N])
{
	int i,j;
    for(i = 0; i<N; i++)
    {
        for(j = 0; j<N; j++)
        {
            if(chessBoard[i][j]==0) return 0;
        }
    }
    return 1;
}

int quadBacktrackingTopLeft(struct quads* c,int knightCount)
{
	int i,j;
	if(knightCount == 3)
	{
		mirrorQuad(c->topLeft,c->bottomRight);
		if(quadBacktrackingTopRight(c, 0))
		{
			return 1;
		}
		else 
		{
		return 0;
		}
	}
	else
	{
		for(i = 1; i<Q; i++)
		{
			for(j = 1; j<Q; j++)
			{
				if((i == 1 && j == 1) || (i == 3 && j == 3))
				{
					continue;
				}
				else if(c->topLeft[i][j] != 'K')
				{
					c->topLeft[i][j] = 'K';
					if(quadBacktrackingTopLeft(c,knightCount+1))
					{
						return 1;
					}
					else
					{
						c->topLeft[i][j] = 0;
					}
				}
			}
		}
		return 0;
	}
	
}


int quadBacktrackingTopRight(struct quads* c,int knightCount)
{
	int i,j;
	if(knightCount == 3)
	{
		mirrorQuad(c->topRight,c->bottomLeft);
		mergeQuads(c);
		checkMergedQuads(c);

		if(allSpacesDominated(c->chessBoard))
		{
			printChessBoard(c->chessBoard);
			return 1;
		}
		else 
		{
			fillChessBoard(c->chessBoard,0);
			return 0;
		}
	}
	else
	{	
		for(i = 1; i<Q; i++)
		{
			for(j = 0; j<Q-1; j++)
			{
				if((i == 3 && j == 0) || (i == 1 && j == 2))
				{
					continue;
				}
				else if(c->topRight[i][j] != 'K')
				{
					c->topRight[i][j] = 'K';
					if(quadBacktrackingTopRight(c,knightCount+1))
					{
						return 1;
					}
					else
					{
						c->topRight[i][j] = 0;
					}
				}
			}
		}
		return 0;
	}
}




void mirrorQuad(int quad[Q][Q],int mirror[Q][Q])
{
	int i,j;
	for (i = 0; i<Q; i++)
	{
		for(j = 0; j<Q; j++)
		{
			mirror[Q-i-1][Q-j-1] = quad[i][j];
		}
	}
}


void mergeQuads(struct quads* c)
{
	int i,j;
	for(i = 0; i<Q; i++)
	{
		for(j = 0; j<Q; j++)
		{
			c->chessBoard[i][j] = c->topLeft[i][j];
		}
	}
	for(i = 0; i<Q; i++)
	{
		for(j = 4; j<N; j++)
		{
			c->chessBoard[i][j] = c->topRight[i][j-Q];
		}
	}

	for(i = 4; i<N; i++)
	{
		for(j = 0; j<Q; j++)
		{
			c->chessBoard[i][j] = c->bottomLeft[i-Q][j];
		}
	}

	for(i = 4; i<N; i++)
	{
		for(j = 4; j<N; j++)
		{
			c->chessBoard[i][j] = c->bottomRight[i-Q][j-Q];
		}
	}
}


void checkMergedQuads(struct quads* c)
{
	int i,j;
	for(i = 0; i<N; i++)
	{
		for(j = 0; j<N; j++)
		{
			if(c->chessBoard[i][j] == 'K')
			{
			if(i+2 < N && j+1 < N && c->chessBoard[i+2][j+1] != 'K') c->chessBoard[i+2][j+1]=1;
			if(i+2 < N && j-1 >= 0 && c->chessBoard[i+2][j-1] != 'K') c->chessBoard[i+2][j-1]=1;

			if(i-2 >= 0 && j+1 < N && c->chessBoard[i-2][j+1] != 'K') c->chessBoard[i-2][j+1]=1;
			if(i-2 >= 0 && j-1 >= 0 && c->chessBoard[i-2][j-1] != 'K') c->chessBoard[i-2][j-1]=1;

			if(i+1 < N && j+2 < N && c->chessBoard[i+1][j+2] != 'K') c->chessBoard[i+1][j+2]=1;
			if(i+1 < N && j-2 >= 0 && c->chessBoard[i+1][j-2] != 'K') c->chessBoard[i+1][j-2]=1;

			if(i-1 >= 0 && j+2 < N && c->chessBoard[i-1][j+2] != 'K')  c->chessBoard[i-1][j+2]=1;
			if(i-1 >= 0 && j-2 >= 0 && c->chessBoard[i-1][j-2] != 'K') c->chessBoard[i-1][j-2]=1;
			}
		}
	}
}


int main() 
{
	struct quads a;
	
	fillQuad(a.topLeft, 0);
	fillQuad(a.topRight, 0);
	fillQuad(a.bottomLeft, 0);
	fillQuad(a.bottomRight, 0);
	
	quadBacktrackingTopLeft(&a,0);

return 0;
}
