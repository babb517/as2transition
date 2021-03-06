/* Generated by re2c 0.13.6 on Wed Jul 30 20:41:48 2014 */
#line 1 "as2transition/TransitionFormatter.r2c"
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

#include <string>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cctype>

#include "babb/utils/memory.h"

#include "as2transition/TransitionFormatter.h"
#include "as2transition/TransitionPath.h"
#include "as2transition/Predicate.h"
#include "as2transition/parser/PredicateParser.h"
#include "as2transition/Config.h"

namespace u = babb::utils;

namespace as2transition {

/**
 * Checks if the provided string consists of just integers.
 * @param str The string to check.
 * @return True if str contains only [0-9].
 */
bool isIntegerString(std::string const& str) {
	char const* c_str = str.c_str();

	size_t sz = str.size();
	for (size_t i = 0; i < sz; i++) {
		if (!isdigit(c_str[i])) return false;
	} 
	return true;
}

void TransitionFormatter::help(std::ostream& out, bool shorthand) {
	out
		<< "  --format=FORMAT" << " OR --FORMAT " << ((shorthand) ? " OR -r / -i / -e / -s" : "")	<< std::endl 
		<< "         Specifies a format to use for each of the constants being output. FORMAT can "	<< std::endl
		<< "         be any of the following: "														<< std::endl
		<< "              raw   - Displays all constants as they appear from the solver."			<< std::endl
		<< "              inner - Strips and displays the inner <pre> from h(<pred>,<t>) style "	<< std::endl
		<< "                      (or similar), atoms."												<< std::endl
		<< "              eql   - Similar to 'inner' but also formats all inner eql(<c>,<v>) "		<< std::endl
		<< "                      (or eq(<c>,<v>)) as <c>=<v>."										<< std::endl
		<< "              short - Similar to 'eql' but also compresses boolean <c>=true and"		<< std::endl
		<< "                      <c>=false to c and -c, respectively. (Default Value.)"			<< std::endl
		  																							<< std::endl
		<< "  --all" << ((shorthand) ? " OR -a" : "")												<< std::endl
		<< "         Displays all positive predicates."												<< std::endl 
		<< "  --ALL" << ((shorthand) ? " OR -A" : "")												<< std::endl
		<< "   	      Displays all predicates, positive and negative." 								<< std::endl
		<< "  --negated[=true|false]" << ((shorthand) ? " OR -n" : "")								<< std::endl
		<< "         Sets whether to show negative constants which the value of 'none' or 'false'"	<< std::endl
		<< "  --strong-negation[=true|false]"														<< std::endl
		<< "         Sets whether to show predicates of the form -p."						 		<< std::endl
		<< "  --contribs[=true|false]" << ((shorthand) ? " OR -c" : "")								<< std::endl
		<< "         Sets whether to show formatted \"contribution\" and \"x_contrib\" constants"	<< std::endl
		<< "         which are used as intermediates for C+ additive constants."					<< std::endl
		<< "  --xpreds[=true|false]" << ((shorthand) ? " OR -x" : "")								<< std::endl
		<< "         Sets whether to show constants who's (inner) names begin with \"x_\" which"	<< std::endl
		<< "         are used as temporary constants in CPlus2ASP."									<< std::endl
																									<< std::endl 
		<< "  --separate-actions[=true|false]" 														<< std::endl
		<< "         Sets whether to show action constants in a separate section."					<< std::endl
		<< "  --separate-ext[=true|false]"															<< std::endl
		<< "         Sets whether to show external constants in a separate section."				<< std::endl
																									<< std::endl
		<< "  --strip-sanitization[=true|false]" << ((shorthand) ? " OR -z" : "")					<< std::endl
		<< "         Sets whether the sanitization prefixes saniConst_ and saniObj_ should be "		<< std::endl
		<< "         removed from in front of constants and objects, respectively."					<< std::endl
		<< "  --strip-prefix[=true|false]" << ((shorthand) ? " OR -p" : "")							<< std::endl
		<< "         Sets whether the non-reified constant prefixes (c_X_X, e_X_X, and o_) should "	<< std::endl
		<< "         be removed from in front of constants and objects."							<< std::endl
																									<< std::endl
		<< "  --line" << ((shorthand) ? " OR -l" : "")												<< std::endl
		<< "         Prints out each predicate on a separate line." 								<< std::endl
		<< "  --none=VALUE" << ((shorthand) ? " OR -n=VALUE" : "")									<< std::endl
		<< "          Sets [VALUE] to be treated as an alias for 'none'. Useful if 'none' has been"	<< std::endl
		<< "          replaced with an integer to circumvent a bug in Gringo 3.X.X's unification"	<< std::endl
		<< "          checking that sometimes prevents grounding." 									<< std::endl;
}

bool TransitionFormatter::parseOption(char const* opt, bool shorthand) {
	char const* marker = opt;
	char const* cursor = opt;

	
#line 112 "<stdout>"
	{
		char yych;
		unsigned int yyaccept = 0;

		yych = *cursor;
		switch (yych) {
		case '\n':	goto yy2;
		case '-':	goto yy3;
		default:	goto yy5;
		}
yy2:
		cursor = marker;
		switch (yyaccept) {
		case 0: 	goto yy4;
		case 1: 	goto yy27;
		case 2: 	goto yy39;
		case 3: 	goto yy51;
		case 4: 	goto yy90;
		case 5: 	goto yy97;
		case 6: 	goto yy115;
		case 7: 	goto yy129;
		default:	goto yy145;
		}
yy3:
		yyaccept = 0;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '-':	goto yy6;
		default:	goto yy4;
		}
yy4:
#line 148 "as2transition/TransitionFormatter.r2c"
		{ goto no_long_match; 													}
#line 146 "<stdout>"
yy5:
		yych = *++cursor;
		goto yy4;
yy6:
		yych = *++cursor;
		switch (yych) {
		case 'A':	goto yy13;
		case 'a':	goto yy12;
		case 'c':	goto yy15;
		case 'e':	goto yy10;
		case 'f':	goto yy7;
		case 'i':	goto yy9;
		case 'l':	goto yy17;
		case 'n':	goto yy14;
		case 'r':	goto yy8;
		case 's':	goto yy11;
		case 'x':	goto yy16;
		default:	goto yy2;
		}
yy7:
		yych = *++cursor;
		switch (yych) {
		case 'o':	goto yy161;
		default:	goto yy2;
		}
yy8:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy158;
		default:	goto yy2;
		}
yy9:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy153;
		default:	goto yy2;
		}
yy10:
		yych = *++cursor;
		switch (yych) {
		case 'q':	goto yy150;
		default:	goto yy2;
		}
yy11:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy69;
		case 'h':	goto yy70;
		case 't':	goto yy68;
		default:	goto yy2;
		}
yy12:
		yych = *++cursor;
		switch (yych) {
		case 'l':	goto yy65;
		default:	goto yy2;
		}
yy13:
		yych = *++cursor;
		switch (yych) {
		case 'L':	goto yy62;
		default:	goto yy2;
		}
yy14:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy45;
		case 'o':	goto yy44;
		default:	goto yy2;
		}
yy15:
		yych = *++cursor;
		switch (yych) {
		case 'o':	goto yy32;
		default:	goto yy2;
		}
yy16:
		yych = *++cursor;
		switch (yych) {
		case 'p':	goto yy22;
		default:	goto yy2;
		}
yy17:
		yych = *++cursor;
		switch (yych) {
		case 'i':	goto yy18;
		default:	goto yy2;
		}
yy18:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy19;
		default:	goto yy2;
		}
yy19:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy20;
		default:	goto yy2;
		}
yy20:
		++cursor;
#line 145 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::LINES);											}
#line 251 "<stdout>"
yy22:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy23;
		default:	goto yy2;
		}
yy23:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy24;
		default:	goto yy2;
		}
yy24:
		yych = *++cursor;
		switch (yych) {
		case 'd':	goto yy25;
		default:	goto yy2;
		}
yy25:
		yych = *++cursor;
		switch (yych) {
		case 's':	goto yy26;
		default:	goto yy2;
		}
yy26:
		yyaccept = 1;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '=':	goto yy28;
		default:	goto yy27;
		}
yy27:
#line 130 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_XPREDS, "true"); 		return true; 		}
#line 286 "<stdout>"
yy28:
		yych = *++cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy29;
		default:	goto yy2;
		}
yy29:
		++cursor;
		yych = *cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy29;
		default:	goto yy31;
		}
yy31:
#line 131 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_XPREDS, opt+strlen("--xpreds="));	 		}
#line 353 "<stdout>"
yy32:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy33;
		default:	goto yy2;
		}
yy33:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy34;
		default:	goto yy2;
		}
yy34:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy35;
		default:	goto yy2;
		}
yy35:
		yych = *++cursor;
		switch (yych) {
		case 'i':	goto yy36;
		default:	goto yy2;
		}
yy36:
		yych = *++cursor;
		switch (yych) {
		case 'b':	goto yy37;
		default:	goto yy2;
		}
yy37:
		yych = *++cursor;
		switch (yych) {
		case 's':	goto yy38;
		default:	goto yy2;
		}
yy38:
		yyaccept = 2;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '=':	goto yy40;
		default:	goto yy39;
		}
yy39:
#line 128 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_CONTRIBS, "true");					 		}
#line 400 "<stdout>"
yy40:
		yych = *++cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy41;
		default:	goto yy2;
		}
yy41:
		++cursor;
		yych = *cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy41;
		default:	goto yy43;
		}
yy43:
#line 129 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_CONTRIBS, opt+strlen("--contribs=")); 		}
#line 467 "<stdout>"
yy44:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy56;
		default:	goto yy2;
		}
yy45:
		yych = *++cursor;
		switch (yych) {
		case 'g':	goto yy46;
		default:	goto yy2;
		}
yy46:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy47;
		default:	goto yy2;
		}
yy47:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy48;
		default:	goto yy2;
		}
yy48:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy49;
		default:	goto yy2;
		}
yy49:
		yych = *++cursor;
		switch (yych) {
		case 'd':	goto yy50;
		default:	goto yy2;
		}
yy50:
		yyaccept = 3;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '=':	goto yy52;
		default:	goto yy51;
		}
yy51:
#line 124 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_NEGATED, "true");							}
#line 514 "<stdout>"
yy52:
		yych = *++cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy53;
		default:	goto yy2;
		}
yy53:
		++cursor;
		yych = *cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy53;
		default:	goto yy55;
		}
yy55:
#line 125 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_NEGATED, opt+strlen("--negated=")); 		}
#line 581 "<stdout>"
yy56:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy57;
		default:	goto yy2;
		}
yy57:
		yych = *++cursor;
		switch (yych) {
		case '=':	goto yy58;
		default:	goto yy2;
		}
yy58:
		yych = *++cursor;
		if (yych <= 0x00) goto yy2;
yy59:
		++cursor;
		yych = *cursor;
		if (yych >= 0x01) goto yy59;
#line 146 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::NONE_ALIAS,opt+strlen("--none="));				}
#line 603 "<stdout>"
yy62:
		yych = *++cursor;
		switch (yych) {
		case 'L':	goto yy63;
		default:	goto yy2;
		}
yy63:
		++cursor;
#line 122 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_ALL); 										}
#line 614 "<stdout>"
yy65:
		yych = *++cursor;
		switch (yych) {
		case 'l':	goto yy66;
		default:	goto yy2;
		}
yy66:
		++cursor;
#line 121 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_ALMOST_ALL); 								}
#line 625 "<stdout>"
yy68:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy102;
		default:	goto yy2;
		}
yy69:
		yych = *++cursor;
		switch (yych) {
		case 'p':	goto yy75;
		default:	goto yy2;
		}
yy70:
		yych = *++cursor;
		switch (yych) {
		case 'o':	goto yy71;
		default:	goto yy2;
		}
yy71:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy72;
		default:	goto yy2;
		}
yy72:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy73;
		default:	goto yy2;
		}
yy73:
		++cursor;
#line 119 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::FMT,"short");									}
#line 660 "<stdout>"
yy75:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy76;
		default:	goto yy2;
		}
yy76:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy77;
		default:	goto yy2;
		}
yy77:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy78;
		default:	goto yy2;
		}
yy78:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy79;
		default:	goto yy2;
		}
yy79:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy80;
		default:	goto yy2;
		}
yy80:
		yych = *++cursor;
		switch (yych) {
		case '-':	goto yy81;
		default:	goto yy2;
		}
yy81:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy83;
		case 'e':	goto yy82;
		default:	goto yy2;
		}
yy82:
		yych = *++cursor;
		switch (yych) {
		case 'x':	goto yy95;
		default:	goto yy2;
		}
yy83:
		yych = *++cursor;
		switch (yych) {
		case 'c':	goto yy84;
		default:	goto yy2;
		}
yy84:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy85;
		default:	goto yy2;
		}
yy85:
		yych = *++cursor;
		switch (yych) {
		case 'i':	goto yy86;
		default:	goto yy2;
		}
yy86:
		yych = *++cursor;
		switch (yych) {
		case 'o':	goto yy87;
		default:	goto yy2;
		}
yy87:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy88;
		default:	goto yy2;
		}
yy88:
		yych = *++cursor;
		switch (yych) {
		case 's':	goto yy89;
		default:	goto yy2;
		}
yy89:
		yyaccept = 4;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '=':	goto yy91;
		default:	goto yy90;
		}
yy90:
#line 133 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SEP_ACTIONS, "true");							}
#line 756 "<stdout>"
yy91:
		yych = *++cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy92;
		default:	goto yy2;
		}
yy92:
		++cursor;
		yych = *cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy92;
		default:	goto yy94;
		}
yy94:
#line 134 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SEP_ACTIONS, opt+strlen("--separate-actions="));	}
#line 823 "<stdout>"
yy95:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy96;
		default:	goto yy2;
		}
yy96:
		yyaccept = 5;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '=':	goto yy98;
		default:	goto yy97;
		}
yy97:
#line 136 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SEP_ABS, "true");								}
#line 840 "<stdout>"
yy98:
		yych = *++cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy99;
		default:	goto yy2;
		}
yy99:
		++cursor;
		yych = *cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy99;
		default:	goto yy101;
		}
yy101:
#line 137 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SEP_ABS, opt+strlen("--separate-abs="));		 	}
#line 907 "<stdout>"
yy102:
		yych = *++cursor;
		switch (yych) {
		case 'i':	goto yy103;
		case 'o':	goto yy104;
		default:	goto yy2;
		}
yy103:
		yych = *++cursor;
		switch (yych) {
		case 'p':	goto yy120;
		default:	goto yy2;
		}
yy104:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy105;
		default:	goto yy2;
		}
yy105:
		yych = *++cursor;
		switch (yych) {
		case 'g':	goto yy106;
		default:	goto yy2;
		}
yy106:
		yych = *++cursor;
		switch (yych) {
		case '-':	goto yy107;
		default:	goto yy2;
		}
yy107:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy108;
		default:	goto yy2;
		}
yy108:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy109;
		default:	goto yy2;
		}
yy109:
		yych = *++cursor;
		switch (yych) {
		case 'g':	goto yy110;
		default:	goto yy2;
		}
yy110:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy111;
		default:	goto yy2;
		}
yy111:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy112;
		default:	goto yy2;
		}
yy112:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy113;
		default:	goto yy2;
		}
yy113:
		yych = *++cursor;
		switch (yych) {
		case 'd':	goto yy114;
		default:	goto yy2;
		}
yy114:
		yyaccept = 6;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '=':	goto yy116;
		default:	goto yy115;
		}
yy115:
#line 126 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_STRONG_NEGATED, "true");					}
#line 991 "<stdout>"
yy116:
		yych = *++cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy117;
		default:	goto yy2;
		}
yy117:
		++cursor;
		yych = *cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy117;
		default:	goto yy119;
		}
yy119:
#line 127 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_STRONG_NEGATED, opt+strlen("--strong-negated="));}
#line 1058 "<stdout>"
yy120:
		yych = *++cursor;
		switch (yych) {
		case '-':	goto yy121;
		default:	goto yy2;
		}
yy121:
		yych = *++cursor;
		switch (yych) {
		case 'p':	goto yy123;
		case 's':	goto yy122;
		default:	goto yy2;
		}
yy122:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy134;
		default:	goto yy2;
		}
yy123:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy124;
		default:	goto yy2;
		}
yy124:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy125;
		default:	goto yy2;
		}
yy125:
		yych = *++cursor;
		switch (yych) {
		case 'f':	goto yy126;
		default:	goto yy2;
		}
yy126:
		yych = *++cursor;
		switch (yych) {
		case 'i':	goto yy127;
		default:	goto yy2;
		}
yy127:
		yych = *++cursor;
		switch (yych) {
		case 'x':	goto yy128;
		default:	goto yy2;
		}
yy128:
		yyaccept = 7;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '=':	goto yy130;
		default:	goto yy129;
		}
yy129:
#line 142 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::STRIP_PREFIX, "true");							}
#line 1118 "<stdout>"
yy130:
		yych = *++cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy131;
		default:	goto yy2;
		}
yy131:
		++cursor;
		yych = *cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy131;
		default:	goto yy133;
		}
yy133:
#line 143 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::STRIP_PREFIX, opt+strlen("--strip-prefix=")); }
#line 1185 "<stdout>"
yy134:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy135;
		default:	goto yy2;
		}
yy135:
		yych = *++cursor;
		switch (yych) {
		case 'i':	goto yy136;
		default:	goto yy2;
		}
yy136:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy137;
		default:	goto yy2;
		}
yy137:
		yych = *++cursor;
		switch (yych) {
		case 'i':	goto yy138;
		default:	goto yy2;
		}
yy138:
		yych = *++cursor;
		switch (yych) {
		case 'z':	goto yy139;
		default:	goto yy2;
		}
yy139:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy140;
		default:	goto yy2;
		}
yy140:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy141;
		default:	goto yy2;
		}
yy141:
		yych = *++cursor;
		switch (yych) {
		case 'i':	goto yy142;
		default:	goto yy2;
		}
yy142:
		yych = *++cursor;
		switch (yych) {
		case 'o':	goto yy143;
		default:	goto yy2;
		}
yy143:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy144;
		default:	goto yy2;
		}
yy144:
		yyaccept = 8;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '=':	goto yy146;
		default:	goto yy145;
		}
yy145:
#line 139 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::STRIP_SAN, "true");								}
#line 1256 "<stdout>"
yy146:
		yych = *++cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy147;
		default:	goto yy2;
		}
yy147:
		++cursor;
		yych = *cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy147;
		default:	goto yy149;
		}
yy149:
#line 140 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::STRIP_SAN, opt+strlen("--strip-sanitization=")); }
#line 1323 "<stdout>"
yy150:
		yych = *++cursor;
		switch (yych) {
		case 'l':	goto yy151;
		default:	goto yy2;
		}
yy151:
		++cursor;
#line 118 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::FMT,"eql"); 										}
#line 1334 "<stdout>"
yy153:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy154;
		default:	goto yy2;
		}
yy154:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy155;
		default:	goto yy2;
		}
yy155:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy156;
		default:	goto yy2;
		}
yy156:
		++cursor;
#line 117 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::FMT,"inner");									}
#line 1357 "<stdout>"
yy158:
		yych = *++cursor;
		switch (yych) {
		case 'w':	goto yy159;
		default:	goto yy2;
		}
yy159:
		++cursor;
#line 116 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::FMT,"raw");										}
#line 1368 "<stdout>"
yy161:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy162;
		default:	goto yy2;
		}
yy162:
		yych = *++cursor;
		switch (yych) {
		case 'm':	goto yy163;
		default:	goto yy2;
		}
yy163:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy164;
		default:	goto yy2;
		}
yy164:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy165;
		default:	goto yy2;
		}
yy165:
		yych = *++cursor;
		switch (yych) {
		case '=':	goto yy166;
		default:	goto yy2;
		}
yy166:
		yych = *++cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy167;
		default:	goto yy2;
		}
yy167:
		++cursor;
		yych = *cursor;
		switch (yych) {
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':	goto yy167;
		default:	goto yy169;
		}
yy169:
#line 115 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::FMT,opt+strlen("--format="));					}
#line 1465 "<stdout>"
	}
#line 149 "as2transition/TransitionFormatter.r2c"

no_long_match:
	if (!shorthand) return false;
	cursor = opt;
	marker = opt;

	
#line 1475 "<stdout>"
	{
		char yych;
		yych = *cursor;
		switch (yych) {
		case '\n':	goto yy172;
		case '-':	goto yy173;
		default:	goto yy175;
		}
yy172:
yy173:
		++cursor;
		switch ((yych = *cursor)) {
		case 'A':	goto yy188;
		case 'a':	goto yy190;
		case 'c':	goto yy184;
		case 'e':	goto yy194;
		case 'i':	goto yy196;
		case 'l':	goto yy176;
		case 'n':	goto yy186;
		case 'p':	goto yy178;
		case 'r':	goto yy198;
		case 's':	goto yy192;
		case 'x':	goto yy182;
		case 'z':	goto yy180;
		default:	goto yy174;
		}
yy174:
#line 174 "as2transition/TransitionFormatter.r2c"
		{ return false; }
#line 1505 "<stdout>"
yy175:
		yych = *++cursor;
		goto yy174;
yy176:
		++cursor;
#line 172 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::LINES);					}
#line 1513 "<stdout>"
yy178:
		++cursor;
#line 170 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::STRIP_PREFIX, "true");	}
#line 1518 "<stdout>"
yy180:
		++cursor;
#line 169 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::STRIP_SAN, "true"); 		}
#line 1523 "<stdout>"
yy182:
		++cursor;
#line 167 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_XPREDS,"true"); 	}
#line 1528 "<stdout>"
yy184:
		++cursor;
#line 166 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_CONTRIBS,"true");	}
#line 1533 "<stdout>"
yy186:
		++cursor;
#line 165 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_NEGATED,"true"); 	}
#line 1538 "<stdout>"
yy188:
		++cursor;
#line 163 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_ALL); 				}
#line 1543 "<stdout>"
yy190:
		++cursor;
#line 162 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::SHOW_ALMOST_ALL); 		}
#line 1548 "<stdout>"
yy192:
		++cursor;
#line 160 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::FMT,"short");	 		}
#line 1553 "<stdout>"
yy194:
		++cursor;
#line 159 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::FMT,"eql"); 				}
#line 1558 "<stdout>"
yy196:
		++cursor;
#line 158 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::FMT,"inner");			}
#line 1563 "<stdout>"
yy198:
		++cursor;
#line 157 "as2transition/TransitionFormatter.r2c"
		{ return setOption(Option::FMT,"raw"); 				}
#line 1568 "<stdout>"
	}
#line 175 "as2transition/TransitionFormatter.r2c"


}

// Sets the specified option
bool TransitionFormatter::setOption(Option::type opt, char const* val) {

	switch (opt) {
	case Option::FMT:
		if (!val)						return false;
		if (!strcmp(val,"raw")) 		config()->format(Config::PredFormat::RAW);
		else if (!strcmp(val, "inner"))config()->format(Config::PredFormat::INNER);
		else if (!strcmp(val, "eql")) 	config()->format(Config::PredFormat::EQL);
		else if (!strcmp(val, "short"))config()->format(Config::PredFormat::SHORT);
		else 							return false;
		return true;

	case Option::SHOW_ALL:
		config()->showmask(~0);
		return true;

	case Option::SHOW_ALMOST_ALL:
		config()->showmask(config()->showmask() | Config::PredType::CONTRIBUTION | Config::PredType::XPREDICATE);
		return true;

	case Option::SHOW_NEGATED:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config()->showmask(config()->showmask() | Config::PredType::NEGATIVE);
		else if (!strcmp(val,"false"))	config()->showmask(config()->showmask() & ~Config::PredType::NEGATIVE);
		else 							return false;
		return true;

	case Option::SHOW_STRONG_NEGATED:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config()->showmask(config()->showmask() | Config::PredType::STRONG_NEGATION);
		else if (!strcmp(val,"false"))	config()->showmask(config()->showmask() & ~Config::PredType::STRONG_NEGATION);
		else 							return false;
		return true;

	case Option::SHOW_CONTRIBS:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config()->showmask(config()->showmask() | Config::PredType::CONTRIBUTION);
		else if (!strcmp(val,"false"))	config()->showmask(config()->showmask() & ~Config::PredType::CONTRIBUTION);
		else 							return false;
		return true;

	case Option::SHOW_XPREDS:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config()->showmask(config()->showmask() | Config::PredType::XPREDICATE);
		else if (!strcmp(val,"false"))	config()->showmask(config()->showmask() & ~Config::PredType::XPREDICATE);
		else 							return false;
		return true;

	case Option::SEP_ACTIONS:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config()->separateActions(true);
		else if (!strcmp(val,"false"))	config()->separateActions(false);
		else 							return false;
		return true;

	case Option::SEP_ABS:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config()->separateExternal(true);
		else if (!strcmp(val,"false"))	config()->separateExternal(false);
		else 							return false;
		return true;

	case Option::STRIP_SAN:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config()->stripSanitization(true);
		else if (!strcmp(val,"false"))	config()->stripSanitization(false);
		else 							return false;
		return true;
	
	case Option::STRIP_PREFIX:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config()->stripPrefix(true);
		else if (!strcmp(val,"false"))	config()->stripPrefix(false);
		else 							return false;
		return true;

	case Option::LINES:
		config()->onePredPerLine(true);
		return true;

	case Option::NONE_ALIAS:
		config()->noneAlias(new ReferencedString(val));
		return true;

	default:
		return false;
	}
}



/**
 * Reads in and processes the answer set line(s) that are next in the provided stream.
 * @param in The in stream to read from.
 * @param output The output stream to write to.
 * @param solutionNum The current solution # we're working with.
 * @param config The system configuration.
 * @param nextToken The next token to be read.
 */
TransitionPath* TransitionFormatter::format(std::istream& in, bool ignorenl) const {
	TransitionPath* path = new TransitionPath(config());
	std::string token, tmp;
	
/*
	Config::Solver::type solver = config()->solver();

	// read next candidate token
	bool newline;
	newline = readTokenOrNewline(in, token);

	// Skip any answer set header...
	if (token == "Stable") {
		// smodels
		newline = readTokenOrNewline(in, token); // 'Models:'
		if (!newline) newline = readTokenOrNewline(in, token);
		if (solver == Config::Solver::UNKNOWN) solver = Config::Solver::SMODELS;
	} else if (token == "Answer") {
		// cmodels
		newline = readTokenOrNewline(in, token); // 'set:'
		if (!newline) newline = readTokenOrNewline(in, token);
		if (solver == Config::Solver::UNKNOWN) solver = Config::Solver::CMODELS;
	} else if (token[token.size()-1] == '.' && isIntegerString(token.substr(0,token.size()-1))) {
		// oclingo
		if(solver == Config::Solver::UNKNOWN) solver = Config::Solver::OCLINGO;
	}
*/

	// Read until we reach the next line.
	u::ref_ptr<parser::PredicateParser> parser = new parser::PredicateParser(in, true);
	parser->parse();

	// Transfer each of the predicates into the path...
	for (parser::PredicateParser::iterator it = parser->begin(); it != parser->end(); it++) {
		path->add(*it);
	}

	return path;
}



// Reads characters from the in stream until either a complete token or a newline character has been read.
bool TransitionFormatter::readTokenOrNewline(std::istream& in, std::string& out, bool ws) {
	char c;

	out = "";
	while (in.good() && isspace(in.peek())) {
		c = in.get();
		if (c == '\n') {
			out += c;
			return true;
		} else if (ws) {
			out += c;
		}
	}

	while (in.good() && !isspace(in.peek())) {
		out += in.get();
	}


	return false;
}
};
