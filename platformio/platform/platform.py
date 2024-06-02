#
# Robcmp compiler platform for platformio
#   Require packages according to upload_protocol and board
#

import os
from platformio.public import PlatformBase

class RobcmpPlatform(PlatformBase):
    def configure_default_packages(self, variables, targets):
        upload_protocol = variables.get("upload_protocol", "")
        board = variables.get("board")
        required_tool = None
        
        if upload_protocol == "serial":
            if board == "avr328p":
                required_tool = "tool-avrdude"
            elif board == "stm32f1":
                required_tool = "tool-stm32duino"
        elif upload_protocol == "stlink":
            if board == "stm32f1":
                required_tool = "tool-openocd"

        if required_tool:
            self.packages[required_tool]['optional'] = False

        return super().configure_default_packages(variables, targets)

    def get_boards(self, id_=None):
        result = super().get_boards(id_)
        if not result:
            return result
        if id_:
            return self._add_default_debug_tools(result)
        else:
            for key, value in result.items():
                result[key] = self._add_default_debug_tools(result[key])
        return result

    def _add_default_debug_tools(self, board):
        debug = board.manifest.get("debug", {})
        if "tools" not in debug:
            debug["tools"] = {}

        if debug.get("target_mcu", ""):
            debug["tools"]["robcmp-led"]["server"]["arguments"] = [
                "-f", "$PROG_PATH",
                "-m", debug["target_mcu"],
                "-hw", "led",
                "-g"
            ]
            debug["tools"]["robcmp-ssd1306"]["server"]["arguments"] = [
                "-f", "$PROG_PATH",
                "-m", debug["target_mcu"],
                "-hw", "ssd1306",
                "-g"
            ]
            debug["tools"]["robcmp-hd44780"]["server"]["arguments"] = [
                "-f", "$PROG_PATH",
                "-m", debug["target_mcu"],
                "-hw", "hd44780",
                "-g"
            ]

        board.manifest["debug"] = debug
        return board
