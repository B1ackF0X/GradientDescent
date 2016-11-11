#include <stdio.h>
#include <math.h>

double CompositeGradientMethod(double epsilon);
double GradientDescent(double x, double alfa, double nablaF);
double AlfaMethod(double a, double b, double x, double epsilon);
int StopCondition(double F1, double F2, double epsilon);
int AlfaStopCondition(double a, double b, int n, double epsilon);
double nablaF(double x);
double f(double x);
double func(struct vector G);

struct vector
{
    double x;
    double y;
};

int main(void)
{
    double epsilon = 0.0000001;
    struct vector some = { 4.0, 5.0 };
    
    printf("%lf\n", CompositeGradientMethod(epsilon));
    printf("%lf\n", func(some));
    
    return 0;
}

double CompositeGradientMethod(double epsilon)
{
    double x = .0, F1, alfa;
    
    alfa = AlfaMethod(0, 1, x, epsilon);
    F1 = GradientDescent(x, alfa, nablaF(x));
    for(; !StopCondition(x, F1, epsilon);)
    {
        x = F1;
        alfa = AlfaMethod(0, 1, x, epsilon);
        F1 = GradientDescent(x, alfa, nablaF(x));
    }
    
    return F1;
}

double GradientDescent(double x, double alfa, double nablaF)
{
    return x - alfa * nablaF;
}

double AlfaMethod(double a, double b, double x, double epsilon)
{
    int i;
    double x1, x2;
    
   
    for(i = 0; !AlfaStopCondition(0, 1, i, epsilon); i++)
    {
        x1 = (a + b)/2 - epsilon/2;
        x2 = (a + b)/2 + epsilon/2;
        
        if(f(x - x1 * nablaF(x)) > f(x - x2 * nablaF(x)))
            a = x1;
        else
            b = x2;
    }
    
    return x1;
}

int StopCondition(double F1, double F2, double epsilon)
{
    if (fabs(F2 - F1) < epsilon)
        return 1;
    
    return 0;
}

int AlfaStopCondition(double a, double b, int n, double epsilon)
{
    if ((b-a-epsilon)/pow(2, n+1) < epsilon/2)
        return 1;
    
    return 0;
}

double nablaF(double x)
{
    return 2*(x-1);
}

double f(double x)
{
    return (x-1)*(x-1);
}

double func(struct vector G)
{
    return G.x + G.y;
}
