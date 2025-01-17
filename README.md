PROJECT: AGRO_BOT

Overview :
This document provides detailed instructions on how to use the Agro-Bot system. Agro-Bot is an Arduino-based robot designed for agricultural tasks. It follows a black line using infrared sensors, detects obstacles using an ultrasonic sensor, and checks soil moisture levels to determine whether irrigation is needed.

Features:
01. Line Following: Uses two infrared sensors to follow a white line, stops if detected black.
02. Obstacle Detection: Halts operation if an obstacle is detected within 6 inches.
03. Soil Moisture Detection: Measures soil moisture and activates a pump for irrigation if necessary.
04. Servo Motor Control: Lowers a servo arm for soil moisture measurement and raises it back after completion.
05. Timed Operation: Runs the line-following mode for 30 seconds before performing a soil moisture check.
