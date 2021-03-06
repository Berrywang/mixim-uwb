/* -*- mode:c++ -*- ********************************************************
 * file:        Move.h
 *
 * author:      Andreas Koepke, Michael Swigulski
 *
 * copyright:   (C) 2005, 2010 Telecommunication Networks Group (TKN) at
 *              Technische Universitaet Berlin, Germany.
 *
 *              This program is free software; you can redistribute it
 *              and/or modify it under the terms of the GNU General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later
 *              version.
 *              For further information see file COPYING
 *              in the top level directory
 ***************************************************************************
 * part of:     framework implementation developed by tkn
 **************************************************************************/

#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <cmath>
#include <cassert>

#include <omnetpp.h>

#include "Coord.h"
#include "BaseUtility.h"
#include "ImNotifiable.h"

/**
 * @brief Class to store object position and movement
 *
 * @ingroup baseUtils
 * @ingroup utils
 * @ingroup blackboard
 *
 * @author Andreas Koepke, Michael Swigulski
 **/
class Move : public BBItem {

    BBITEM_METAINFO(BBItem);

protected:
    /** @brief Start position of the host (in meters)**/
    Coord startPos;
    /** @brief start time at which host started at startPos **/
    simtime_t startTime;
    /** @brief direction the host is moving to, must be normalized **/
    Coord direction;
    /** speed of the host in meters per second **/
    double speed;

public:
	double getSpeed() const
	{
		return speed;
	}

	void setSpeed(double speed)
	{
		this->speed = speed;
	}

	const Coord& getStartPos() const
	{
		return startPos;
	}

	simtime_t getStartTime() const
	{
		return startTime;
	}

	/**
	 * @brief Sets start-position and start-time
	 */
	void setStart(const Coord& startPos, simtime_t startTime)
	{
		this->startPos = startPos;
		this->startTime = startTime;
	}

	/**
	 * @brief Sets start-position to passed value and start-time to current simulation-time
	 */
	void setStart(const Coord& startPos)
	{
		setStart(startPos, simTime());
	}

	const Coord& getDirection() const
	{
		return direction;
	}

	/**
	 * @brief Sets the direction from a passed vector,
	 * which must be already normalized or 0.
	 */
	void setDirectionByVector(const Coord& direction)
	{
		assert(	FWMath::close(direction.squareLength(), 1.0)
				|| FWMath::close(direction.squareLength(), 0.0));
		this->direction = direction;
	}

	/**
	 * @brief Sets the normalized direction from a passed target.
	 */
	void setDirectionByTarget(const Coord& target) {

    	double d = startPos.distance( target );
	    direction = (target - startPos) / d;

        //double d = sqrt(dir.x*dir.x + dir.y*dir.y);
        //direction.x = dir.x/d;
        //direction.y = dir.y/d;
    }

    /*
     * @brief Returns the position of the Move (Host) at the specified point in time.
     * It is intended to be passed simTime() as actualTime and returns the actual position.
     *
     * Assumes that direction represents a normalized vector (length equals 1.0).
     * Further this function does not check whether the given time point is before
     * the startTime of the actual move pattern. So in this case one might obtain
     * an unintended result.
     *
     */
    virtual Coord getPositionAt(simtime_t actualTime) const
    {
    	// if speed is very close to 0.0, the host is practically standing still
    	if ( FWMath::close(speed, 0.0) ) return startPos;

    	// otherwise: actualPos = startPos + ( direction * v * t )
    	return startPos + ( direction * speed * SIMTIME_DBL(actualTime - startTime) );
    }

public:

    std::string info() const {
        std::ostringstream ost;
        ost << " HostMove "
            << " startPos: " << startPos.info()
            << " direction: " << direction.info()
            << " startTime: " << startTime
            << " speed: " << speed;
        return ost.str();
    }
};

#endif

