// Written by ProximaCentauri - 2025 - Basic calculator that is made for KSP planet modders to make their lives easier by calculating essentials

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "DeltaV.h"


void Transfer_DV_outer(double bodyMass,double bodyRadius, double initialOrbit, double destination_SemiMajor, double departure_semiMajor, double referenceMass);
void liberation_Speed(double mass, double radius, double parking_Orbit);
void minSpeed_Circ(double geeASL, double time, double radius, double parking_Orbit);


int main(void) {

    float lat;
    float lon;
    float x,y,z;
    char m;
    double r1,r2,mass1,mass2,g1,g2,massB,d1,d2,dB;
    const double G = 6.67430*pow(10,-11);
    float luminosity;


    do {
        printf("+----------------Menu----------------+\nA) Coordinate calculator\nB) Barycenter\nC) Homeworld SMA for Kerbin insulation \nD) DeltaV calculations for interplanetary transfer (dv map aid)\nE) Exit\n>> ");
        scanf("%c",&m);
        fflush(stdin);
        switch(m) {
            case 'a':
            case 'A':

                printf("\nEnter a latitude: \n>> ");
                scanf("%f",&lat);

                printf("\nEnter a longitude: \n>> ");
                scanf("%f",&lon);
                fflush(stdin);
                x = cos(lat)*cos(lon);
                y = sin(lat);
                z = cos(lat)*sin(lon);

                printf("\nThese coordinates in a cartesian system are: \n");
                printf("x = %.30f\ny = %.30f\nz = %.30f\n",x,y,z);

                system("PAUSE");

                system("cls");

                break;
            case 'b':
            case 'B' :

                printf("\nEnter radius of body 1(m)\n>> ");
                scanf("%lf",&r1);

                printf("\nEnter radius of body 2(m)\n>> ");
                scanf("%lf",&r2);

                printf("\nEnter geeASL of body 1\n>> ");
                scanf("%lf",&g1);

                printf("\nEnter geeASL of body 2\n>> ");
                scanf("%lf",&g2);

                printf("\nEnter the distance between the two bodies (m)\n>> ");
                scanf("%lf",&dB);
                fflush(stdin);

                mass1 = (g1*9.81*pow(r1,2))/G;
                mass2 = ((g2*9.81)*pow(r2,2))/G;

                d1 = (dB*mass2)/(mass1+mass2);
                d2 = (dB*mass1)/(mass1+mass2);

                massB = mass1 + mass2;
                printf("\nThe mass of Body 1 is: %.10ekg\nThe mass of Body 2 is: %.10ekg\nMass of the barycenter is: %.10ekg\n",mass1,mass2,massB);

                printf("\nSMA of body 1 (m): %lf\nSMA of body 2 (m): %lf\nThe SMA is relative to the barycenter\n",d1,d2);

                printf("\nNote* : You might want to use these SMAs as SOI sizes for your bodies to avoid overlapping and problems the game might face.\n\n");

                system("PAUSE");

                system("cls");
                break;
            case 'C':
            case 'c':
                printf("\nEnter the luminosity of your star (insolation)\n>> ");
                scanf("%f",&luminosity);
                d1 = sqrt(luminosity*pow(1.36*pow(10,10),2)/1360);

                fflush(stdin);

                printf("\nSMA (m) = %lf\n",d1);
                system("PAUSE");

                system("cls");
                break;

            case 'd':
            case 'D':

                printf("\nEnter the geeASL of your body (surface g)\n>> "); // ask for gee
                scanf("%lf",&g1);

                printf("\nEnter the radius of your body (in meters) (the planet where you depart from)\n>> "); // ask for radius
                scanf("%lf",&r1);

                printf("\nEnter the parking orbit (in meters)\n>> "); // ask orbit radius
                scanf("%lf",&r2);

                printf("\nEnter the semiMajor Axis of your departure (in meters, for scientific notations use E)\n>> "); // ask for departure SMA
                scanf("%lf",&d2);

                printf("\nEnter the semiMajor Axis of your destination (in meters, for scientific notations use E)\n>> "); // ask for destination SMA
                scanf("%lf",&d1);

                printf("\nEnter the mass of the object the two bodies orbit (commonly their star) (in meters, for scientific notations use E)\n>> "); // ask for star mass
                scanf("%lf",&mass1);

                fflush(stdin); // empty input buffer

                Transfer_DV_outer(g1,r1,r2,d1,d2,mass1);
                liberation_Speed(g1, r1, r2);

                printf("\nDo you want an approximation of the DV necessary to put yourself into orbit? (Y/N)\n>> ");

                char YN;
                scanf("%c",&YN);
                fflush(stdin); // empty input buffer

                switch(YN) {
                    case 'y':
                    case 'Y':
                        double time;
                    printf("\nEnter an approximated time of flight (generalized, in seconds): \n>> ");
                    scanf("%lf",&time);

                    minSpeed_Circ(g1,time,r1,r2);
                    break;


                    default: printf("\nInvalid Choice...\n");


                    case 'N': // if no just break buddy
                    case 'n': break;
                }

                system("PAUSE");

                system("cls");

                break;
            case 'e':
            case 'E':
                printf("\nEnd\n"); break;
            default : system("cls"); printf("\nInvalid choice\n"); break;
        }
    }while(m != 'E' && m!='e');


    return 0;
}
