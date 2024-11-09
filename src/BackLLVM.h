
#pragma once

#include "BuildTypes.h"
#include "Injections.h"

extern std::unique_ptr<IRBuilder<>> Builder;

enum RobBackend {rb_native, rb_avr, rb_arm, rb_xtensa};

typedef struct {
	enum RobBackend backend;
	const char *name;
	const char *triple;
	const char *cpu;
	const char *features;
	const DataType pointerType;
} TargetInfo;

extern unsigned int codeAddrSpace;
extern unsigned int dataAddrSpace;

enum SupportedTargets {
	st_native, 
	
	// avr
	st_attiny13a,
	st_attiny85,
	st_atmega328p,
	st_atmega32u4, 
	st_atmega1284p, 
	
	// stm32
	st_stm32f1, 
	
	// awaiting backend goes mainstream
	st_esp32, 
	__last_target};

extern enum SupportedTargets currentTargetId;

extern TargetInfo supportedTargets[__last_target];
void setTarget(const char *targetarch);
const TargetInfo& currentTarget();

class Variable;

extern map<string, Injection*> injections;
