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

#include <iostream>

#include "TransitionPath.h"
#include "Timestep.h"
#include "Predicate.h"
#include "Config.h"

using namespace std;

namespace as2transition {

/**
 * @brief An exposed API for formatting answer sets using as2transition.
 */
class TransitionFormatter {
private:
	/*****************************************************************************************/
	/* Members */
	/*****************************************************************************************/
	 Config mConfig;			///< System configuration.

public:
	/*****************************************************************************************/
	/* Types */
	/*****************************************************************************************/

	/// A enum of the various user-exposed options.
	enum Option {
		OPT_FMT,						///< General format option. Pass "raw", "inner", "eql", or "short" as value.
										///< "raw" - Do not format predicates.
										///< "inner" - Strip h(), occ(), ab_h(), and ab_occ()
										///< "eql" - Write eql(c,v) as c=v
										///< "short" - Compress c=true and c=false to c and -c.
		
		OPT_SHOW_ALMOST_ALL,			///< Show all predicates.
		OPT_SHOW_ALL,					///< Show almost all predicates.

		OPT_SHOW_NEGATED,				///< show negated predicates (true, false).
		OPT_SHOW_CONTRIBS,				///< show contribution predicates (true, false).
		OPT_SHOW_XPREDS,				///< show x_ predicates (true, false).
		
		OPT_SEP_ACTIONS,				///< Separate actions from fluents (true, false).
		OPT_SEP_ABS,					///< Separate abnormalities from regular constants. (true, false).

		OPT_LINES,						///< Separate constants onto separate lines.
		OPT_NONE_ALIAS					///< Replace the provided value with 'none'.
	};


	/*****************************************************************************************/
	/* Constructors / Destructor */
	/*****************************************************************************************/
	/// Default Constructor
	inline TransitionFormatter()
	{ /* Intentionally left blank */ }

	/// Copy Constructor
	inline TransitionFormatter(TransitionFormatter const& other)
	{	mConfig = other.mConfig; }

	/// Destructor
	inline ~TransitionFormatter()
	{ /* Intentionally Left Blank */ }

	/*****************************************************************************************/
	/* Public Methods */
	/*****************************************************************************************/
	/// Gets the configuration instance for manipulation.
	inline Config& config() { return mConfig; }

	/// Gets the configuration instance for viewing
	inline Config const& config() const { return mConfig; }

	/// Display list of support command line arguments in the form of a help dialog.
	/// @param shorthand Whether to print short hand flags as well (these may conflict with your program).
	/// @param out The output stream to write to.
	static void help(std::ostream& out, bool shorthand = false);

	/// Parses a command line argument and sets the appropriate configuration option.
	/// @param opt The option to parse.
	/// @param shorthand Whether to recognize short hand flags as well (these may conflict with your program).
	/// @return True if the option was valid. False otherwise.
	bool parseOption(char const* opt, bool shorthand = false);

	/// Sets the provided user-exposed option.
	/// @param opt The option to set.
	/// @param val The value for the option (if required).
	/// @return True if the value was valid and the option has been set.
	bool setOption(Option opt, char const* val = NULL);
	
	/// Translates the answer set provided by the input stream and writes the corresponding
	/// transitional output to the output stream.
	/// @param in The input stream to read the answer set from.
	/// @param out The output stream to write the transition system to.
 	/// @param ignorenl True to indicate the answer set may span multiple lines (assumes that the answer set occupies the entire input stream).
	/// @param solver The type of solver that produced the answer set. Setting to unknown causes as2transition to operate in compatibility mode and uses best guesses.
	inline std::ostream& format(std::istream& in, std::ostream& out, bool ignorenl = false) const {
		TransitionPath* path = format(in, ignorenl);
		path->output(out);
		delete path;
		return out;
	}

	/// Translates the answer set provided by the input stream and returns the a data structure containing the resulting transition system.
	/// @param in The input stream to read the answer set from.
 	/// @param ignorenl True to indicate the answer set may span multiple lines (assumes that the answer set occupies the entire input stream).
	/// @param solver The type of solver that produced the answer set. Setting to unknown causes as2transition to operate in compatibility mode and uses best guesses.
	/// @return A pointer to a newly allocated data structure containing the resulting path.
	TransitionPath* format(std::istream& in, bool ignorenl = false) const;


private:
	/********************************************************************************************/
	/* Private Methods */
	/********************************************************************************************/

	/**
 	 * Reads characters from the input stream until either a complete token or a newline character has been read.
 	 * @param input The input stream to read from.
 	 * @param out The string to write the results to.
 	 * @param ws Whether we should preserve whitespace preceding the token (or newline).
	 * @return true if a newline was encoutered, false otherwise.
	 */
	static bool readTokenOrNewline(std::istream& input, std::string& out, bool ws = false);


};


}; /* end namespace as2transition */

