
typedef struct
{ char first_name[20],
       last_name[20]; 
  int  score;
  char grade;
}student_t;
student_t stul, stu2;

struct { int x, y; } x;

struct { int x, y; } y;

int main(void) {
    
    student_t stu_list[30];
    
    printf("%s", stul);
    
    printf("%d %c", stul.score, stul.grade);
    
    stu2 = stul;
    
    if(stu2.score == stul.score)
        printf("Equal");
    
    if(stu2 == stul)
            printf("Equal structures");
    
    scan_student(&stul);
    
    stu2.last_name = "Martin";
}

