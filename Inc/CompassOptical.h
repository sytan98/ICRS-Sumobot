#ifndef ICRS_SUMOBOT_COMPASSOPTICAL_H
#define ICRS_SUMOBOT_COMPASSOPTICAL_H

#include <stdio.h>
#include <math.h>

#define PI 3.141593
#define REAR_SENSOR_OFFSET 10
#define SIDE_SENSOR_OFFSET 10

/* orientation and position variables */
// Heading - the position of our robot
// startAngle - initial position our robot is facing
static float heading, startAngle;
// xycoords: the x,y coordinates of our robot on the field.
// will have to measure the field and set this to a reasonable value before the competition.
extern float xycoords[2];
// polar coords: coordinates measured in r, theta.
extern float polarcoords[2];

/* orientation and position functions */
// gets the relative heading of the robot from compass readings
float getHeading(float angle);
// updates the x,y position of the robot
void updatePos(float hdg, int dx, int dy);
// gets the polar coordinates of the current xy pos
void updatePolarCoords(void);
/* distance sensor filtering variables */

// holds the max expected readings for each distance sensor.
// indexed clockwise from robot 12'o clock:
// 0: FR-TOF, 1: R-US, 2: RR-US, 3: LR-US, 4: L-US, 5: FL-TOF.
static float maxSensorRange[6];

/* distance sensor filtering functions */
// uses the global heading and x,y position variables to update the above array
void updateMaxSensorRange(float hdg);
float quadraticPos(float a, float b, float c);
float quadraticNeg(float a, float b, float c);

#endif //ICRS_SUMOBOT_COMPASSOPTICAL_H