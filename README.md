## AVR UART Shell Library

A lightweight, embeddable command-line interface (CLI) for AVR microcontrollers. Perfect for debugging, configuration, and interactive control of your embedded projects.

## Adding Custom Commands

To add your own custom commands follow the instructions inside the template.c file. Once you finish implementing your command register it inside shell*init() function using register*(your_command_name)\_command().

## Demo

This demo was done using this library and [avr-hd44780-i2c](https://github.com/krdgomer/avr-hd44780-i2c)
![demo](https://github.com/krdgomer/avr-uart-shell/blob/main/demo.gif)
