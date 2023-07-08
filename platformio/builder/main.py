"""
    Build script for robcmp platform
"""

import sys
from os.path import join
from SCons.Script import AlwaysBuild, Builder, Default, DefaultEnvironment, Glob

env = DefaultEnvironment()

mcu = env.GetProjectOption("custom_mcu")
if mcu == "stm32":
    ld = "ld.lld"
    ldflags = ["-nostdlib", "-entry=main", "-Tmemory.lld.ld", "-Bstatic"]
elif mcu == "avr328p":
    ld = "avr-gcc"
    ldflags = ["-mmcu=atmega328p"]
else:
    sys.stderr.write("The requested mpu is not supported.\n")
    env.Exit(1)


env.Replace(
    UPLOADER=join("$PIOPACKAGES_DIR", "tool-bar", "uploader"),
    UPLOADCMD="$UPLOADER $SOURCES"
)

env.Append(
    BUILDERS=dict(
        ElfToBin=Builder(
            action=" ".join(["llvm-objcopy", "-O", "binary", "$SOURCES", "$TARGET"]),
            suffix=".bin"
        ),
        Linker=Builder(
            action = ' '.join([ld, "$SOURCES", ' '.join(ldflags), "-o", "$TARGET"]),
            suffix=".elf"
        ),
        Rob=Builder(
            action = ' '.join(["robcmp", "-a"+mcu, "-o", "$TARGET", "$SOURCE"]),
            suffix = '.o',
            src_suffix = '.rob',
        )
    )
)

sources = Glob(env.subst(join("$PROJECT_DIR/src/", "*.rob")))
#source_fnames = [join("$PROJECT_DIR/src/", f.name) for f in sources]
#print("SOURCES: ", source_fnames)

target_objs = []
for f in sources:
    target_objs += env.Rob(f)

target_elf = env.Linker("firmware", target_objs)
target_bin = env.ElfToBin(join("$BUILD_DIR", "firmware"), target_elf)

upload = env.Alias(["upload"], target_bin, "$UPLOADCMD")
AlwaysBuild(upload)

Default(target_bin)