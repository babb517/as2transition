include Makefile.shared

as2transincludedir = $(includedir)/as2transition


lib_LIBRARIES = libas2transition.a
bin_PROGRAMS = as2transition

as2transinclude_HEADERS = \
	TransitionFormatter.h \
	TransitionPath.h \
	Predicate.h \
	StringUtils.h \
	Config.h \
	Timestep.h

BUILT_SOURCES = \
	TransitionFormatter.cpp

libas2transition_a_SOURCES = \
	TransitionFormatter.cpp \
	TransitionPath.cpp \
	Timestep.cpp \
	Predicate.cpp \
	StringUtils.cpp 


as2transition_SOURCES = \
	main.cpp 
#	TransitionFormatter.cpp \
#	TransitionPath.cpp \
#	Timestep.cpp \
#	Predicate.cpp \
#	StringUtils.cpp 

as2transition_LDADD = libas2transition.a

install-exec-hook:
	chmod 755 $(as2transincludedir)
	chmod 744 $(as2transincludedir)/*
	chown root -R $(as2transincludedir)

