/* 
 * Copyright (c) 2010-2013 <Joseph Babb, Michael Cassollary, Joohyung Lee>
 *
 * For information on how to contact the authors, please visit
 *	http://reasoning.eas.asu.edu/cplus2asp
 *
 * This file is part of the cplus2asp system.
 *
 * cplus2asp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cplus2asp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <vector>

#include "Timestep.h"
#include "Config.h"

namespace as2transition {

/**
 * @brief Represents a path through a transition system consisting of a number of timesteps 
 * (with assoicated states / actions / abnormalities) 
 */
class TransitionPath {
private:
	/**************************************************************************************/
	/* Members */
	/**************************************************************************************/
	Config mConfig;								///< System configuration.
	std::vector<Timestep*> mSteps;				///< The steps in the transition.
	Timestep mTimeless;

public:
	/**************************************************************************************/
	/* Types / Constants */
	/**************************************************************************************/
	typedef std::vector<Timestep*>::iterator iterator;
	typedef std::vector<Timestep*>::const_iterator const_iterator;

	static size_t const TIMELESS = Timestep::TIMELESS;

	/**************************************************************************************/
	/* Constructors / Destructors */
	/**************************************************************************************/
	/// Basic Constructor.
	inline TransitionPath(Config const& config)
		: mConfig(config), mTimeless(config)
	{ /* Intentionally left blank */ }

	/// Basic Destructor.
	inline ~TransitionPath()
	{ /* Intentionally Left Blank */ 
		for (Timestep* ts : *this)
			delete ts;
	}

	/**************************************************************************************/
	/* Methods */
	/**************************************************************************************/
	/// Gets an iterator pointing to the beginning of the path
	inline iterator begin()						{ return mSteps.begin(); }
	inline const_iterator begin() const			{ return mSteps.begin(); }

	/// Gets an iterator pointing to the end of the path.
	inline iterator end()						{ return mSteps.end(); }
	inline const_iterator end() const			{ return mSteps.end(); }

	/// Gets the number of steps in the path
	inline size_t length() const				{ return mSteps.size(); }

	/// Gets the specified timestep in the path (or NULL).
	inline Timestep* step(size_t t) { 
		if (t == TIMELESS) return &mTimeless; 
		else return (t < length()) ? mSteps[t] : NULL;
	}

	inline Timestep const* step(size_t t) const { 
		if (t == TIMELESS) return &mTimeless; 
		else return (t < length()) ? mSteps[t] : NULL;
	}

	/// Adds the predicate to the path at the appropriate timestep, creating it if neccessary.
	/// @param pred The predicate to add.
	/// @return True if the predicate resulted in a new time step being created.
	bool add(Predicate* pred);

	/// Prints the path to the provided output stream.
	/// @param out The output stream to print to.
	/// @return out
	std::ostream& output(std::ostream& out) const;

};

/// Prints the path to the provided output strea
inline std::ostream& operator<<(std::ostream& lhs, TransitionPath const& rhs) { return rhs.output(lhs); }

}; /* end namesapce as2transition */

