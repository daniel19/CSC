/**
 * Lockheed Martin - CDL Systems USA Technical Question
 * Cylinder.cpp
 * Purpose: Cylinder class that contains the attributes of a right circular cylinder.
 * Commisionioned by: Chelle Fritz
 *
 * @author Daniel Brown
 * @version 1.0 4/24/2014
 *
 */


class Cylinder{
    
private:
    double height;
    double radius;
    double PI  = 22/7;

public:
    
    Cylinder(double h, double r){
        height = h;
        radius = r;
    }
    
    void setHeight(double h){
        height = h;
    }
    
    void setRadius(double r){
        radius = r;
    }
    
    double getHeight(){
        return height;
    }
    
    double getRadius(){
        return radius;
    }
    
    double getVolume(){
        return PI*(radius*radius)*height;
    }

};