The purpose of the lab is to have a button control the blinking of an LED using an interrupt. This is done by having a timer control the LED blink and then having a port interrupt control the enable.

The difference between the two is that the FR6989 has to have is default high impedance state disabled, and requires the pullup resistor to be enabled for the button.