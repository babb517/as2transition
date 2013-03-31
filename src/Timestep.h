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

#include <climits> // For INT_MIN
#include <cstdlib> // For exit()
#include <iostream>
#include <list>
#include <string>

#include "Config.h"
#include "Predicate.h"

namespace as2transition {

/**
 * Holds information about the predicates that are true at a given time step.
 */
class Timestep 
{
private:
	/***************************************************************************/
	/* Members */
	/***************************************************************************/
	size_t mTime; 							///< The time step this structure represents in the solution.
	Config mConfig;						///< The configuration for the AS2Transition. Used to write out the timestep.

	
	std::list<Predicate*> mConstants;	///< Complete list of all constants associated with this timestep.

	std::list<Predicate*> mFluents; 	///< The fluents that are true at this time step.
	std::list<Predicate*> mStaticAbs; 	///< The static abnormalities that are exhibited at this time step.
	
	std::list<Predicate*> mActions; 	///< The actions that occurred in the next transition at this time step.
	std::list<Predicate*> mDynamicAbs; 	///< The dynamic abnormalities that occurred in the next transition.
public:

	/***************************************************************************/
	/* Types / Constants */
	/***************************************************************************/
	typedef std::list<Predicate*>::iterator iterator;
	typedef std::list<Predicate*>::const_iterator const_iterator;

	/// Time value to indicate that the timestep is not associated with a step in
	/// the transition system.
	static const size_t TIMELESS = Predicate::TIMELESS;


	/***************************************************************************/
	/* Constructors / Destructors */
	/***************************************************************************/

	/// Constructor.
	/// @param config The AS2Transition configuration used to format the timestep.
	/// @param time The time stamp associated with this timestep (or TIMELESS).
	inline Timestep(Config const& config, size_t time = TIMELESS)
		: mTime(time), mConfig(config)
	{ /* Intentionally left blank */ }
	
	/// Destructor.  Deallocated associated predicates.
	virtual inline ~Timestep() { 
		for (iterator it = mConstants.begin(); it != mConstants.end(); it++) delete *it;
	}
	
	/** 
	 * Accessor for timeStep.
	 * @return The value of timeStep.
	 */
	inline size_t time() const 							{ return mTime; }

	/**
	 * Mutator for timeStep.
	 * @param newTimeStep - The new value for timeStep.
	 */
	inline void time(size_t newTimeStep) 				{ mTime = newTimeStep; }
	
	/** 
	 * Adds a predicate to our list of predicates, creating a new Predicate object to hold the appropriate data.
	 * Automatically keeps the predicates sorted.
	 * @param newPredicate - The predicate object to add.
	 */
	void add(Predicate* newPredicate);
	
	/// Gets an iterator for the beginning of the list of all constants associated with the timestep.
	inline const_iterator begin() const 				{ return mConstants.begin(); }
	/// Gets an iterator for the end of the list of all constants associated with the timestep.
	inline const_iterator end() const 					{ return mConstants.end(); }
	/// Gets the number of constants in the timestep.
	inline size_t num() const							{ return mConstants.size(); }

	/// Gets an iterator for the beginning of the list of fluents in the timestep.
	inline const_iterator beginFluents() const 			{ return mFluents.begin(); }
	/// Gets an iterator for the end the list of fluents in the timestep.
	inline const_iterator endFluents() const 			{ return mFluents.end(); }
	/// Gets the number of fluents in the timestep.
	inline size_t numFluents() const					{ return mFluents.size(); }

	/// Gets an iterator for the beginning of the list of static abnormalities in the timestep.
	inline const_iterator beginStaticAbs() const 		{ return mStaticAbs.begin(); }
	/// Gets an iterator for the end the list of static abnormalities in the timestep.
	inline const_iterator endStaticAbs() const 			{ return mStaticAbs.end(); }
	/// Gets the number of static abnormalities in teh timestep
	inline size_t numStaticAbs() const					{ return mStaticAbs.size(); }
	

	/// Gets an iterator for the beginning of the list of actions occurring in the transition.
	inline const_iterator beginActions() const 			{ return mActions.begin(); }
	/// Gets an iterator for the beginning of the list of actions occurring in the transition.
	inline const_iterator endActions() const 			{ return mActions.end(); }
	/// Gets the number of actions in the timestep.
	inline size_t numActions()							{ return mActions.size(); }

	/// Gets an iterator for the beginning of the list of dynamnic abnormalities occurring in the transition.
	inline const_iterator beginDynamicAbs() const 		{ return mDynamicAbs.begin(); }
	/// Gets an iterator for the beginning of the list of dynamic abnormalities occurring in the transition.
	inline const_iterator endDynamicAbs() const 		{ return mDynamicAbs.end(); }
	/// Gets the number of dynamic abnormalities in the timestep.
	inline size_t numDynamicAbs() const					{ return mDynamicAbs.size(); }	

	/**
	 * Outputs the contents of this timestep to one or more output streams.
	 * @param out - The stream to output to.
	 * @return The number of predicates output in this timestep.
	 */
	size_t output( std::ostream& out ) const;

private:

	/// Simple method used to insert items into a sorted list.
	/// @param list The list to insert the item into.
	/// @param pred The item to insert.
	void insert(std::list<Predicate*>& list, Predicate* pred);

	/**
	 * Prints out the provided list and associated label (if anything would print) according to configuration policy.
	 * @param out The output stream to print to.
	 * @param list The list of predicates to print.
	 * @param lbl The label to print out (only prints if any of the predicates in the list would print according to the configuration.
	 * return The number of predicates printed.
	 */
	size_t print(std::ostream& out, std::list<Predicate*> const& list, char const* lbl = NULL) const;

};

/// Prints the step to the provided output strea
inline std::ostream& operator<<(std::ostream& lhs, Timestep const& rhs) { rhs.output(lhs); return lhs; }

}; /* end namespace as2transition */

