#include "CompassOptical.h"

float xycoords[2] = {24.52,24};
float polarcoords[2] = {0,0};

// Angle is the reading of the compass sensor
// heading and starting directions defined beforehand as globals
float getHeading(float angle){
    heading = angle - startAngle;
    if(heading < 0){
        heading += 360;
    }
    return heading;
}
// Do we need to init a trigo function LUT?
// Remember to include and link math.h
void updatePos(float hdg, int dx, int dy){
    float deltaX, deltaY;

    hdg = hdg*PI/180; // Convert degrees into radians
    // printf("Heading is %f, PI is %f\n", hdg, M_PI);

    // taking into account change in X position
    deltaX = dx*sin(hdg);
    deltaY = dx*cos(hdg);
    xycoords[0] += deltaX;
    xycoords[1] += deltaY;

    // taking into account change in Y position
    hdg += PI/2;
    deltaX = dy*sin(hdg);
    deltaY = dy*cos(hdg);
    xycoords[0] += deltaX;
    xycoords[1] += deltaY;
}
void updatePolarCoords(void){
    // atan(y/x) gives theta in RADIANS
    polarcoords[1] = atan2(xycoords[1], xycoords[0] );
    // pythagoras' theorem
    polarcoords[0] = sqrt(xycoords[0]*xycoords[0] + xycoords[1]*xycoords[1]);
}

// takes into account the TOF sensor angle to give a proper reading
// Have to see the orientation of the TOF servos!
// Current assumption: TOF sensor ranges from 45-135.
// 90 is dead center. 45 is full left, and 135 is full right.
void updateMaxSensorRange(float hdg){
    // Based on equations of a circle, we are solving the +- quadratic equations.

    // Firstly, this is for finding the Rear sensor distances.
    float x = xycoords[0];
    float y = xycoords[1];

    float xpos, xneg, ypos, yneg;
    float grad, yint;

    // Transform from north up to regular trigo angles
    hdg +=90;
    if(hdg >= 360){
        hdg -= 360;
    }

    if(hdg==90 || hdg == 270){
        // Solve for y instead of x.
        ypos = sqrt(70*70 - x*x);
        yneg = -ypos;
        xpos = x;
        xneg = x;
    } else if (hdg==0 || hdg==180){
        // Solve for horizontal line
        ypos = y;
        yneg = y;
        xpos = sqrt(70*70 - y*y);
        xneg = -xpos;
    } else {
        // Indeterminate case, solve a quadratic equation.
        float hdgRad = hdg * PI / 180;
        grad = tan(hdgRad);

        yint = y-grad*x;

        printf("grad is %3f and yint is %3f\n", grad, yint);

        float a, b, c;
        a = (grad*grad) + 1;
        b = 2*grad*yint;
        c = yint*yint - 70*70;

        printf("a:%3f, b:%3f, c:%3f\n", a, b, c);
        ypos = quadraticPos(a, b, c)*grad + yint;
        yneg = quadraticNeg(a, b, c)*grad + yint;
    }

    float distpos = sqrt( pow(ypos-y, 2) + pow(xpos-x, 2) );
    float distneg = sqrt( pow(yneg-y, 2) + pow(xneg-x, 2) );


    // need to come up with how to accept or reject the possible values: which one should we take?
    // Come up with something based on polar coordinates and current robot direction.

    // below is just for debug only, to see whether values are reasonable.
    // In truth we just have to know what direction the robot is facing to know what to write to.

    /* If heading is from 0 - 180 (robot faces the "front" of the field) then rear sensor max dist
     * is the one that is calculated from yneg/xneg.
     * Else, it is the one calculated from ypos/xpos.
     */
    if(hdg < 180){
        // 0: FR-TOF, 1: R-US, 2: RR-US, 3: LR-US, 4: L-US, 5: FL-TOF.
        maxSensorRange[0] = distpos;
        maxSensorRange[5] = distpos;
        maxSensorRange[2] = distneg;
        maxSensorRange[3] = distneg;
    } else {
        maxSensorRange[0] = distneg;
        maxSensorRange[5] = distneg;
        maxSensorRange[2] = distpos;
        maxSensorRange[3] = distpos;
    }

    // Solve for the distances for the side ultrasounds: take a similar approach as before.
    // Transform from regular trigo angle to angle for side sensor.
    hdg -=90;
    if(hdg < 0){
        hdg += 360;
    }
    if(hdg==90 || hdg == 270){
        // Solve for y instead of x.
        ypos = sqrt(70*70 - x*x);
        yneg = -ypos;
        xpos = x;
        xneg = x;
    } else if (hdg==0 || hdg==180){
        // Solve for horizontal line
        ypos = y;
        yneg = y;
        xpos = sqrt(70*70 - y*y);
        xneg = -xpos;
    } else {
        // Indeterminate case, solve a quadratic equation.
        float hdgRad = hdg * PI / 180;
        grad = tan(hdgRad);

        yint = y-grad*x;

        printf("grad is %3f and yint is %3f\n", grad, yint);

        float a, b, c;
        a = (grad*grad) + 1;
        b = 2*grad*yint;
        c = yint*yint - 70*70;

        printf("a:%3f, b:%3f, c:%3f\n", a, b, c);
        ypos = quadraticPos(a, b, c)*grad + yint;
        yneg = quadraticNeg(a, b, c)*grad + yint;
    }

    distpos = sqrt( pow(ypos-y, 2) + pow(xpos-x, 2) );
    distneg = sqrt( pow(yneg-y, 2) + pow(xneg-x, 2) );

    // Similarly as before, if hdg is between 0 and 180, right sensor is xpos/ypos, and vice versa.
    if(hdg < 180){
        // 0: FR-TOF, 1: R-US, 2: RR-US, 3: LR-US, 4: L-US, 5: FL-TOF.
        maxSensorRange[1] = distpos;
        maxSensorRange[4] = distneg;
    } else {
        maxSensorRange[1] = distneg;
        maxSensorRange[4] = distpos;
    }

}

float quadraticPos(float a, float b, float c){
    float disc = b*b - 4*a*c;
    if(disc < 0){
        printf("imag number\n");
    }
    float num = -b + sqrt(disc);
    float den = 2*a;
    if(den==0){
        printf("the given a was a zero!!\n");
    }
    return num/den;
}
float quadraticNeg(float a, float b, float c){
    float disc = b*b - 4*a*c;
    if(disc < 0){
        printf("imag number\n");
    }
    float num = -b - sqrt(disc);
    float den = 2*a;
    if(den==0){
        printf("the given a was a zero!!\n");
    }
    return num/den;
}