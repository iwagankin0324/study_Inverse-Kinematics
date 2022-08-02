#include<stdio.h>
#include<math.h>

#define eps  1.0e-4
//#define check

/* √2 の答え */
double ans = 1.41421356237;

/* Newton法による数値計算: √2 */
int main(void){
    int i;
    double tmp;
    double x1 = 5.0, x2;
    int itr = 0;
    double error;

    while(1){
        itr++;
        x2 =  x1 - ((x1 * x1 - 2) / (x1 * 2));
        #ifdef check  
            printf("x2= %e\n", x2);
            tmp = fabs(x2-x1);
            printf("tmp= %e\n", tmp);
        #endif
        if( fabs(x2-x1) < eps ) break;;
        x1 = x2;
    }

    //計算結果
    printf("itaretion: %d\n", itr);
    printf("result: %e\n", x2);

    //答えとの相対誤差
    error = fabs( (x2-ans)/ans )*100;
    printf("relative_error: %e\n", error);    


    return 0;
}
