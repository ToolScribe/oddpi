# CXXFLAGS = -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -I .
CXXFLAGS=-I. -D_DEBUG -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -g -std=c++11 -fvisibility-inlines-hidden -fno-exceptions -fno-rtti -fPIC -ffunction-sections -fdata-sections -Wcast-qual -fno-strict-aliasing    -pedantic -Wno-long-long -Wall -W -Wno-unused-parameter -Wwrite-strings    -Wno-maybe-uninitialized -Wno-missing-field-initializers


all:	obj.o

