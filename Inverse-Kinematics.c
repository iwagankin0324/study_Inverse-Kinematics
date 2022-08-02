#include<stdio.h>
#include<math.h>

#define pi 3.14159265359
#define eps 1.0e-3
int max_itr = 100;

//リンク長
double L1 = 1.0;
double L2 = 1.0;
//初期座標
double x , y;
//初期角度
double q1 = 0.0;
double q2 = 0.0;

int main(void)
{
    int itr;
    double p1, p2;
    double J11, J12, J21, J22;
    double detJ;
    double dp1, dp2, dq1, dq2;
    double x_tmp, y_tmp;

    //初期座標
    double x , y;
    x = L1*cos(q1)+L2*cos(q1+q2);
    y = L1*sin(q1)+L2*sin(q1+q2);
    printf("init_crd: x= %e , y= %e\n", x, y);
    
    //手先位置の入力
    p1 = 1.366;
    p2 = 1.366;
    // printf("p1= ");
    // scanf("%lf", &p1);
    // printf("p2= ");
    // scanf("%lf", &p2);



    dp1 = p1 - x;
    dp2 = p2 - y;
    printf("dp1= %e, dp2= %e\n", dp1, dp2);

    for(itr = 0; itr < max_itr; itr++){

        printf("itr= %d\n", itr);

        //ヤコビ行列
        J11 = -L1*sin(q1)-L2*sin(q1+q2);
        J12 = -L2*sin(q1+q2);
        J21 =  L1*cos(q1)-L2*cos(q1+q2);
        J22 =  L2*cos(q1+q2);
        //printf("J11= %e, J12=  %e, J21= %e, J=22 %e\n", J11, J12, J21, J22);

        //ヤコビ行列式
        detJ = J11*J22 - J12*J21;
        
        //itr=0の時、零割したので対処
        if(itr==0) detJ = 1.0;

        //角速度の計算
        dq1 =  (J22/detJ)*dp1 - (J12/detJ)*dp2;
        dq2 = -(J21/detJ)*dp1 + (J11/detJ)*dp2;

        //角度の更新
        q1 = q1 + dq1;
        q2 = q2 + dq2;

        //手先位置の更新
        x = L1*cos(q1)+L2*cos(q1+q2);
        y = L1*sin(q1)+L2*sin(q1+q2);
        printf("calculation: x= %e , y= %e\n", x, y);

        dp1 = p1 - x;
        dp2 = p2 - y;
        x_tmp = fabs( dp1 );
        y_tmp = fabs( dp2 );
        printf("absolute value: x_tmp= %e , y_tmp= %e\n", x_tmp, y_tmp);

        if( (x_tmp < eps) && (y_tmp < eps) ) break;
        
    }

    printf("\n");

    if(itr==max_itr){
        printf("Newton method failed.\n");
    }else{
        printf("Result:\n");
        printf("itr= %d\n", itr);
        printf("x= %e , y= %e\n", x, y);
        printf("dx= %e , dy= %e\n", dp1, dp2);
        printf("q_x= %e , q_y= %e\n", p1, p2);
        printf("dq_x= %e , dq_y= %e\n", dq1, dq2);
    }

    return 0;

}