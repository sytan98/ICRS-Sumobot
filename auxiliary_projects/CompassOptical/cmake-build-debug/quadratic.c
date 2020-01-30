#include <stdio.h>
#include <math.h>

#define PI 3.141593


float roots[5];

// float grad, yint;

float* quadratic(float a, float b, float c);
void getLineEqn(float x, float y, float theta);

int main(){
    int a, b, c;

    scanf("%d %d %d", &a, &b, &c);
    getLineEqn(a, b, c);
    
    // With this quadratic equation we want to:
    // Update Max Sensor Range.


}   

float* quadratic(float a, float b, float c){
    float disc;
    disc = b*b;
    disc -= 4*a*c;
    printf("disc is = %3f\n", disc);
    if(disc < 0){
        // Number is imag
        printf("The number is imaginary!\n");
        roots[2] = 0;
    } else if(disc==0) {
        // 2 repeated roots
        printf("Two repeated roots.\n");
        roots[0] = (-b + sqrt(disc) )/ (2*a);
        roots[1] = roots[0];
        roots[2] = 1;
    } else {
        // Two different roots
        printf("Normal quadratic.\n");
        roots[0] = (-b + sqrt(disc) ) / (2*a);
        roots[1] = (-b - sqrt(disc) ) / (2*a);
        roots[2] = 2;
    }
    return roots;
}

void getLineEqn(float x, float y, float theta){
    printf("x coord: %f, y coord: %f, theta: %f\n", x, y, theta);
    
    float grad, yint;
    float ypos, yneg;
    
    if(theta==90 || theta == 270){
        // Solve for y instead of x.
        ypos = sqrt(70*70 - x*x);
        yneg = -ypos;
        roots[0] = x;
        roots[1] = x;
    } else if (theta==0 || theta==180){
        // Solve for horizontal line
        ypos = y;
        yneg = y;
        roots[0] = sqrt(70*70 - y*y);
        roots[1] = -roots[0];
    } else {
        // Indeterminate case, solve a quadratic equation.
        theta = theta * PI / 180;
        grad = tan(theta);

        if(grad==0){
            yint = y;
        }

        yint = y-grad*x;

        printf("grad is %3f and yint is %3f\n", grad, yint);

        float a, b, c;
        a = (grad*grad) + 1;
        b = 2*grad*yint;
        c = yint*yint - 70*70;

        printf("a:%3f, b:%3f, c:%3f\n", a, b, c);

        quadratic(a, b, c);

        ypos = roots[0]*grad + yint;
        yneg = roots[1]*grad + yint;
    }
    
    printf("Positive root is %3f and negative root is %3f\n", roots[0], roots[1]);
    printf("yPos is %3f and yNeg is %3f\n", ypos, yneg);

    float posdist = sqrt( pow(ypos-y, 2) + pow(roots[0]-x, 2) );
    float negdist = sqrt( pow(yneg-y, 2) + pow(roots[1]-x, 2) );

    printf("Positive distance is %f and Negative distance is %f\n", posdist, negdist);

    return;
    
}
