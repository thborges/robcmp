#
# Robcmp compiler platform for platformio
#   Require packages according to upload_protocol and custom_mcu
#

from platformio.public import PlatformBase

class RobcmpPlatform(PlatformBase):
    def configure_default_packages(self, variables, targets):
        upload_protocol = variables.get("upload_protocol", "")
        custom_mcu = variables.get("custom_mcu")
        required_tool = None
        
        if upload_protocol == "serial":
            if custom_mcu == "avr328p":
                required_tool = "tool-avrdude"
            elif custom_mcu == "stm32f1":
                required_tool = "tool-stm32duino"
        elif upload_protocol == "stlink":
            if custom_mcu == "stm32f1":
                required_tool = "tool-openocd"

        if required_tool:
            self.packages[required_tool]['optional'] = False

        return super().configure_default_packages(variables, targets)
