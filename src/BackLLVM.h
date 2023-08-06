
#pragma once

#include "BuildTypes.h"

extern std::unique_ptr<IRBuilder<>> Builder;

typedef struct {
	const char *name;
	const char *triple;
	const char *cpu;
	const char *features;
	const DataType pointerType;
} TargetInfo;

extern unsigned int globalAddrSpace;
enum SupportedTargets {native, avr328p, stm32f1, esp32, __last_target};
extern enum SupportedTargets currentTargetId;
#define currentTarget (supportedTargets[currentTargetId])

static TargetInfo supportedTargets[__last_target] = {
	{"", "", "", "", tint64}, // default target
	{"avr328p", "avr", "atmega328p", "+avr5", tint16},
	{"stm32f1", "thumbv7m-none-eabi", "cortex-m3", "", tint32},
	{"esp32",   "xtensa",  "", "", tint32},
};

static void initTarget(const char *targetarch) {
	currentTargetId = native; //native
	for(int t = native; t < __last_target; t++) {
		if (strcmp(targetarch, supportedTargets[t].name) == 0) {
			currentTargetId = static_cast<enum SupportedTargets>(t);
			break;
		}
	}
}
