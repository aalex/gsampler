/*##############################################################################
    File:       moveable.h
    Purpose:    Class that acts as a wrapper around a PAT holding some node 
    object, and provides functions to translate/rotate the object in the scene.
    This is a combination of the translator/rotator objects from the previous
    two tutorials, with the exception that there is no automatic algorithm to
    keep the object in motion. The transformation triggers must be performed
    externally, via some other class calling the proper functions of this class.
                
    Returns:    N/A
##############################################################################*/
#ifndef MOVABLE_H
#define MOVABLE_H
#include <osg/PositionAttitudeTransform>

//##############################################################################

class Movable{
public:
/*//////////////////////////////////////////////////////////////////////////////
    Default Constructor - Initialize the PAT that will be held by this class,
    as well initialize all facing variables to the initial value (0.0)
//////////////////////////////////////////////////////////////////////////////*/
    Movable(osg::PositionAttitudeTransform& pat);

/*//////////////////////////////////////////////////////////////////////////////
    Default Destructor - Empty
//////////////////////////////////////////////////////////////////////////////*/    
    ~Movable();

/*//////////////////////////////////////////////////////////////////////////////
    Functions used to translate the PAT by a certain amount.
//////////////////////////////////////////////////////////////////////////////*/
    void translate_x(float amount);
    void translate_y(float amount);
    void translate_z(float amount);

/*//////////////////////////////////////////////////////////////////////////////
    Functions used to rotate the PAT by a certain amount
//////////////////////////////////////////////////////////////////////////////*/
    void rotate_x(float amount);
    void rotate_y(float amount);
    void rotate_z(float amount);
    
private:

    /*
        The PAT holding our model we wish to control.
    */
    osg::PositionAttitudeTransform * _pat;
    
    /*
        Facing variables that range from 0 -> 360 degrees. These are used
        in determining how the model is rotated each time it is drawn. We must
        keep the 3 individual facings because the model will always have a 3D
        orientation in 3D space.
    */
    float _x_facing;
    float _y_facing;
    float _z_facing;
    
    //Utility function to ensure the facing parameter stays within 0 ->360
    void enforce_rotation_bounds(float& facing);
    
    //Utility function to update the PAT attitude after any rotate_[x|y|z](amount) call
    void update_rotation_attitude();
};
#endif
