# Electric curtain

Controller: NodeMCU DEVKIT 1.0 + `FauxMoESP`

The original controller has 4 buttons: open, close, and 2 buttons for stop. All buttons are active-low (possibly pulled high by a pull-up resistor), logic level = 5V.

Modified controller has the same three functionalities: open, close, stop, but simulated by using two FauxMo devices:
- curtain opener: ON = open curtain, OFF = stop
- curtain closer: on = close curtain, OFF = stop

The two "stop" functions are identical.

## To-Do
- [ ] add schematic and photos
- [ ] device does not respond after sometime - maybe disable the three control pins after a while, instead of leaving some on all the time
- [x] add pull-down resistors
