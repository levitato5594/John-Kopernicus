#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const float pi = 3.14159265359;
const double G = 6.67430*pow(10,-11);

// List of functions that calculate dv
float ejectionAngle(float transfer_Period,float destination_Period);
double circularization_DV(double transferOrbit_ApV,double destination_Orbital_V);
double insertion_Inner_DV(double transferOrbit_PeV,double destination_Orbital_V);

//Transfer dv

void Transfer_DV_outer(double body_gee,double bodyRadius, double initialOrbit, double destination_SemiMajor, double departure_semiMajor, double referenceMass) {

    // Variables for main function
    double ecc, bodyMass,semiMajor,T,T1,Vp,Vpe,orbitalSpeed,ejectSpeed_Initial,Vlib,deltaV;

    // Main ejection DV calculations
    bodyMass = (body_gee*9.81*pow(bodyRadius,2))/G;

    // Semi-major axis of transfer orbit
    semiMajor = (destination_SemiMajor + departure_semiMajor)/2;

    T1 = 2*pi*sqrt(pow(departure_semiMajor,3)/(G*referenceMass));
    orbitalSpeed = (2*pi*departure_semiMajor)/T1;

    ecc = (destination_SemiMajor/semiMajor)-1;

    T = 2*pi*sqrt(pow(semiMajor,3)/(G*referenceMass));

    // Speed at periapsis of transfer orbit
    Vp = (2*pi*semiMajor/T)*sqrt((1+ecc)/(1-ecc));

    //
    ejectSpeed_Initial = Vp - orbitalSpeed;

    Vlib = sqrt((2*G*bodyMass)/(bodyRadius + initialOrbit));

    // Speed at periapsis after burn
    Vpe = sqrt(pow(ejectSpeed_Initial,2)+pow(Vlib,2));

    //Vpe - Circularization speed
    deltaV = Vpe - sqrt((G*bodyMass)/(bodyRadius + initialOrbit));

    // end of Ejection Dv calculations

    // Variables for sub functions
    double destination_Period = 2*pi*sqrt(pow(destination_SemiMajor,3)/(G*referenceMass)); // period of destination, for ejection angle
    double Va = (2*pi*semiMajor/T)*sqrt((1-ecc)/(1+ecc)); // speed at apoapsis, for circularization DV
    double orbitalSpeed_destination = (2*pi*destination_SemiMajor)/destination_Period;


    printf("\nDV of transfer is : %.0lf m/s",deltaV);

    printf("\nEjection angle of transfer is : %.0lf degrees",ejectionAngle(T,destination_Period));

    if(departure_semiMajor < destination_SemiMajor)
        printf("\nCircularization DV is : %.0lf m/s\n", circularization_DV(Va,orbitalSpeed_destination));

    if(departure_semiMajor > destination_SemiMajor)
        printf("\nCircularization DV is : %.0lf m/s\n", insertion_Inner_DV(Vp,orbitalSpeed_destination));

    printf("\n");
}


float ejectionAngle(float transfer_Period,float destination_Period)
{
    float ejectionAngle,time,alpha;

    // the time of travel is equal to the half of the transfer's orbit period
    time = transfer_Period/2;

    //angle done by the destination body on its orbit over that period of time
    alpha = (time/destination_Period)*360;

    //travel angle
    ejectionAngle = 180 - alpha;

    return ejectionAngle;
}

double circularization_DV(double transferOrbit_ApV,double destination_Orbital_V) {
    double circularization_DV = abs(destination_Orbital_V - transferOrbit_ApV);

    return circularization_DV;
}

double insertion_Inner_DV(double transferOrbit_PeV,double destination_Orbital_V) {

    double insertion_Inner_DV = abs(destination_Orbital_V- transferOrbit_PeV);

    return insertion_Inner_DV;
}

void liberation_Speed(double geeASL, double radius, double parking_Orbit) {
    double dv, mass;

    mass = (geeASL*9.81*pow(radius,2))/G;
    dv = sqrt((2*G*mass)/(radius+parking_Orbit)) - (2*pi*(radius + parking_Orbit)/(2*pi*sqrt(pow(radius+parking_Orbit,3)/(G*mass))));

    printf("\nThe speed of liberation from the planet of origin at the selected parking orbit is : %.0lf m/s\n", dv);
}

void minSpeed_Circ(double geeASL, double time, double radius, double parking_Orbit) {

    // dv for gravity loss
    double loss, g, mass, dv;

    mass = (geeASL*9.81*pow(radius,2))/G;

    const double f = 0.7; // flight profile approximation

    g = geeASL * 9.81; // turn geeASL to m/s^2

    loss = g*time*f;

    // dv for min speed of circularization
    dv = sqrt((G*mass)/(radius+parking_Orbit));

    printf("\nMinimum DV for orbital insertion : %.0lf m/s\n", dv);

    printf("\nSpeed loss due to gravity (dv that needs to be added) : %.0lf m/s\n", loss);

    printf("\nTotal DV to get into orbit from the surface (rough approximation) : %.0lf m/s\n", dv + loss);

}

