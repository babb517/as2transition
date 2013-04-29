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

#include <list>

#include "Timestep.h"
#include "Predicate.h"

namespace as2transition {


// Adds a predicate to our list of predicates
void Timestep::add(Predicate* newPredicate)
{
	insert(mConstants, newPredicate);

	switch (newPredicate->type()) {
	case Predicate::T_STATIC_AB:
		insert(mStaticAbs, newPredicate);
		break;


	case Predicate::T_DYNAMIC_AB:
		insert(mDynamicAbs, newPredicate);
		break;

	case Predicate::T_CONTRIB:
	case Predicate::T_ACTION:
		insert(mActions, newPredicate);
		break;

	case Predicate::T_RIGID:
	case Predicate::T_UNKNOWN:
	case Predicate::T_FLUENT:
	default:
		insert(mFluents, newPredicate);
		break;
	}
}


// Simple method used to insert items into a sorted list.
void Timestep::insert(std::list<Predicate*>& list, Predicate* pred) {
	iterator it;
	for (it = list.begin(); it != list.end() && (*it)->name() <= pred->name(); it++);
	list.insert(it, pred);
}


size_t Timestep::output( std::ostream& out ) const {

	size_t counter = 0;

	if (time() == TIMELESS) {
		out << "\t";
	} else {
		// Output time step header and appropriate trailing whitespace.
		out << "\t" << time() << ": ";
	}


	counter += print(out, mFluents);

	if (!mConfig.separateActions) {
		counter += print(out, mActions);
	}	

	counter += print(out, mStaticAbs, 
		(mConfig.separateAbnormalities) ? "STATIC ABS" : NULL);

	if (mConfig.separateActions) {
		counter += print(out, mActions, "ACTIONS");
	}

	counter += print(out, mDynamicAbs, 
		(mConfig.separateAbnormalities) ? "DYNAMIC ABS" : NULL);

	out << std::endl;

	return counter;
}

// prints the provided list  and associated label.
size_t Timestep::print(std::ostream& out, std::list<Predicate*> const& list, char const* lbl) const {
	std::list<Predicate const*> tmp;
	size_t sz;
	
	// figure out which preds we will be printing.
	for (Predicate const* pred : list) {
		if (pred->xpred() && !mConfig.showXPredicates) continue;
		if (pred->negative(&mConfig.noneAlias) && !mConfig.showNegPredicates) continue;
		if (pred->isStrongNeg() && !mConfig.showStrongNegPredicates) continue;
		if (pred->type() == Predicate::T_CONTRIB && !mConfig.showContribPredicates) continue;
		tmp.push_back(pred);
	}


	if ((sz = tmp.size())) {
		// print the label.
		if (lbl) out << "\n\n\t" << lbl << ": ";

		// print the predicates
		for (Predicate const* pred : tmp) {
			out
				<< ((mConfig.onePredPerLine) ? "\n\t\t" : " ")
				<< pred->str(mConfig.predFormat, &mConfig.noneAlias) ;
		}

	}

	return sz;
}


}; /* end namespace as2transition */
