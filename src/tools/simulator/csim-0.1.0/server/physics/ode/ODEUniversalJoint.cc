/*
 *  Gazebo - Outdoor Multi-Robot Simulator
 *  Copyright (C) 2003
 *     Nate Koenig & Andrew Howard
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
/* Desc: A universal joint
 * Author: Nate Keonig, Andrew Howard
 * Date: 21 May 2003
 * CVS: $Id: ODEUniversalJoint.cc 7039 2008-09-24 18:06:29Z natepak $
 *
 * Modified by: Eurico Pedrosa <efp@ua.p>
 * Date: 10 Fev 2010
 *
 * Modification Notes
 *
 *  The modifications presented by me, have the purpose of
 *  removing the 'rendering' and 'gui' modules from the code base.
 *  The reasons behind this decision are simple, allow gazebo to run
 *  on computers with less gpu capabilities and lessen the the coupling
 *  between simulation and visualization.
 *
 */

#include "ODEUniversalJoint.hh"

using namespace gazebo;

//////////////////////////////////////////////////////////////////////////////
// Constructor
ODEUniversalJoint::ODEUniversalJoint( dWorldID worldId )
    : UniversalJoint<ODEJoint>()
{
  this->jointId = dJointCreateUniversal( worldId, NULL );
}

//////////////////////////////////////////////////////////////////////////////
// Destructor
ODEUniversalJoint::~ODEUniversalJoint()
{
}

//////////////////////////////////////////////////////////////////////////////
// Get the anchor point
Vector3 ODEUniversalJoint::GetAnchor(int /*index*/) const
{
  dVector3 result;
  this->physics->LockMutex();
  dJointGetUniversalAnchor( this->jointId, result );
  this->physics->UnlockMutex();

  return Vector3( result[0], result[1], result[2] );
}

//////////////////////////////////////////////////////////////////////////////
// Set the anchor point
void ODEUniversalJoint::SetAnchor( int /*index*/, const Vector3 &anchor )
{
  this->physics->LockMutex();
  dJointSetUniversalAnchor( this->jointId, anchor.x, anchor.y, anchor.z );
  this->physics->UnlockMutex();
}

//////////////////////////////////////////////////////////////////////////////
// Get the first axis of rotation
Vector3 ODEUniversalJoint::GetAxis(int index ) const
{
  dVector3 result;

  this->physics->LockMutex();
  if (index == 0)
    dJointGetUniversalAxis1( this->jointId, result );
  else
    dJointGetUniversalAxis2( this->jointId, result );
  this->physics->UnlockMutex();

  return Vector3( result[0], result[1], result[2] );
}

//////////////////////////////////////////////////////////////////////////////
// Set the first axis of rotation
void ODEUniversalJoint::SetAxis( int index, const Vector3 &axis )
{
  this->physics->LockMutex();
  if (index == 0)
    dJointSetUniversalAxis1( this->jointId, axis.x, axis.y, axis.z );
  else
    dJointSetUniversalAxis2( this->jointId, axis.x, axis.y, axis.z );
  this->physics->UnlockMutex();
}

//////////////////////////////////////////////////////////////////////////////
// Get the angle of an axis
Angle ODEUniversalJoint::GetAngle(int index) const
{
  Angle result;

  this->physics->LockMutex();
  if (index == 0)
    result = dJointGetUniversalAngle1( this->jointId );
  else
    result = dJointGetUniversalAngle2( this->jointId );
  this->physics->UnlockMutex();

  return result;
}

//////////////////////////////////////////////////////////////////////////////
// Get the angular rate of an axis
double ODEUniversalJoint::GetVelocity(int index) const
{
  double result;

  this->physics->LockMutex();
  if (index == 0)
    result = dJointGetUniversalAngle1Rate( this->jointId );
  else 
    result = dJointGetUniversalAngle2Rate( this->jointId );
  this->physics->UnlockMutex();
}
 
//////////////////////////////////////////////////////////////////////////////
/// Set the velocity of an axis(index).
void ODEUniversalJoint::SetVelocity(int index,double angle)
{
  if (index == 0)
    this->SetParam(dParamVel, angle);
  else
    this->SetParam(dParamVel2, angle);
}
 
//////////////////////////////////////////////////////////////////////////////
// Set the torque of this joint
void ODEUniversalJoint::SetForce(int index, double torque)
{
  this->physics->LockMutex();
  if (index == 0)
    dJointAddUniversalTorques( this->jointId, torque, 0);
  else
    dJointAddUniversalTorques( this->jointId, 0, torque);
  this->physics->UnlockMutex();
}

//////////////////////////////////////////////////////////////////////////////
/// Set the max allowed force of an axis(index).
void ODEUniversalJoint::SetMaxForce(int index, double t)
{
  if (index == 0)
    this->SetParam(dParamFMax, t);
  else
    this->SetParam(dParamFMax2, t);
}

//////////////////////////////////////////////////////////////////////////////
/// Get the max allowed force of an axis(index).
double ODEUniversalJoint::GetMaxForce(int index)
{
  if (index == 0)
    return this->GetParam(dParamFMax);
  else
    return this->GetParam(dParamFMax2);
}

//////////////////////////////////////////////////////////////////////////////
// Set the parameter to value
void ODEUniversalJoint::SetParam( int parameter, double value)
{
  this->physics->LockMutex();
  dJointSetUniversalParam( this->jointId, parameter, value );
  this->physics->UnlockMutex();
}


