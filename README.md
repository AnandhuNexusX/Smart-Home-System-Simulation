# AI Smart Home System Simulation

ESP32-based smart home automation system built in Wokwi.

## Features
- Motion-based lighting
- Temperature-controlled fan
- LCD status display
- DHT22 temperature and humidity monitoring
- Optional Blynk integration

## Files

### sketch/sketch.ino
Main ESP32 program.

### diagram.json
Circuit connections and components.

### libraries.txt
Libraries required by the simulation.

### wokwi-project.txt
Contains the Wokwi simulation link.

## Working Logic

1. PIR detects motion.
2. LDR checks ambient light.
3. LED turns on when the room is dark and occupied.
4. DHT22 measures temperature and humidity.
5. Servo acts as a fan:
   - >32°C → High speed
   - 27-32°C → Medium speed
   - <27°C → OFF
6. LCD displays room status.

## Wokwi Simulation

https://wokwi.com/projects/464198097463525377
