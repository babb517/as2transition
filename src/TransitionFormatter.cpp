/* Generated by re2c 0.13.5 on Sun Mar 31 01:32:17 2013 */
#line 1 "TransitionFormatter.re2c"
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

#include "TransitionFormatter.h"
#include "TransitionPath.h"
#include "Predicate.h"

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
		<< "         Displays all predicates, positive and negative." 								<< std::endl
		<< "  --negated[=true|false]" << ((shorthand) ? " OR -n" : "")								<< std::endl
		<< "         Sets whether to show negative constants which the value of 'none' or 'false'"	<< std::endl
		<< "  --contribs[=true|false]" << ((shorthand) ? " OR -c" : "")								<< std::endl
		<< "         Sets whether to show formatted \"contribution\" and \"x_contrib\" constants"	<< std::endl
		<< "         which are used as intermediates for C+ additive constants."					<< std::endl
		<< "  --xpreds[=true|false]" << ((shorthand) ? " OR -x" : "")								<< std::endl
		<< "         Sets whether to show constants who's (inner) names begin with \"x_\" which"	<< std::endl
		<< "         are used as temporary constants in CPlus2ASP."									<< std::endl
																									<< std::endl 
		<< "  --separate-actions[=true|false]" 														<< std::endl
		<< "         Sets whether to show action constants in a separate section."					<< std::endl
		<< "  --separate-abs[=true|false]"															<< std::endl
		<< "         Sets whether to show abnormality constants in a separate section."				<< std::endl
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

	
#line 97 "TransitionFormatter.cpp"
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
		case 4: 	goto yy85;
		case 5: 	goto yy95;
		}
yy3:
		yyaccept = 0;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '-':	goto yy6;
		default:	goto yy4;
		}
yy4:
#line 125 "TransitionFormatter.re2c"
		{ goto no_long_match; 													}
#line 128 "TransitionFormatter.cpp"
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
		case 'o':	goto yy111;
		default:	goto yy2;
		}
yy8:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy108;
		default:	goto yy2;
		}
yy9:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy103;
		default:	goto yy2;
		}
yy10:
		yych = *++cursor;
		switch (yych) {
		case 'q':	goto yy100;
		default:	goto yy2;
		}
yy11:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy68;
		case 'h':	goto yy69;
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
#line 122 "TransitionFormatter.re2c"
		{ return setOption(OPT_LINES);											}
#line 232 "TransitionFormatter.cpp"
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
#line 113 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_XPREDS, "true"); 		return true; 		}
#line 267 "TransitionFormatter.cpp"
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
#line 114 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_XPREDS, opt+strlen("--xpreds="));	 		}
#line 334 "TransitionFormatter.cpp"
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
#line 111 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_CONTRIBS, "true");					 		}
#line 381 "TransitionFormatter.cpp"
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
#line 112 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_CONTRIBS, opt+strlen("--contribs=")); 		}
#line 448 "TransitionFormatter.cpp"
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
#line 109 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_NEGATED, "true");							}
#line 495 "TransitionFormatter.cpp"
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
#line 110 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_NEGATED, opt+strlen("--negated=")); 		}
#line 562 "TransitionFormatter.cpp"
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
#line 123 "TransitionFormatter.re2c"
		{ return setOption(OPT_NONE_ALIAS,opt+strlen("--none="));				}
#line 584 "TransitionFormatter.cpp"
yy62:
		yych = *++cursor;
		switch (yych) {
		case 'L':	goto yy63;
		default:	goto yy2;
		}
yy63:
		++cursor;
#line 107 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_ALL); 										}
#line 595 "TransitionFormatter.cpp"
yy65:
		yych = *++cursor;
		switch (yych) {
		case 'l':	goto yy66;
		default:	goto yy2;
		}
yy66:
		++cursor;
#line 106 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_ALMOST_ALL); 								}
#line 606 "TransitionFormatter.cpp"
yy68:
		yych = *++cursor;
		switch (yych) {
		case 'p':	goto yy74;
		default:	goto yy2;
		}
yy69:
		yych = *++cursor;
		switch (yych) {
		case 'o':	goto yy70;
		default:	goto yy2;
		}
yy70:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy71;
		default:	goto yy2;
		}
yy71:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy72;
		default:	goto yy2;
		}
yy72:
		++cursor;
#line 104 "TransitionFormatter.re2c"
		{ return setOption(OPT_FMT,"short");									}
#line 635 "TransitionFormatter.cpp"
yy74:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy75;
		default:	goto yy2;
		}
yy75:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy76;
		default:	goto yy2;
		}
yy76:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy77;
		default:	goto yy2;
		}
yy77:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy78;
		default:	goto yy2;
		}
yy78:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy79;
		default:	goto yy2;
		}
yy79:
		yych = *++cursor;
		switch (yych) {
		case '-':	goto yy80;
		default:	goto yy2;
		}
yy80:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy81;
		default:	goto yy2;
		}
yy81:
		yych = *++cursor;
		switch (yych) {
		case 'b':	goto yy83;
		case 'c':	goto yy82;
		default:	goto yy2;
		}
yy82:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy90;
		default:	goto yy2;
		}
yy83:
		yych = *++cursor;
		switch (yych) {
		case 's':	goto yy84;
		default:	goto yy2;
		}
yy84:
		yyaccept = 4;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '=':	goto yy86;
		default:	goto yy85;
		}
yy85:
#line 119 "TransitionFormatter.re2c"
		{ return setOption(OPT_SEP_ABS, "true");								}
#line 707 "TransitionFormatter.cpp"
yy86:
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
		case 'z':	goto yy87;
		default:	goto yy2;
		}
yy87:
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
		case 'z':	goto yy87;
		default:	goto yy89;
		}
yy89:
#line 120 "TransitionFormatter.re2c"
		{ return setOption(OPT_SEP_ABS, opt+strlen("--separate-abs="));		 	}
#line 774 "TransitionFormatter.cpp"
yy90:
		yych = *++cursor;
		switch (yych) {
		case 'i':	goto yy91;
		default:	goto yy2;
		}
yy91:
		yych = *++cursor;
		switch (yych) {
		case 'o':	goto yy92;
		default:	goto yy2;
		}
yy92:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy93;
		default:	goto yy2;
		}
yy93:
		yych = *++cursor;
		switch (yych) {
		case 's':	goto yy94;
		default:	goto yy2;
		}
yy94:
		yyaccept = 5;
		yych = *(marker = ++cursor);
		switch (yych) {
		case '=':	goto yy96;
		default:	goto yy95;
		}
yy95:
#line 116 "TransitionFormatter.re2c"
		{ return setOption(OPT_SEP_ACTIONS, "true");							}
#line 809 "TransitionFormatter.cpp"
yy96:
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
		case 'z':	goto yy97;
		default:	goto yy2;
		}
yy97:
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
		case 'z':	goto yy97;
		default:	goto yy99;
		}
yy99:
#line 117 "TransitionFormatter.re2c"
		{ return setOption(OPT_SEP_ACTIONS, opt+strlen("--separate-actions="));	}
#line 876 "TransitionFormatter.cpp"
yy100:
		yych = *++cursor;
		switch (yych) {
		case 'l':	goto yy101;
		default:	goto yy2;
		}
yy101:
		++cursor;
#line 103 "TransitionFormatter.re2c"
		{ return setOption(OPT_FMT,"eql"); 										}
#line 887 "TransitionFormatter.cpp"
yy103:
		yych = *++cursor;
		switch (yych) {
		case 'n':	goto yy104;
		default:	goto yy2;
		}
yy104:
		yych = *++cursor;
		switch (yych) {
		case 'e':	goto yy105;
		default:	goto yy2;
		}
yy105:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy106;
		default:	goto yy2;
		}
yy106:
		++cursor;
#line 102 "TransitionFormatter.re2c"
		{ return setOption(OPT_FMT,"inner");									}
#line 910 "TransitionFormatter.cpp"
yy108:
		yych = *++cursor;
		switch (yych) {
		case 'w':	goto yy109;
		default:	goto yy2;
		}
yy109:
		++cursor;
#line 101 "TransitionFormatter.re2c"
		{ return setOption(OPT_FMT,"raw");										}
#line 921 "TransitionFormatter.cpp"
yy111:
		yych = *++cursor;
		switch (yych) {
		case 'r':	goto yy112;
		default:	goto yy2;
		}
yy112:
		yych = *++cursor;
		switch (yych) {
		case 'm':	goto yy113;
		default:	goto yy2;
		}
yy113:
		yych = *++cursor;
		switch (yych) {
		case 'a':	goto yy114;
		default:	goto yy2;
		}
yy114:
		yych = *++cursor;
		switch (yych) {
		case 't':	goto yy115;
		default:	goto yy2;
		}
yy115:
		yych = *++cursor;
		switch (yych) {
		case '=':	goto yy116;
		default:	goto yy2;
		}
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
#line 100 "TransitionFormatter.re2c"
		{ return setOption(OPT_FMT,opt+strlen("--format="));					}
#line 1018 "TransitionFormatter.cpp"
	}
#line 126 "TransitionFormatter.re2c"

no_long_match:
	if (!shorthand) return false;
	cursor = opt;
	marker = opt;

	
#line 1028 "TransitionFormatter.cpp"
	{
		char yych;
		yych = *cursor;
		switch (yych) {
		case '\n':	goto yy122;
		case '-':	goto yy123;
		default:	goto yy125;
		}
yy122:
yy123:
		++cursor;
		switch ((yych = *cursor)) {
		case 'A':	goto yy134;
		case 'a':	goto yy136;
		case 'c':	goto yy130;
		case 'e':	goto yy140;
		case 'i':	goto yy142;
		case 'l':	goto yy126;
		case 'n':	goto yy132;
		case 'r':	goto yy144;
		case 's':	goto yy138;
		case 'x':	goto yy128;
		default:	goto yy124;
		}
yy124:
#line 148 "TransitionFormatter.re2c"
		{ return false; }
#line 1056 "TransitionFormatter.cpp"
yy125:
		yych = *++cursor;
		goto yy124;
yy126:
		++cursor;
#line 146 "TransitionFormatter.re2c"
		{ return setOption(OPT_LINES);					}
#line 1064 "TransitionFormatter.cpp"
yy128:
		++cursor;
#line 144 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_XPREDS,"true"); 	}
#line 1069 "TransitionFormatter.cpp"
yy130:
		++cursor;
#line 143 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_CONTRIBS,"true");	}
#line 1074 "TransitionFormatter.cpp"
yy132:
		++cursor;
#line 142 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_NEGATED,"true"); 	}
#line 1079 "TransitionFormatter.cpp"
yy134:
		++cursor;
#line 140 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_ALL); 				}
#line 1084 "TransitionFormatter.cpp"
yy136:
		++cursor;
#line 139 "TransitionFormatter.re2c"
		{ return setOption(OPT_SHOW_ALMOST_ALL); 		}
#line 1089 "TransitionFormatter.cpp"
yy138:
		++cursor;
#line 137 "TransitionFormatter.re2c"
		{ return setOption(OPT_FMT,"short");	 		}
#line 1094 "TransitionFormatter.cpp"
yy140:
		++cursor;
#line 136 "TransitionFormatter.re2c"
		{ return setOption(OPT_FMT,"eql"); 				}
#line 1099 "TransitionFormatter.cpp"
yy142:
		++cursor;
#line 135 "TransitionFormatter.re2c"
		{ return setOption(OPT_FMT,"inner");			}
#line 1104 "TransitionFormatter.cpp"
yy144:
		++cursor;
#line 134 "TransitionFormatter.re2c"
		{ return setOption(OPT_FMT,"raw"); 				}
#line 1109 "TransitionFormatter.cpp"
	}
#line 149 "TransitionFormatter.re2c"


}

// Sets the specified option
bool TransitionFormatter::setOption(Option opt, char const* val) {

	switch (opt) {
	case OPT_FMT:
		if (!val)						return false;
		if (!strcmp(val,"raw")) 		config().predFormat = Format::FMT_RAW;
		else if (!strcmp(val, "inner"))	config().predFormat = Format::FMT_INNER;
		else if (!strcmp(val, "eql")) 	config().predFormat = Format::FMT_EQL;
		else if (!strcmp(val, "short"))	config().predFormat = Format::FMT_SHORT;
		else 							return false;
		return true;

	case OPT_SHOW_ALL:
		config().showNegPredicates = true;
		/* no break */

	case OPT_SHOW_ALMOST_ALL:
		config().showContribPredicates = true;
		config().showXPredicates = true;
		return true;

	case OPT_SHOW_NEGATED:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config().showNegPredicates = true;
		else if (!strcmp(val,"false"))	config().showNegPredicates = false;
		else 							return false;
		return true;

	case OPT_SHOW_CONTRIBS:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config().showContribPredicates = true;
		else if (!strcmp(val,"false"))	config().showContribPredicates = false;
		else 							return false;
		return true;

	case OPT_SHOW_XPREDS:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config().showXPredicates = true;
		else if (!strcmp(val,"false"))	config().showXPredicates = false;
		else 							return false;
		return true;

	case OPT_SEP_ACTIONS:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config().separateActions = true;
		else if (!strcmp(val,"false"))	config().separateActions = false;
		else 							return false;
		return true;

	case OPT_SEP_ABS:
		if (!val)						return false;
		if (!strcmp(val,"true"))		config().separateAbnormalities = true;
		else if (!strcmp(val,"false"))	config().separateAbnormalities = false;
		else 							return false;
		return true;

	case OPT_LINES:
		config().onePredPerLine = true;
		return true;

	case OPT_NONE_ALIAS:
		config().noneAlias = val;
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
	
	size_t num_dquote;
	size_t num_squote;
	size_t num_lparen;
	size_t num_rparen;
	
	Predicate* predTemp;

	Solver solver = config().solver;

	// read next candidate token
	bool newline;
	newline = readTokenOrNewline(in, token);

	// Skip any answer set header...
	if (token == "Stable") {
		// smodels
		newline = readTokenOrNewline(in, token); // 'Models:'
		if (!newline) newline = readTokenOrNewline(in, token);
		if (solver == SLVR_UNKNOWN) solver = SLVR_SMODELS;
	} else if (token == "Answer") {
		// cmodels
		newline = readTokenOrNewline(in, token); // 'set:'
		if (!newline) newline = readTokenOrNewline(in, token);
		if (solver == SLVR_UNKNOWN) solver = SLVR_CMODELS;
	} else if (token[token.size()-1] == '.' && isIntegerString(token.substr(0,token.size()-1))) {
		// oclingo
		if(solver == SLVR_UNKNOWN) solver = SLVR_OCLINGO;
	}


	// Read until we reach the next line.

	while (in.good() && (ignorenl || !newline)
			&& (solver != SLVR_OCLINGO || (token != "Step:" && token != "End")) /* oClingo online mode compatibility */) {

			while (newline && in.good()) 
				newline = readTokenOrNewline(in, token);

			// Figure out the next atom, ensuring that we have balanced ", ', (, ).
			// Assuming that the only time we have white space within the atom is
			// in a string literal we can just keep grabbing chunks until we have
			// something that appears to be balanced.
			// TODO: This assume no escape characters.
			num_dquote = std::count(token.begin(), token.end(), '"');
			num_squote = std::count(token.begin(), token.end(), '\'');
			num_lparen = std::count(token.begin(), token.end(), '(');
			num_rparen = std::count(token.begin(), token.end(), ')');

			while ((num_dquote % 2 
				|| num_squote % 2
				|| num_lparen != num_rparen) && in.good()) {

				// get the next token.
				newline = readTokenOrNewline(in, tmp, true);
				token += tmp;

				num_dquote += std::count(tmp.begin(), tmp.end(), '"');
				num_squote += std::count(tmp.begin(), tmp.end(), '\'');
				num_lparen += std::count(tmp.begin(), tmp.end(), '(');
				num_rparen += std::count(tmp.begin(), tmp.end(), ')');
			}


			if (!in.good()) break;
			// At this point we have what appears to be a complete atom. Process it.

			// extract the predicate
			predTemp = Predicate::makePredicate(token);
			
			// Add the predicate to the appropriate step
			path->add(predTemp);

			// next token
			newline = readTokenOrNewline(in, token);
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