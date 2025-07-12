# Jump-Rope-Challenge-Tracker
✨ Project Title: Jump Rope Challenge Tracker 🏃‍♂️⏱️
📋 Project Summary
This interactive jump-counting system was built using Arduino Uno R3 to promote fun and healthy physical activity.
It allows users to choose difficulty levels and track their jump count with real-time feedback and a timed challenge.

🎯 Purpose: Encourage physical activity and set personal fitness goals

💡 Solution: Automatically detect and count rope jumps per session

🔔 Features: Tilt sensor, buzzer, dual LCD displays, level-based targets

🛠️ Tools: Used Timer1 interrupt and I2C communication for display & timing

🧰 Components Used
🧠 Arduino Uno R3

📟 16x2 I2C LCD Display (Main Display)

⏲️ 16x2 I2C LCD Display (Timer)

🎛️ Keypad 4x4

🔔 Active Buzzer

🟢 Green LED

🎯 Tilt Sensor (for jump detection)

🧵 Jumper Wires

🔌 Breadboard

⚡ Resistors (for LEDs)

🖼️ Circuit Diagram
The image below illustrates the full wiring of the components on a breadboard connected to Arduino Uno R3.
🔧🧩📷 

🎬 Demonstration Video
📽️ A short video showing a full run of the system, from level selection to jump detection and feedback.
🏃‍♀️✅🟢 

⚙️ How It Works – Step by Step
1️⃣ The user selects a difficulty level (1–5) using the keypad
2️⃣ The main LCD displays the selected level and target jump count
3️⃣ A tilt sensor detects each jump and updates the jump count
4️⃣ Timer1 tracks time (1 min or 1:20 based on level) on LCD #2
5️⃣ Once the target is reached, a buzzer beeps and a green LED lights up
6️⃣ At the end, the user can repeat, change the level, or exit

