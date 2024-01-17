/*************************************************************
 * 1. Name:
 *      Jared Weisgarber
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/
#include <iostream>  // for CIN and COUT
#include <cmath>
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
 // your function goes here
double computeDistance(double startingPos, double velocity, double accel, double time)
{
    double distance;
    distance = startingPos + velocity * time + 0.5 * accel * time * time;
    return distance;
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
 // your function goes here
double computeAcceleration(double force, double mass)
{
    double accel;
    accel = force / mass;
    return accel;
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/
 // your function goes here
double computeVelocity(double velocity, double accel, double time)
{
    double newVelocity;
    newVelocity = velocity + accel * time;
    return newVelocity;
}
/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
 // your function goes here
double computeVerticalComponent(double a, double total) {
    double y;
    y = total * cos(a);
    return y;
}

/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/
 // your function goes here
double computeHorizontalComponent(double a, double total) {
    double x;
    x = total * sin(a);
    return x;
}

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/
 // your function goes here
double computeTotalComponent(double x, double y) {
    double total;
    total = sqrt(x * x + y * y);
    return total;
}

/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/
 // your function goes here
double convertDegToRad(double d) {
    double r;
    double pi = 2*acos(0.0);
    r = d / 360 * 2 * pi;
    return r;
}

/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
 // your function goes here
double prompt(string message) {
    double response;
    cout << message << " ";
    cin >> response;
    return response;
}

/****************************************************************
 * MAIN
 * Prompt for input, compute new position, and display output
 ****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
    double x = 0.0;
    double t = 1.0;
    double aRadians;            // Angle in radians
    double accelerationThrust;  // Acceleration due to thrust
    double ddxThrust;           // Horizontal acceleration due to thrust
    double ddyThrust;           // Vertical acceleration due to thrust
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double v;                   // Total velocity
    
    accelerationThrust = computeAcceleration(THRUST, WEIGHT);
    aRadians = convertDegToRad(aDegrees);
    ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
    ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);
    
    // Go through the simulator five times
    for (int i = 0; i < 5; i++) {
        // Calculate the components of the acceleration due to thrust and gravity.
        ddx = ddxThrust;
        ddy = ddyThrust + GRAVITY;
        
        // Find the x and y components of the velocity
        dx = computeVelocity(dx, ddx, t);
        dy = computeVelocity(dy, ddy, t);

        // Find the new position of the LM
        x = computeDistance(x, dx, ddx, t);
        y = computeDistance(y, dy, ddy, t);

        // Find the total velocity
        v = computeTotalComponent(dx, dy);

        // Output
        cout.setf(ios::fixed | ios::showpoint);
        cout.precision(2);
        cout << i + 1 << "s "
             << "x,y:(" << x << ", " << y << ")m  "
             << "dx,dy:(" << dx << ", " << dy << ")m/s  "
             << "speed:" << v << "m/s  "
             << "angle:" << aDegrees << "deg\n";
    }

    return 0;
}
