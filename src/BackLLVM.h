
#pragma once

#include "BuildTypes.h"

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

enum SupportedTargets {st_native, st_avr328p, st_stm32f1, st_esp32, __last_target};
extern enum SupportedTargets currentTargetId;
#define currentTarget (supportedTargets[currentTargetId])

static TargetInfo supportedTargets[__last_target] = {
	{rb_native, "", "", "", "", tint64}, // default target
	{rb_avr,    "avr328p", "avr", "atmega328p", "+avr5", tint16},
	{rb_arm,    "stm32f1", "thumbv7m-none-eabi", "cortex-m3", "", tint32},
	{rb_xtensa, "esp32",   "xtensa",  "", "", tint32},
};

static void setTarget(const char *targetarch) {
	currentTargetId = st_native; //native
	for(int t = st_native; t < __last_target; t++) {
		if (strcmp(targetarch, supportedTargets[t].name) == 0) {
			currentTargetId = static_cast<enum SupportedTargets>(t);
			break;
		}
	}
}
