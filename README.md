# RC Maze Solver Car

A line-following RC car that solves mazes using four IR sensors and an Arduino.

## Features
- 4 IR sensors (center left/right, side left/right) for wall detection
- Differential drive with two DC motors and L298N driver
- Auto-turn logic to handle T-junctions and dead ends
- Modular code structure for easy tweaking of speeds and thresholds

## Hardware
- Arduino Uno (or clone)
- L298N Dual H-bridge motor driver
- 2 × DC motors + wheels
- 4 × IR obstacle/line sensors
- Battery pack or DC power convertor
- Jumper wires, chassis


| Signal        | Arduino Pin |
| ------------- | ----------- |
| IR Center R   | 7           |
| IR Center L   | 8           |
| IR Left       | 6           |
| IR Right      | 11          |
| Motor IN1     | 2           |
| Motor IN2     | 3           |
| Motor IN3     | 4           |
| Motor IN4     | 5           |
| ENA (Motor A) | 9           |
| ENB (Motor B) | 10          |

## Software / Usage
1. Open `src/MazeSolver.ino` in the Arduino IDE.  
2. Select the correct board & COM port.  
3. Upload.  

### Code Overview
- `getReadings()` reads all four IR sensors.
- `forward()`, `turn_left()`, `turn_right()`, `reverse()`, `stop()` wrap motor commands.
- The main `loop()` uses flag variables to remember last turn direction and implements:
  - Straight-ahead when both center sensors see no wall.
  - Gentle corrections when only one center sensor is triggered.
  - Sharp turns on side-sensor triggers.
  - Reverse and re-route on dead ends.


## License
MIT © 2025 Kareem Abdelaziz
