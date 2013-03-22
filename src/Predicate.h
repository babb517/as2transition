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


#ifndef PREDICATE_DOT_H
#define PREDICATE_DOT_H

#include <climits> // For INT_MIN
#include <string>

#include "Config.h"
#include "StringUtils.h"

/**
 * The Predicate class represents an atom of a solution at a given time step.
 * It has member variables that store information about the atom's name and state,
 * and exposes static methods to evaluate strings for various signs of predicate-ness.
 */
class Predicate
{
  public:

	/// An enum providing a list of the possible predicate types we can encounter.
	enum Type { T_FLUENT, T_RIGID, T_ACTION, T_CONTRIB, T_STATIC_AB, T_DYNAMIC_AB, T_EQL, T_UNKNOWN };

	/// Special values for special time steps
	static int const RIGID_TIME = INT_MIN;


	/// Enum of the various types of equality that can be contained in the predicate
	enum EqlVal {
		HASEQL_NONE = 0,
		HASEQL_EQ,
		HASEQL_EQL
	};
	
	/**
	 * Constructor for a standard predicate which has no special formatting.
	 * @param name - The full name of the predicate.
	 */
	Predicate(std::string const& name)
		: name(name), timeStamp(RIGID_TIME), predType(T_UNKNOWN), hasEql(HASEQL_NONE), xpred(NULL), value("")
			{ /* Intentionally Left Blank */ }
	
	/**
	 * Constructor for a specially formatted predicate.
	 * @param predType - The type of predicate we are working with.
	 * @param name - The name of the predicate.
	 * @param timeStamp - The time at which the predicate is relevant.
	 * @param xpred - Whether the predicate's name is x_<name>, which marks it as an internal predicate.
	 * @param value - The (optional) value the predicate has taken. The empty string if the predicate doesn't have an eql() or eq() wrapper.
	 */
	inline Predicate(Type predType, std::string const& name, int timeStamp, bool xpred, std::string const& value = "")
		: name(name), timeStamp(timeStamp), predType(predType), hasEql((value != "") ? HASEQL_EQL : HASEQL_NONE), xpred(xpred), value(value)
		{ /* Intentionally Left Blank */ }
	
	/**
	 * Destructor. Here for completeness purposes, but does nothing.
	 */
	inline virtual ~Predicate() { /* Intentionally Left Blank */ };
	
	/**
	 * Accessor for name.
	 * @return The string name.
	 */
	inline std::string const& getName() const { return name; };
	
	/**
	 * Accessor for timeStamp.
	 * @return The current value of timeStamp.
	 */
	inline int getTimeStamp() const { return timeStamp; }

	/**
	 * Accessor for predType.
	 * @return The current value of predType.
	 */
	inline Type getType() const { return predType; }

	/**
	 * Accessor for value.
	 * @return The current value of value.
	 */
	inline std::string const& getValue() const { return value; }

	/**
	 * Accessor for xpred.
	 * @return The current value of xpred.
	 */
	inline bool isXPred() { return xpred; }

	/**
	 * Determines if the predicate appears to be boolean.
	 * @return True if the predicate value "true" or "false".
	 */
	inline bool isBool() { return isTrue() || isFalse(); }

	/**
	 * Determines if the predicate value is the reserved 'none' or 'false' keywords.
	 * @return True if the value is 'none' or 'false'.
	 */
	inline bool isNegative() { return isNone() || isFalse(); }

	/// Determines if the predicate's value is 'none'.
	inline bool isNone() { return value == sNoneValue; }

	/// Determines if the predicate's value is 'true'.
	inline bool isTrue() { return value == "true"; }

	/// DeterminEs if the predicate's value is 'false'.
	inline bool isFalse() { return value == "false"; }



	/**
	 * Accessor for hasEql.
	 * @return The current value of hasEql.
	 */
	inline EqlVal getHasEql() const { return hasEql; }
	
	/**
	 * Re-creates an appropriate string representation of the predicate and returns it.
	 * @param fmt - The formatting style to use.
	 * @return The appropriate string representation of the predicate.
	 */
	std::string toPredicateString(Config::Format fmt);
	
	/**
	 * Evaluates text to determine if it has a special prefix, such as "h(", "occ(", or "ab(" and returns that information.
	 * Assumes text is one complete predicate.
	 * @param text - The predicate to examine.
	 * @param outOffset - An optional offset that can be returned indicating the starting position after the prefix.
	 * @return The type of prefix we're looking at, or T_UNKNOWN.
	 */
	static Type getPrefixType(std::string const& text, size_t* outOffset = NULL);

	/**
	 * Attempts to extract relevant info from a specially formatted predicate in text.
	 * Assumes text is one complete predicate.
	 * @param text - The predicate to examine.
	 * @param outType - Set to the type of predicate that's within the text (T_UNKNOWN if we can't identify it or it's malformed).
	 * @param outHasEql - Set to true if the predicate has an eql(<name>,<value>) or eq(<name>,<value>) function wrapper.
	 * @param outName - The name of the predicate (text in the event we were unable to identify the predicate or the predicate is malformed).
	 * @param outXPred - Whether the predicate's name is of the form 'x_<pred>', which marks it as an internal predicate.
	 * @param outVal - The value the predicate has taken ("" if the predicate does not have an eql or eq function wrapper).
	 * @param outTime - The timestamp for the predicate. Set to RIGID_TIME if the predicate appears to be rigid.
	 */
	static void getPredInfo(std::string const& text, Type& outType, EqlVal& outHasEql, std::string& outName, bool& outXPred, std::string& outVal, int& outTime);

	/**
	 * Creates a predicate instance from a string containing the predicate.
	 * @param text A string containing the predicate.
	 * @return A new predicate instance based on the provided string.
	 */
	inline static Predicate* makePredicate(std::string const& text) {
		Predicate* ret = new Predicate("");
		// populate!
		getPredInfo(text, ret->predType, ret->hasEql, ret->name, ret->xpred, ret->value, ret->timeStamp);
		return ret;
	}

	/**
	 * Retrieves the appropriate prefix string given a predicate type.
	 * @param predType - The type of the predicate.
	 * @return A string containing the appropriate prefix for the predicate type.
	 */
	static std::string predTypeToPrefixString(Type predType);

	/**
	 * Sets the value that should be treated as 'none'.
	 * @param noneAlias the new alias for 'none'.
	 */
	inline static void setNoneAlias(std::string const& noneAlias)	{ sNoneValue = noneAlias; }

	/// Gets the value that's being treated as 'none'
	inline static std::string const& getNoneAlias()			{ return sNoneValue; }


  protected:
	std::string name; 		///< The full contents of the predicate (just the inner predicate if it was a specially formatted predicate).
	int timeStamp; 			///< The time stamp the predicate occurs in (if applicable). Possibly RIGID_TIME (if the predicate is rigid).
	Type predType;			///< The type of predicate that this instance represents.
	EqlVal hasEql;			///< True if the predicate has an eql(<name>,<value>) or eq(<name>,<value>) function wrapper, false otherwise.
	bool xpred;				///< True if the predicate's name has the form 'x_<name>', which marks it as an internal predicate.
	std::string value;		///< The value the predicate has taken, or "" if there is no function wrapper.
	

	static std::string sNoneValue;	///< The (possibly aliased) value that corresponds to a value of 'none'.
};

#endif // PREDICATE_DOT_H
