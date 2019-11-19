
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
  int Pos;
  int MaxLength;

  int *Buffer;
} HEAP;

void Swap( int *A, int *B )
{
  int tmp = *A;
  *A = *B;
  *B = tmp;
}

void SiftUp( HEAP *Heap, int Pos )
{
  while (Pos != 0 && Heap->Buffer[Pos] > Heap->Buffer[(Pos - 1) / 2])
  {
    Swap(&Heap->Buffer[Pos], &Heap->Buffer[(Pos - 1) / 2]);
    Pos = (Pos - 1) / 2;
  }
}

void SiftDown( HEAP *Heap, int Pos )
{
  int size = Heap->Pos + 1;

  while (2 * Pos + 1 < size)
  {
    if (2 * Pos + 2 < size &&
        Heap->Buffer[2 * Pos + 2] > Heap->Buffer[2 * Pos + 1] &&
        Heap->Buffer[2 * Pos + 2] > Heap->Buffer[Pos])
    {
      Swap(&Heap->Buffer[Pos], &Heap->Buffer[2 * Pos + 2]);
      Pos = 2 * Pos + 2;
    }
    else if (Heap->Buffer[2 * Pos + 1] > Heap->Buffer[Pos])
    {
      Swap(&Heap->Buffer[Pos], &Heap->Buffer[2 * Pos + 1]);
      Pos = 2 * Pos + 1;
    }
    else
      break;
  }
}

void Resize( HEAP *Heap )
{
  int tmp[Heap->MaxLength];

  memcpy(tmp, Heap->Buffer, Heap->MaxLength * sizeof(int));

  free(Heap->Buffer);
  Heap->MaxLength *= 2;

  Heap->Buffer = malloc(Heap->MaxLength * sizeof(int));
  memcpy(Heap->Buffer, tmp, Heap->MaxLength / 2 * sizeof(int));
}

void Insert( HEAP *Heap, int X )
{
  Heap->Pos++;
  if (Heap->MaxLength == Heap->Pos)
    Resize(Heap);

  Heap->Buffer[Heap->Pos] = X;
  SiftUp(Heap, Heap->Pos);
}

int Extract( HEAP *Heap )
{
  int max = Heap->Buffer[0], i;

  Swap(&Heap->Buffer[Heap->Pos], &Heap->Buffer[0]);
  Heap->Pos--;
  SiftDown(Heap, 0);
  return max;
}

int main( void )
{
  HEAP heap;
  int N, i;

  heap.Pos = -1;
  heap.MaxLength = 1024;
  heap.Buffer = malloc(sizeof(int) * 1024);

  scanf("%i", &N);
  for (i = 0; i < N; i++)
  {
    int choice, in;

    scanf("%i", &choice);
    switch (choice)
    {
      case 0:
        scanf("%i", &in);
        Insert(&heap, in);
      break;
      case 1:
        printf("%i\n", Extract(&heap));
      break;
    }
  }

  free(heap.Buffer);
  return 0;
}
