#ifndef DELTAV_H
#define DELTAV_H




void Transfer_DV_outer(double body_gee,double bodyRadius, double initialOrbit, double destination_SemiMajor, double departure_semiMajor, double referenceMass);
void liberation_Speed(double mass, double radius, double parking_Orbit);
void minSpeed_Circ(double geeASL, double time, double radius, double parking_Orbit);


#endif //DELTAV_H
