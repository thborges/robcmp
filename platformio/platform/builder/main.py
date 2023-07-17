"""
    Build script for robcmp platform
"""

import os
import sys
from os.path import join
from SCons.Script import AlwaysBuild, Builder, Default, DefaultEnvironment, Glob

env = DefaultEnvironment()
platform = env.PioPlatform()
ldscripts_folder = platform.get_package_dir("toolchain-robcmp")

os.environ['LD_LIBRARY_PATH'] = join(ldscripts_folder, "lib")

# Needed by debug
env.Replace(
    PROGNAME="firmware.elf"
)

board = env.subst("$BOARD")
mcu = env.subst("$BOARD_MCU")
if mcu == "stm32f1":
    ld = "ld.lld"
    ldflags = ["-nostdlib", "-entry=main", "-T" + ldscripts_folder + "/share/stm32f1.lld.ld", "-Bstatic"]
elif mcu == "atmega328p":
    ld = "avr-ld"
    ldflags = ["--gc-sections", "-Tdata=0x800100"]
else:
    sys.stderr.write("The requested mcu is not supported.\n")
    env.Exit(1)


env.Append(
    BUILDERS=dict(
        ElfToBin=Builder(
            action=" ".join(["llvm-objcopy", "-Oihex", "$SOURCES", "$TARGET"]),
            suffix=".bin"
        ),
        Linker=Builder(
            action = ' '.join([ld, "$SOURCES", ' '.join(ldflags), "-o", "$TARGET"]),
            suffix=".elf"
        ),
        Rob=Builder(
            action = ' '.join(["robcmp", "-a", board, "-o", "$TARGET", "$SOURCE"]),
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
    target_objs += env.Rob(join("$BUILD_DIR", f.name + ".o"), f)

target_elf = env.Linker(join("$BUILD_DIR", "firmware"), target_objs)
target_bin = env.ElfToBin(join("$BUILD_DIR", "firmware"), target_elf)

# UPLOAD
upload_protocol = env.subst("$UPLOAD_PROTOCOL")
upload_actions = []

if upload_protocol == "serial":
    upload_actions.append(env.VerboseAction(env.AutodetectUploadPort, "Looking for upload port..."))

    if mcu == "stm32f1":
        stm32flash_bin = join(platform.get_package_dir("tool-stm32duino"), "stm32flash")
        env.Replace(
            UPLOADER=join(stm32flash_bin, "stm32flash"),
            UPLOADERFLAGS=["-g", "0x08000000", "-b", "115200", "-w"],
            UPLOADCMD='$UPLOADER $UPLOADERFLAGS "$SOURCE" $UPLOAD_PORT'
        )

    elif mcu == "atmega328p":
        avrdude_bin = join(platform.get_package_dir("tool-avrdude"), "avrdude")
        avrdude_cfg = join(platform.get_package_dir("tool-avrdude"), "avrdude.conf")
        env.Replace(
            UPLOADER=avrdude_bin,
            UPLOADERFLAGS=["-C", avrdude_cfg, "-v", "-V", "-c", "arduino", "-p", "m328p", "-U"],
            UPLOADCMD='$UPLOADER $UPLOADERFLAGS flash:w:${SOURCE}:i -P $UPLOAD_PORT'
        )
        
    else:
        sys.stderr.write("Upload protocol %s doesn't support mcu %s\n" % (upload_protocol, mcu))
        env.Exit(1)

elif upload_protocol == "stlink":
    if mcu == "stm32f1":
        openocd_folder = platform.get_package_dir("tool-openocd")
        env.Replace(
            UPLOADER=join(openocd_folder, "bin", "openocd"),
            UPLOADERFLAGS=["-f", join(openocd_folder, "scripts/interface/stlink.cfg"),
                           "-f", join(openocd_folder, "scripts/target/stm32f1x.cfg"),
                           "-c", "program $SOURCE reset 0x08000000 exit"],
            UPLOADCMD="$UPLOADER $UPLOADERFLAGS"
        )
        
    else:
        sys.stderr.write("Upload protocol %s doesn't support mcu %s\n" % (upload_protocol, mcu))
        env.Exit(1)

else:
    sys.stderr.write("Unknown upload protocol %s\n" % upload_protocol)
    env.Exit(1)

upload_actions.append(env.VerboseAction("$UPLOADCMD", "Uploading $SOURCE"))

upload = env.Alias(["upload"], target_bin, upload_actions)
AlwaysBuild(upload)

Default(target_bin)