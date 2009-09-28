#include "movable.h"
////////////////////////////////////////////////////////////////////////////////
Movable::
Movable(osg::PositionAttitudeTransform& pat):
    _pat(&pat),
    _x_facing(0.0),     //Set the initial facings to be 0 (default)
    _y_facing(0.0),
    _z_facing(0.0)
{}
////////////////////////////////////////////////////////////////////////////////
Movable::
~Movable(){}
////////////////////////////////////////////////////////////////////////////////
/*
    Simple Vector addition to translate the PAT. Add the new amount to the old
    position vector to obtain the new offset. Applies for all 3 translate functions.
*/
void Movable::
translate_x(float amount){
    /*
        Set the new position to be the sum of a vec3d offset coordinate from center
        and the old position
    */
    _pat->setPosition(
        osg::Vec3d(amount, 0, 0) += _pat->getPosition()
    );
}
////////////////////////////////////////////////////////////////////////////////
void Movable::
translate_y(float amount){
    /*
        Set the new position to be the sum of a vec3d offset coordinate from center
        and the old position
    */
    _pat->setPosition(
        osg::Vec3d(0, amount, 0) += _pat->getPosition()
    );
}
////////////////////////////////////////////////////////////////////////////////
void Movable::
translate_z(float amount){
    /*
        Set the new position to be the sum of a vec3d offset coordinate from center
        and the old position
    */
    _pat->setPosition(
        osg::Vec3d(0, 0, amount) += _pat->getPosition()
    );
}
////////////////////////////////////////////////////////////////////////////////
void Movable::
rotate_x(float amount){
    //Increment the facing
    _x_facing += amount;
    
    //Check facing bounds
    enforce_rotation_bounds(_x_facing);
    
    //Update the attitude
    update_rotation_attitude();
}
////////////////////////////////////////////////////////////////////////////////
void Movable::
rotate_y(float amount){

    //Increment the facing
    _y_facing += amount;
    
    //Check facing bounds
    enforce_rotation_bounds(_y_facing);
    
    //Update the attitude
    update_rotation_attitude();
}
////////////////////////////////////////////////////////////////////////////////
void Movable::
rotate_z(float amount){

    //Increment the facing
    _z_facing += amount;
    
    //Check facing bounds
    enforce_rotation_bounds(_z_facing);
    
    //Update the attitude
    update_rotation_attitude();
}
////////////////////////////////////////////////////////////////////////////////
void Movable::
enforce_rotation_bounds(float& facing){

    /*
        Check the bounds to be between 0 and 360 - enforce bounds if not
        Handles facing becoming too large
    */
    if(facing > 360.0){
        facing = 0.0;
    }
    /*
        Also works in reverse... if the facing becomes too small
    */
    else if(facing < 0.0){
        facing = 360.0;
    }
}
////////////////////////////////////////////////////////////////////////////////
void Movable::
update_rotation_attitude(){

    /*
        Update the attitude with a new Quat based on the x y z facing values.
        Though it is probable that only one of the facings actually changed, we
        don't need to worry about rotating with the others, as they will not 
        change the facing.
    */
    _pat->setAttitude(
        osg::Quat(
    		osg::DegreesToRadians(_x_facing), osg::Vec3d(1.0, 0.0, 0.0),
    		osg::DegreesToRadians(_y_facing), osg::Vec3d(0.0, 1.0, 0.0),
    		osg::DegreesToRadians(_z_facing), osg::Vec3d(0.0, 0.0, 1.0)
	    )
    );
}
////////////////////////////////////////////////////////////////////////////////
