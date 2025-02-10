#include "dry.h"

/* Global Variables: */

Rec_Pointer     Ptr_Glob,
                Next_Ptr_Glob;
int             Int_Glob;
Boolean         Bool_Glob;
char            Ch_1_Glob,
                Ch_2_Glob;
int             Arr_1_Glob [50];
int             Arr_2_Glob [50] [50];

#ifndef REG
        Boolean Reg = false;
#define REG
        /* REG becomes defined as empty */
        /* i.e. no register variables   */
#else
        Boolean Reg = true;
#undef REG
#define REG register
#endif
/* Procedure for the assignment of structures,          */
/* if the C compiler doesn't support this feature       */
 #ifdef  NOSTRUCTASSIGN
 mymemcpy (d, s, l)
 register char   *d;
 register char   *s;
 register int    l;
 {
         while (l--) *d++ = *s++;
 }
 #endif


Boolean		Done;

long            Begin_Time,
                End_Time,
                User_Time;
float           Microseconds,
                Dhrystones_Per_Second;

/* end of variables for time measurement */

/******************************************************************************************************************************************
 * DEFINES
 *****************************************************************************************************************************************/
#define HEAP_TOTAL_SIZE       4*1024
#define HEAP_NODE_SIZE        sizeof(MyHeapNodeType)
#define NULL_PTR  ((void *)0)

/******************************************************************************************************************************************
 * TYPES
 *****************************************************************************************************************************************/
typedef struct MyHeapNodeTypeTag
{
  uint32_t size;                              /* size of heap, without size of control data */
  uint8_t  used;                              /* allocated by application or not*/
  struct MyHeapNodeTypeTag* nextNode;         /* pointer to next heap entry */
  struct MyHeapNodeTypeTag* prevNode;         /* pointer to next heap entry */
} MyHeapNodeType;

/******************************************************************************************************************************************
 * VARIABLES
 *****************************************************************************************************************************************/
static unsigned char MyHeapArea[HEAP_TOTAL_SIZE];
static MyHeapNodeType* heapStart = (MyHeapNodeType *)MyHeapArea;


 /******************************************************************************************************************************************
 * FUNCTIONS
 *****************************************************************************************************************************************/

/**************************************************************************************************
 * meminit
 **************************************************************************************************/
void meminit()
{
  heapStart = (MyHeapNodeType *)MyHeapArea;
  heapStart->size = HEAP_TOTAL_SIZE - HEAP_NODE_SIZE;
  heapStart->nextNode = NULL_PTR;
  heapStart->prevNode = NULL_PTR;
}

/**************************************************************************************************
 * mmalloc
 **************************************************************************************************/
void * mmalloc(size_t size)
{
  MyHeapNodeType* currentHeapBlock;
  MyHeapNodeType* bestHeapBlock;
  uint32_t bestHeapBlockSize;

  /* init current block to start of heap */
  currentHeapBlock = heapStart;
  /* init best heap block */
  bestHeapBlock = (MyHeapNodeType*)NULL_PTR;
  bestHeapBlockSize = HEAP_TOTAL_SIZE + 1; /* init with invalid size */

  while (currentHeapBlock)
  {
    /* check if current block matches and fittest best (so far) */
    if ( (!currentHeapBlock->used) && 
         (currentHeapBlock->size >= (size + HEAP_NODE_SIZE)) && 
         (currentHeapBlock->size <= bestHeapBlockSize) )
    {
      bestHeapBlock = currentHeapBlock;
      bestHeapBlockSize = currentHeapBlock->size;
    }

    currentHeapBlock = currentHeapBlock->nextNode;
  }

  if (bestHeapBlock != NULL_PTR)
  {
    MyHeapNodeType* heapNodeAllocate;

    /* found a matching block, split it up and return the top of the memory area to the user */
    /* the best matching block is decreased by the needed memory area*/
    bestHeapBlock->size = bestHeapBlock->size - size - HEAP_NODE_SIZE;
    /* new heap node is after the current heap + the size of its control data + allocated memory size */
    heapNodeAllocate = (MyHeapNodeType*)(((unsigned char*)bestHeapBlock) + HEAP_NODE_SIZE + bestHeapBlock->size);
    heapNodeAllocate->size = size;
    heapNodeAllocate->used = 1;
    heapNodeAllocate->nextNode = bestHeapBlock->nextNode;
    heapNodeAllocate->prevNode = bestHeapBlock;
    if (bestHeapBlock->nextNode != NULL_PTR)
    {
      /* next block exists */
      bestHeapBlock->nextNode->prevNode = heapNodeAllocate;
    }
    bestHeapBlock->nextNode = heapNodeAllocate;
    /* return pointer to memory of new heap node after control data */
    return (void*)((unsigned char*)heapNodeAllocate + HEAP_NODE_SIZE);
  }

  return NULL_PTR;
}

/**************************************************************************************************
 * memfree
 **************************************************************************************************/
void memfree(void* p)
{
  if (p == NULL_PTR)
  {
    return;
  }

  /* get actual heap node */
  MyHeapNodeType* currentBlock = (MyHeapNodeType*)((unsigned char*)p - HEAP_NODE_SIZE);

  if (currentBlock == NULL_PTR)
  {
    return;
  }

  currentBlock->used = 0;

  /* check if we can merge with next block */
  if (currentBlock->nextNode != NULL_PTR)
  {
    if (!currentBlock->nextNode->used)
    {
      /* add size of next block and its control data to current block */
      currentBlock->size += currentBlock->nextNode->size;
      currentBlock->size += HEAP_NODE_SIZE;

      /* remove next block */
      /* link current block to next-next block */
      currentBlock->nextNode = currentBlock->nextNode->nextNode;
      /* link next-next block to current block if next-next block exists */
      if (currentBlock->nextNode != NULL_PTR) /* currentBlock->nextNode points to next-next block already! */
      {
        currentBlock->nextNode->prevNode = currentBlock;
      }
    }
  }

  /* check if we can merge with previous block */
  if (currentBlock->prevNode != NULL_PTR)
  {
    if (!currentBlock->prevNode->used)
    {
      /* add size of freed memory block and its control data to previous block */
      currentBlock->prevNode->size += currentBlock->size;
      currentBlock->prevNode->size += HEAP_NODE_SIZE;

      /* remove freed block from list */
      /* link previous block to next block */
      currentBlock->prevNode->nextNode = currentBlock->nextNode;
      /* link next block to previous block if next block exists */
      if (currentBlock->nextNode != NULL_PTR)
      {
        currentBlock->nextNode->prevNode = currentBlock->prevNode;
      }
    }
  }
}

/* prototype declarations */
/* in this file */
void Proc_1(REG Rec_Pointer Ptr_Val_Par);
void Proc_2(One_Fifty *Int_Par_Ref);
void Proc_3(Rec_Pointer *Ptr_Ref_Par);
void Proc_4(void);
void Proc_5(void);


int main (argc, argv) int argc; char *argv[];
/*****/

  /* main program, corresponds to procedures        */
  /* Main and Proc_0 in the Ada version             */
{

  meminit();
  
        One_Fifty       Int_1_Loc;
  REG   One_Fifty       Int_2_Loc;
        One_Fifty       Int_3_Loc;
  REG   char            Ch_Index;
        Enumeration     Enum_Loc;
        Str_30          Str_1_Loc;
        Str_30          Str_2_Loc;
  REG   int             Run_Index;
  REG   int             Number_Of_Runs;

  /* Arguments */
  if (argc > 2)
  {
     printf ("Usage: %s [number of loops]\n", argv[0]);
  }
  if (argc == 2)
  {
     Number_Of_Runs = atoi (argv[1]);
  } else
  {
     Number_Of_Runs = NUMBER_OF_RUNS;
  }
  if (Number_Of_Runs <= 0)
  {
     Number_Of_Runs = NUMBER_OF_RUNS;
  }

  /* Initializations */

  Next_Ptr_Glob = (Rec_Pointer) mmalloc (sizeof (Rec_Type));
  Ptr_Glob = (Rec_Pointer) mmalloc (sizeof (Rec_Type));

  Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
  Ptr_Glob->Discr                       = Ident_1;
  Ptr_Glob->variant.var_1.Enum_Comp     = Ident_3;
  Ptr_Glob->variant.var_1.Int_Comp      = 40;
  strcpy (Ptr_Glob->variant.var_1.Str_Comp, 
          "DHRYSTONE PROGRAM, SOME STRING");
  strcpy (Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

  Arr_2_Glob [8][7] = 10;
        /* Was missing in published program. Without this statement,    */
        /* Arr_2_Glob [8][7] would have an undefined value.             */
        /* Warning: With 16-Bit processors and Number_Of_Runs > 32000,  */
        /* overflow may occur for this array element.                   */

  printf ("\n");
  printf ("Dhrystone Benchmark, Version %s\n", Version);
  if (Reg)
  {
    printf ("Program compiled with 'register' attribute\n");
  }
  else
  {
    printf ("Program compiled without 'register' attribute\n");
  }
  printf ("Using %s, HZ=%d\n", CLOCK_TYPE, HZ);
  printf ("\n");

  Done = false;
  while (!Done) {
    Arr_2_Glob [8][7] = 10;

    printf ("Trying %d runs through Dhrystone:\n", Number_Of_Runs);

    /***************/
    /* Start timer */
    /***************/


    for (Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
    {

      Proc_5();
      Proc_4();
	/* Ch_1_Glob == 'A', Ch_2_Glob == 'B', Bool_Glob == true */
      Int_1_Loc = 2;
      Int_2_Loc = 3;
      strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
      Enum_Loc = Ident_2;
      Bool_Glob = ! Func_2 (Str_1_Loc, Str_2_Loc);
	/* Bool_Glob == 1 */
      while (Int_1_Loc < Int_2_Loc)  /* loop body executed once */
      {
	Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
	  /* Int_3_Loc == 7 */
	Proc_7 (Int_1_Loc, Int_2_Loc, &Int_3_Loc);
	  /* Int_3_Loc == 7 */
	Int_1_Loc += 1;
      } /* while */
	/* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
      Proc_8 (Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);
	/* Int_Glob == 5 */
      Proc_1 (Ptr_Glob);
      for (Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
			       /* loop body executed twice */
      {
	if (Enum_Loc == Func_1 (Ch_Index, 'C'))
	    /* then, not executed */
	  {
	  Proc_6 (Ident_1, &Enum_Loc);
	  strcpy (Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
	  Int_2_Loc = Run_Index;
	  Int_Glob = Run_Index;
	  }
      }
	/* Int_1_Loc == 3, Int_2_Loc == 3, Int_3_Loc == 7 */
      Int_2_Loc = Int_2_Loc * Int_1_Loc;
      Int_1_Loc = Int_2_Loc / Int_3_Loc;
      Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;
	/* Int_1_Loc == 1, Int_2_Loc == 13, Int_3_Loc == 7 */
      Proc_2 (&Int_1_Loc);
	/* Int_1_Loc == 5 */

    } /* loop "for Run_Index" */

    /**************/
    /* Stop timer */
    /**************/


    User_Time = End_Time - Begin_Time;

    if (false)
    {
      printf ("Measured time too small to obtain meaningful results\n");
      Number_Of_Runs = Number_Of_Runs * 10;
      printf ("\n");
    } else{
     Done = true;
    }
  }

  fprintf (stderr, "Final values of the variables used in the benchmark:\n");
  fprintf (stderr, "\n");
  fprintf (stderr, "Int_Glob:            %d\n", Int_Glob);
  fprintf (stderr, "        should be:   %d\n", 5);
  fprintf (stderr, "Bool_Glob:           %d\n", Bool_Glob);
  fprintf (stderr, "        should be:   %d\n", 1);
  fprintf (stderr, "Ch_1_Glob:           %c\n", Ch_1_Glob);
  fprintf (stderr, "        should be:   %c\n", 'A');
  fprintf (stderr, "Ch_2_Glob:           %c\n", Ch_2_Glob);
  fprintf (stderr, "        should be:   %c\n", 'B');
  fprintf (stderr, "Arr_1_Glob[8]:       %d\n", Arr_1_Glob[8]);
  fprintf (stderr, "        should be:   %d\n", 7);
  fprintf (stderr, "Arr_2_Glob[8][7]:    %d\n", Arr_2_Glob[8][7]);
  fprintf (stderr, "        should be:   Number_Of_Runs + 10\n");
  fprintf (stderr, "Ptr_Glob->\n");
  fprintf (stderr, "  Ptr_Comp:          %p\n", Ptr_Glob->Ptr_Comp);
  fprintf (stderr, "        should be:   (implementation-dependent)\n");
  fprintf (stderr, "  Discr:             %d\n", Ptr_Glob->Discr);
  fprintf (stderr, "        should be:   %d\n", 0);
  fprintf (stderr, "  Enum_Comp:         %d\n", Ptr_Glob->variant.var_1.Enum_Comp);
  fprintf (stderr, "        should be:   %d\n", 2);
  fprintf (stderr, "  Int_Comp:          %d\n", Ptr_Glob->variant.var_1.Int_Comp);
  fprintf (stderr, "        should be:   %d\n", 17);
  fprintf (stderr, "  Str_Comp:          %s\n", Ptr_Glob->variant.var_1.Str_Comp);
  fprintf (stderr, "        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  fprintf (stderr, "Next_Ptr_Glob->\n");
  fprintf (stderr, "  Ptr_Comp:          %p\n", Next_Ptr_Glob->Ptr_Comp);
  fprintf (stderr, "        should be:   (implementation-dependent), same as above\n");
  fprintf (stderr, "  Discr:             %d\n", Next_Ptr_Glob->Discr);
  fprintf (stderr, "        should be:   %d\n", 0);
  fprintf (stderr, "  Enum_Comp:         %d\n", Next_Ptr_Glob->variant.var_1.Enum_Comp);
  fprintf (stderr, "        should be:   %d\n", 1);
  fprintf (stderr, "  Int_Comp:          %d\n", Next_Ptr_Glob->variant.var_1.Int_Comp);
  fprintf (stderr, "        should be:   %d\n", 18);
  fprintf (stderr, "  Str_Comp:          %s\n",
                                Next_Ptr_Glob->variant.var_1.Str_Comp);
  fprintf (stderr, "        should be:   DHRYSTONE PROGRAM, SOME STRING\n");
  fprintf (stderr, "Int_1_Loc:           %d\n", Int_1_Loc);
  fprintf (stderr, "        should be:   %d\n", 5);
  fprintf (stderr, "Int_2_Loc:           %d\n", Int_2_Loc);
  fprintf (stderr, "        should be:   %d\n", 13);
  fprintf (stderr, "Int_3_Loc:           %d\n", Int_3_Loc);
  fprintf (stderr, "        should be:   %d\n", 7);
  fprintf (stderr, "Enum_Loc:            %d\n", Enum_Loc);
  fprintf (stderr, "        should be:   %d\n", 1);
  fprintf (stderr, "Str_1_Loc:           %s\n", Str_1_Loc);
  fprintf (stderr, "        should be:   DHRYSTONE PROGRAM, 1'ST STRING\n");
  fprintf (stderr, "Str_2_Loc:           %s\n", Str_2_Loc);
  fprintf (stderr, "        should be:   DHRYSTONE PROGRAM, 2'ND STRING\n");
  fprintf (stderr, "\n");


    Microseconds = (float) User_Time * Mic_secs_Per_Second 
                        / ((float) HZ * ((float) Number_Of_Runs));
    Dhrystones_Per_Second = ((float) HZ * (float) Number_Of_Runs)
                        / (float) User_Time;

    printf ("Microseconds for one run through Dhrystone: ");
    printf ("%10.1f \n", Microseconds);
    printf ("Dhrystones per Second:                      ");
    printf ("%10.0f \n", Dhrystones_Per_Second);
    printf ("\n");
  
}


void Proc_1 (Ptr_Val_Par)
/******************/

REG Rec_Pointer Ptr_Val_Par;
    /* executed once */
{
  REG Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;  
                                        /* == Ptr_Glob_Next */
  /* Local variable, initialized with Ptr_Val_Par->Ptr_Comp,    */
  /* corresponds to "rename" in Ada, "with" in Pascal           */
  
  structassign (*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob); 
  Ptr_Val_Par->variant.var_1.Int_Comp = 5;
  Next_Record->variant.var_1.Int_Comp 
        = Ptr_Val_Par->variant.var_1.Int_Comp;
  Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
  Proc_3 (&Next_Record->Ptr_Comp);
    /* Ptr_Val_Par->Ptr_Comp->Ptr_Comp 
                        == Ptr_Glob->Ptr_Comp */
  if (Next_Record->Discr == Ident_1)
    /* then, executed */
  {
    Next_Record->variant.var_1.Int_Comp = 6;
    Proc_6 (Ptr_Val_Par->variant.var_1.Enum_Comp, 
           &Next_Record->variant.var_1.Enum_Comp);
    Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
    Proc_7 (Next_Record->variant.var_1.Int_Comp, 10, 
           &Next_Record->variant.var_1.Int_Comp);
  }
  else /* not executed */
    structassign (*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
} /* Proc_1 */


void Proc_2 (Int_Par_Ref)
/******************/
    /* executed once */
    /* *Int_Par_Ref == 1, becomes 4 */

One_Fifty   *Int_Par_Ref;
{
  One_Fifty  Int_Loc;  
  Enumeration   Enum_Loc;

  Int_Loc = *Int_Par_Ref + 10;
  do /* executed once */
    if (Ch_1_Glob == 'A')
      /* then, executed */
    {
      Int_Loc -= 1;
      *Int_Par_Ref = Int_Loc - Int_Glob;
      Enum_Loc = Ident_1;
    } /* if */
  while (Enum_Loc != Ident_1); /* true */
} /* Proc_2 */


void Proc_3 (Ptr_Ref_Par)
/******************/
    /* executed once */
    /* Ptr_Ref_Par becomes Ptr_Glob */

Rec_Pointer *Ptr_Ref_Par;

{
  if (Ptr_Glob != Null)
    /* then, executed */
    *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
  Proc_7 (10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
} /* Proc_3 */


void Proc_4 (void) /* without parameters */
/*******/
    /* executed once */
{
  Boolean Bool_Loc;

  Bool_Loc = Ch_1_Glob == 'A';
  Bool_Glob = Bool_Loc | Bool_Glob;
  Ch_2_Glob = 'B';
} /* Proc_4 */


void Proc_5 (void) /* without parameters */
/*******/
    /* executed once */
{
  Ch_1_Glob = 'A';
  Bool_Glob = false;
} /* Proc_5 */


