# Autonomous Robot Sumo Champion (360° Attack & Defense)

This repository contains the autonomous firmware for my award-winning Sumo Robot, which took **1st Place**  at the regional **Mega Events** competition. Developed during my first year as a Computer Science student at **ENI Fianarantsoa**.

The project showcases a highly robust hardware and software architecture optimized to operate efficiently under strict resource and hardware constraints in Madagascar.

---

## Hardware Architecture

To achieve complete situational awareness and eliminate blind spots, the robot features a 360-degree sensor array:

*   **Microcontroller:** Arduino Uno / TME Education Eco-system.
*   **Tactical Scanning:** 4 x HC-SR04 Ultrasonic Sensors mounted on the Front, Left, Right, and Back to detect opponents from any angle.
*   **Border Security:** 2 x Infrared (IR) Line Tracking Sensors (Front and Back) calibrated to detect the high-contrast boundary of the Dohyo (ring).
*   **Actuators:** 2 x High-Torque DC Motors driven by an H-Bridge controller.

---

## Algorithmic Strategy & State Machine

The firmware is designed with an **absolute-priority safety loop** to prevent ring-outs while maintaining an aggressive hunting behavior:

1.  **Safety First (Anti-Chute):** Before executing any combat logic, the system reads the IR edge sensors. If the white border line is detected, the robot instantly aborts all operations, reverses, and pivots back into the safe black zone.
2.  **360° Situational Awareness:** The robot continuously triggers its 4 ultrasonic radars. 
3.  **Dynamic Counter-Attacks:**
    *   *Front Detection:* Charges forward at maximum speed.
    *   *Flank Detection (Left/Right):* Snap-turns to face the enemy directly.
    *   *Rear Detection:* Executes an immediate 180° spin maneuver to reverse the ambush.
4.  **Search Pattern:** If no enemy is tracked, it performs an energy-efficient pivot scan to sweep the arena.

---

##  How to Simulate & Run
*   The code is open-source and ready to be compiled using the **Arduino IDE**.
*   Hardware schematics can be prototyped virtually on platforms like **Wokwi** or **Tinkercad** for simulation before physical deployment.
