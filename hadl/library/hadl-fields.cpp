
// #include "hadl-fields.h"

template<class D, class F>
F HADL_Field_getValue(D data, int r[][3], int n, int shift, int right, int rot, int arith)
{
   int i,j,l=0;
   unsigned long result=0;
   unsigned long tmp;

   for(i=0;i<n;i++)
   {
      for(
         j=r[i][0];
         (r[i][0]<=r[i][1]) ? (j<=r[i][1]) : (j>=r[i][1]);
         (r[i][0]<=r[i][1]) ? (j+=r[i][2]) : (j-=r[i][2])
      )
      {
         result <<= 1;
         if(data & (1 << j))
            ++result;
         ++l;
      }
   }
      
   if(right)
   {
      tmp = result << (8*sizeof(F) - shift);
      result >>= shift;
      l -= shift;
   }
   else
   {
      tmp = result >> (8*sizeof(F) - shift);
      result <<= shift;
      l += shift;
   }

   if(rot)
      result |= tmp;
   else
   {
      if(arith)
      {
         int msb = result & (1<<(l-1));
         for(i=0;i<8*sizeof(F)-l;i++)
         {
            msb <<= 1;
            result |= msb;
         }
      }
   }
   
   return result;
}

template<class D, class F>
void HADL_Field_setValue(D* target, F data, int r[][3], int n)
{
   int i,j,b;
   unsigned long result=0,m=0;

   for(i=n-1;i>=0;i--)
   {
      for(
         j=r[i][1];
         (r[i][0]<=r[i][1]) ? (j>=r[i][0]) : (j<=r[i][0]);
         (r[i][0]<=r[i][1]) ? (j-=r[i][2]) : (j+=r[i][2])
      )
      {
         b = (data & 1) << j; /* Current bit */
         m |= 1<<j;           /* Mask */
         data >>= 1;          /* Shift data to next bit */

         result |= b;
      }
   }

   *target &= ~m;
   *target |= result;
}

