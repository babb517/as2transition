#include <string>
#include <iostream>

#include "babb/utils/memory.h"
#include "memwrappers.h"
#include "as2transition/parser/lemon_parser.h"
#include "as2transition/parser/PredicateParser.h"


namespace u = babb::utils;

// parser functions
void*       lemon_parserAlloc(void* (*mallocProc)(size_t));
void*       lemon_parserFree(void* yyp, void (*freeProc)(void*));
void        lemon_parser(void* yyp, int tokentype, ReferencedString const* token, as2transition::parser::PredicateParser* parser);
int         lemon_parserPreInject(void* yyp, int pop, ReferencedString const** token);
void		lemon_parserAttemptReduce(void* yyp, as2transition::parser::PredicateParser* parser);
#ifndef NDEBUG
void 		lemon_parserTrace(FILE *TraceFILE, char const*zTracePrompt);
#endif

namespace as2transition {
namespace parser {



PredicateParser::PredicateParser(std::istream& input, bool stopnewline)
	: _stat(Status::READY) {
	_scanner = new Scanner(input, stopnewline);
	_parser = lemon_parserAlloc(malloc);
}

PredicateParser::~PredicateParser() {
	lemon_parserFree(_parser, free);
}


PredicateParser::Status::type PredicateParser::parse() {
	ReferencedString* token;
	int tcode;

	if (_stat == Status::FINISHED) return _stat;


	// parse the list...
	do {
		tcode = _scanner->readToken(token);

		switch (tcode) {

		case T_ERR_UNTERMINATED_STRING:
			_parse_error("Unexpected end of input. Unterminated string.");
			break;
		
		case T_EOF:
			lemon_parser(_parser, tcode, token, this);
			lemon_parserAttemptReduce(_parser, this);
			_stat = Status::FINISHED;
			break;

		default:
			lemon_parser(_parser, tcode, token, this);
			break;
		} 
	} while (_stat == Status::READY);

	return _stat;
}



void PredicateParser::_parse_error(std::string const& error) {
	std::cerr << "ERROR: " << error << std::endl;
	_stat = Status::SYNTAX_ERR;
}

}}
