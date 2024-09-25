"""
    Build script for robcmp platform
"""

import os
import sys
from os.path import join
from SCons.Script import AlwaysBuild, Builder, Default, DefaultEnvironment, Glob

from platformio.util import get_serial_ports


def BeforeUpload(target, source, env):  # pylint: disable=W0613,W0621
    env.AutodetectUploadPort()
    upload_options = {}
    if "BOARD" in env:
        upload_options = env.BoardConfig().get("upload", {})


env = DefaultEnvironment()
platform = env.PioPlatform()
ldscripts_folder = join(platform.get_package_dir("toolchain-robcmp"), "lib")
stdlib_folder = join(platform.get_package_dir("toolchain-robcmp"), "stdlib")

os.environ['LD_LIBRARY_PATH'] = ldscripts_folder

# Needed by debug
env.Replace(
    PROGNAME="firmware.elf"
)

sources = []
auxsources = []

board = env.subst("$BOARD")
mcu = env.subst("$BOARD_MCU")
try:
    hardware_spec = env.GetProjectOption("board_hardware_spec")
except:
    hardware_spec = None
    pass

if mcu == "native":
    ldflags = []
else:
    ldflags = ["-L", stdlib_folder]
    ldflags.append("-nostdlib")
    ldflags.append("-Bstatic")
    ldflags.append("--gc-sections")
    ldflags.append("--lto=thin")

if mcu.startswith("stm32f1"):
    ldflags.append("-Tstm32f1.ld")
    auxsources += Glob(join(stdlib_folder, "stm32f1.rob"))
elif mcu == "atmega328p":
    ldflags.append("-Tatmega328p.ld")
    ldflags.append(join(stdlib_folder, "avr5.o"))
    auxsources += Glob(join(stdlib_folder, "atmega328p.rob"))
elif mcu == "native":
    pass
else:
    sys.stderr.write("The requested mcu is not supported.\n")
    env.Exit(1)

build_type = env.GetProjectOption("build_type")
robcmp_args = ["robcmp", "-a", board, "-o", "$TARGET"]

if build_type == "debug":
    robcmp_args.append("-g")
    robcmp_args.append("-O0")
elif build_type == "release":
    robcmp_args.append("-Oz")

hardware_spec_args = []
if hardware_spec:
    hardware_spec_args = ["-s", hardware_spec]

robcmp_args.append("-I")
robcmp_args.append(stdlib_folder)
robcmp_args.append("$SOURCE")

if board.startswith("atmega") or board.startswith("attiny"):
	avr_gdb = join(platform.get_package_dir("toolchain-robcmp"), "bin", "avr-gdb")
	env.Replace(
		GDB=avr_gdb
	)
else:
	env.Replace(
		GDB="gdb"
	)


linker = "ld.lld"
if mcu == "native":
    linker = "clang -g -O0" # using clang to link on native platform

env.Append(
    BUILDERS=dict(
        ElfToBin=Builder(
            action=" ".join(["llvm-objcopy", "-Oihex", "$SOURCES", "$TARGET"]),
            suffix=".bin"
        ),
        Linker=Builder(
            action = ' '.join([linker, ' '.join(ldflags), "$SOURCES", "-o", "$TARGET"]),
            suffix=".elf"
        ),
        Rob=Builder(
            action = ' '.join(robcmp_args),
            suffix = '.o',
            src_suffix = '.rob',
        ),
        RobDep=Builder(
            action = ' '.join(robcmp_args + hardware_spec_args + ["-bdep"]),
            suffix = '.o',
            src_suffix = '.rob',
        )
    )
)

sources += Glob(env.subst(join("$PROJECT_DIR/src/", "main.rob")))
#sources += Glob(env.subst(join("$PROJECT_DIR/src/**/", "*.rob")))
#print("SOURCES: ", source_fnames)

target_objs = []
for f in sources:
    robdep = env.RobDep(join("$BUILD_DIR", f.name + ".o"), f)
    # Always building while not proper detect dependencies changes (use inside .rob)
    AlwaysBuild(robdep)
    target_objs += robdep
for f in auxsources:
    target_objs += env.Rob(join("$BUILD_DIR", f.name + ".o"), f)

target_elf = env.Linker(join("$BUILD_DIR", "firmware"), target_objs)
target_bin = env.ElfToBin(join("$BUILD_DIR", "firmware"), target_elf)

# UPLOAD
upload_protocol = env.subst("$UPLOAD_PROTOCOL")
upload_actions = []

if upload_protocol == "serial":
    upload_actions.append(env.VerboseAction(env.AutodetectUploadPort, "Looking for upload port..."))

    if mcu.startswith("stm32"):
        stm32flash_bin = join(platform.get_package_dir("tool-stm32duino"), "stm32flash")
        env.Replace(
            UPLOADER=join(stm32flash_bin, "stm32flash"),
            UPLOADERFLAGS=["-b", "115200", "-w"],
            UPLOADCMD='$UPLOADER $UPLOADERFLAGS "$SOURCE" $UPLOAD_PORT'
        )

    elif mcu == "atmega328p":
        avrdude_bin = join(platform.get_package_dir("tool-avrdude"), "avrdude")
        avrdude_cfg = join(platform.get_package_dir("tool-avrdude"), "avrdude.conf")
        env.Replace(
            UPLOADER=avrdude_bin,
            UPLOADERFLAGS=["-C", avrdude_cfg, "-v", "-V", "-c", "arduino", "-p", "m328p", "-b", "57600", "-U"],
            UPLOADCMD='$UPLOADER $UPLOADERFLAGS flash:w:${SOURCE}:i -P $UPLOAD_PORT'
        )

    else:
        sys.stderr.write("Upload protocol %s doesn't support mcu %s\n" % (upload_protocol, mcu))
        env.Exit(1)

elif upload_protocol == "stlink":
    if mcu.startswith("stm32f1"):
        openocd_folder = platform.get_package_dir("tool-openocd")
        env.Replace(
            UPLOADER=join(openocd_folder, "bin", "openocd"),
            UPLOADERFLAGS=["-f", join(openocd_folder, "scripts/interface/stlink.cfg"),
                           "-f", join(openocd_folder, "scripts/target/stm32f1x.cfg"),
                           "-c", "program $SOURCE reset exit"],
            UPLOADCMD="$UPLOADER $UPLOADERFLAGS"
        )

    else:
        sys.stderr.write("Upload protocol %s doesn't support mcu %s\n" % (upload_protocol, mcu))
        env.Exit(1)

elif upload_protocol == "none":
    pass
else:
    sys.stderr.write("Unknown upload protocol %s\n" % upload_protocol)
    env.Exit(1)

upload_actions.append(env.VerboseAction("$UPLOADCMD", "Uploading $SOURCE"))

upload = None
if mcu.startswith("stm32"):
    upload = env.Alias(["upload"], target_elf, upload_actions)
else:
    upload = env.Alias(["upload"], target_bin, upload_actions)
AlwaysBuild(upload)

# SIZE
target_size = env.AddPlatformTarget(
    "size",
    target_elf,
    env.VerboseAction("llvm-size -d $SOURCES", "Calculating size $SOURCE"),
    "Program Size",
    "Calculate program size",
)

env.Depends(target_bin, "size")
Default(target_bin)
