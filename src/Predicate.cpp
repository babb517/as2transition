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


#include <cstring>
#include <iostream>

#include "Predicate.h"
#include "Config.h"

namespace as2transition {

// Re-creates an appropriate string representation of the predicate and returns it.
std::string Predicate::str(Format fmt) const
{
	std::string stripped_name, stripped_value;

	// Strip the 'saniConst_' from the constant.
	if (name().find("saniConst_") == 0) {
		stripped_name = name().substr(10);
	} else {
		stripped_name = name();
	}
	
	// Strip the 'saniObj_' from each of the objects in the name.
	size_t pos; 
	while ((pos = stripped_name.find("saniObj_")) != std::string::npos) {
		stripped_name.replace(pos, 8, "");
	}

	// Strip the 'saniObj_' from the value.
	if (value().find("saniObj_") == 0) {
		stripped_value= value().substr(8);
	} else {
		stripped_value = value();
	}


	// Most of the special formatting only happens to special predicates, so check that first.
	if(type() == T_UNKNOWN) {
		return stripped_name;
	}

	switch (fmt) {
	case FMT_SHORT:
		if (boolean())
			return (isFalse() ? "-" : "") + stripped_name;

		/* no break */
	case FMT_EQL:
		if (hasEql())
			return stripped_name + "=" + stripped_value;
		else return stripped_name;

	case FMT_INNER:
		switch (hasEql()) {
		case HASEQL_EQL:	return "eql(" + stripped_name + ", " + stripped_value + ")";
		case HASEQL_EQ:		return "eq("  + stripped_name + ", " + stripped_value + ")";
		case HASEQL_NONE:	return stripped_name;
		}
		

	case FMT_RAW:
	default:
		std::stringstream ret;

		ret << predTypeToPrefixString(type());


		switch (hasEql()) {
		case HASEQL_EQ:
			ret << "eq("  << stripped_name << ", " << stripped_value << ")";
			break;
		case HASEQL_EQL:
			ret << "eql(" << stripped_name << ", " << stripped_value << ")";
			break;
		case HASEQL_NONE: 
			ret << stripped_name;
			break;
		}

		if (type() != T_RIGID && type() != T_UNKNOWN) {

			if (type() != T_RIGID && time() != TIMELESS) {
				ret << ", " << time();
			}

			ret << ")";
		}

		return ret.str();
	}

}


Predicate::Type Predicate::getPrefixType(std::string const& text, size_t* outOffset) {
	std::string trimStr = StringUtils::trimWhitespace(text);
	char const* tempStr = trimStr.c_str();

	// check the prefix
	if (trimStr.size() >= 2 && !strncmp(tempStr,"h(",2)) {
		if (outOffset) *outOffset = 2;
		return T_FLUENT;
	} else if (trimStr.size() >= 2 && !strncmp(tempStr, "o(",2)) {
		if (outOffset) *outOffset = 2;
		return T_ACTION;
	} else if (trimStr.size() >= 4 && !strncmp(tempStr,"occ(",4)) {
		if (outOffset) *outOffset = 4;
		return T_ACTION;
	} else if (trimStr.size() >= 5 && !strncmp(tempStr,"ab_h(",5)) {
		if (outOffset) *outOffset = 5;
		return T_STATIC_AB;
	} else if (trimStr.size() >= 5 && !strncmp(tempStr,"ab_o(",7)) {
		if (outOffset) *outOffset = 5;
		return T_DYNAMIC_AB;
	} else if (trimStr.size() >= 7 && !strncmp(tempStr,"ab_occ(",7)) {
		if (outOffset) *outOffset = 7;
		return T_DYNAMIC_AB;
	} else if ((trimStr.size() >= 3 && !strncmp(tempStr, "eq(", 3))
		|| (trimStr.size() >= 4 && !strncmp(tempStr, "eql(", 4))) {
		if (outOffset) *outOffset = 0; // 0 offset so we can reparse the eql.
		return T_RIGID;
	} else {
		// This isn't a specially formatted predicate, we give up.
		if (outOffset) *outOffset = 0;
		return T_UNKNOWN;
	}
}

void Predicate::getPredInfo(std::string const& text, Type& outType, EqlVal& outHasEql, std::string& outName, bool& outXPred, std::string& outVal, size_t& outTime)
{
	// Intermediate results
	std::string tmpName;

	size_t curpos = 0;
	size_t offset = 0;
	size_t size;

	std::string trimStr = StringUtils::trimWhitespace(text);
	char const* tempStr = trimStr.c_str();
	size = trimStr.size();

	
	outType = getPrefixType(trimStr, &offset);

	curpos += offset;

	// we don't want to try if we don't know the type.
	if (outType == T_UNKNOWN) {
		outType = T_UNKNOWN;
		outHasEql = HASEQL_NONE;
		outName = trimStr;
		outVal = "";
		outTime = TIMELESS;
		return;
	}


	// If we're still here then we still have work to do. Lets keep working

	// check the function specifier
	if (size - curpos >= 3 && !strncmp(tempStr + curpos, "eq(", 3)) {
		outHasEql = HASEQL_EQ;
		curpos += 3;
	} else if (size - curpos >= 4 && !strncmp(tempStr + curpos, "eql(", 4)) {
		outHasEql = HASEQL_EQL;
		curpos += 4;
	} else {
		outHasEql = HASEQL_NONE;
	}


	// Let's check to see if this is really a contribution predicate...
	if (outType == T_ACTION &&
			((size - curpos >= 10 && !strncmp(tempStr + curpos, "x_contrib(",10))
					|| (size - curpos >= 13 && !strncmp(tempStr + curpos, "contribution(",13))))
	{
			outType = T_CONTRIB;
	}

	// We also should verify whether this is an x_pred.
	if ((size - curpos >= 2 && !strncmp(tempStr + curpos, "x_", 2))) {
		outXPred = true;
	} else {
		outXPred = false;
	}


	// get the base name.
	offset = (size_t)(StringUtils::scanAndMatchParens(tempStr + curpos, ',', size - curpos) - (tempStr + curpos));

	// check to make sure we found it!
	if (offset < 1) {
		outType = T_UNKNOWN;
		outHasEql = HASEQL_NONE;
		outName = trimStr;
		outVal = "";
		outTime = TIMELESS;
		return;
	}

	// endpos is now pointing the comma right after the atom name
	outName = StringUtils::trimWhitespace(trimStr.substr(curpos, offset));

	// start after the comma...
	curpos += offset + 1;

	if (outHasEql) {
		// if the predicate has an eql() wrapper, then we want to get the value it's equal to.

		offset = (size_t)(StringUtils::scanAndMatchParens(tempStr + curpos, ')', size - curpos) - (tempStr + curpos));

		// make sure we found something...
		if (offset < 1) {
			outType = T_UNKNOWN;
			outHasEql = HASEQL_NONE;
			outName = trimStr;
			outVal = "";
			outTime = TIMELESS;
			return;
		}
		outVal = StringUtils::trimWhitespace(trimStr.substr(curpos, offset));

		// skip the ")"
		curpos += offset + 1;

	} else {
		// Doesn't have an eql(), so we don't bother unwrapping the value.
		outVal = "";
	}

	// skip the comma if it exists...
	if (*(tempStr + curpos) == ',') curpos++;

	if (outType == T_RIGID) {
		outTime = TIMELESS;
	} else {
		// last but not least, find ourselves the time
		offset = (size_t)(StringUtils::scanAndMatchParens(tempStr + curpos, ')', size - curpos) - (tempStr + curpos));

		// make sure we found something...


		if (offset == 0 && outType == T_FLUENT) {
			// special case: we're looking at a rigid predicate.
			outTime = TIMELESS;

		} else if (offset < 1) {
			outType = T_UNKNOWN;
			outHasEql = HASEQL_NONE;
			outName = trimStr;
			outVal = "";
			outTime = TIMELESS;
			return;
		} else if (!StringUtils::from_string<size_t>(outTime, StringUtils::trimWhitespace(trimStr.substr(curpos, offset)))) {
			// can't convert to an integer time.
			outTime = TIMELESS;
		}
	}

	return;
}

std::string Predicate::predTypeToPrefixString(Type type) {
	switch (type) {
	case T_FLUENT:
		return "h(";
	case T_ACTION:
	case T_CONTRIB:
		return "occ(";
	case T_STATIC_AB:
		return "ab_(";
	case T_DYNAMIC_AB:
		return "ab_occ(";
	case T_RIGID:
	case T_UNKNOWN:
	default:
		return "";
	}
}

}; /* end namsepace as2transition */


