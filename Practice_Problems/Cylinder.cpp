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
    
private://properties of the cylinder
    double height;
    double radius;
    double PI  = 22/7;

public:
    
    /**
     * Constructor that returns a cylinder object
     * @param h - height of cylinder
     * @param r - radius of cylinder
     * @return Cylinder object
     */
    Cylinder(double h, double r){
        height = h;
        radius = r;
    }
    
    
    //Setters and Getters
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
    
    /**
     * Calculates the volume of a cylinder
     * @param - private properites of the cylinder class
     * @return - volume of cylinder as type double
     */
    double calculateVolume(){
        return PI*(radius*radius)*height;
    }

};