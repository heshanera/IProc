#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/BMPProcessor/BMPProcessor.o \
	${OBJECTDIR}/IProc/IProc.o \
	${OBJECTDIR}/JPEGProcessor/JPEGProcessor.o \
	${OBJECTDIR}/PNGProcessor/PNGProcessor.o \
	${OBJECTDIR}/PixelProcessor/PixelProcessor.o \
	${OBJECTDIR}/TIFFProcessor/TIFFProcessor.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libIProc.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libIProc.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libIProc.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/BMPProcessor/BMPProcessor.o: BMPProcessor/BMPProcessor.cpp
	${MKDIR} -p ${OBJECTDIR}/BMPProcessor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BMPProcessor/BMPProcessor.o BMPProcessor/BMPProcessor.cpp

${OBJECTDIR}/IProc/IProc.o: IProc/IProc.cpp
	${MKDIR} -p ${OBJECTDIR}/IProc
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/IProc/IProc.o IProc/IProc.cpp

${OBJECTDIR}/JPEGProcessor/JPEGProcessor.o: JPEGProcessor/JPEGProcessor.cpp
	${MKDIR} -p ${OBJECTDIR}/JPEGProcessor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/JPEGProcessor/JPEGProcessor.o JPEGProcessor/JPEGProcessor.cpp

${OBJECTDIR}/PNGProcessor/PNGProcessor.o: PNGProcessor/PNGProcessor.cpp
	${MKDIR} -p ${OBJECTDIR}/PNGProcessor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PNGProcessor/PNGProcessor.o PNGProcessor/PNGProcessor.cpp

${OBJECTDIR}/PixelProcessor/PixelProcessor.o: PixelProcessor/PixelProcessor.cpp
	${MKDIR} -p ${OBJECTDIR}/PixelProcessor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PixelProcessor/PixelProcessor.o PixelProcessor/PixelProcessor.cpp

${OBJECTDIR}/TIFFProcessor/TIFFProcessor.o: TIFFProcessor/TIFFProcessor.cpp
	${MKDIR} -p ${OBJECTDIR}/TIFFProcessor
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TIFFProcessor/TIFFProcessor.o TIFFProcessor/TIFFProcessor.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
