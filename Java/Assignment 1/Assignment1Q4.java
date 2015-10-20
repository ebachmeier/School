public class Assignment1Q4 {
  
  public static boolean sumToK (int[] A, int k){
    int i, x, y;
    for (int j = 0; j < A.length; j++){
      i = 0;
      while (i < A.length){
        x = A[j];
        y = A[i];
        if ((x != y) && ((x + y) == k))
          return true;
        else
          i += 1;
      }
    }
    return false;
  }
  
  public static void main(String[] args){
    int[] A = {4, 7, 3, 9, -1, 2, 11};
    
    System.out.println(sumToK(A, 20));
    System.out.println(sumToK(A, 33));
  }
}