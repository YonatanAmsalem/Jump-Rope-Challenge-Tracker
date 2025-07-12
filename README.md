# 🚀 Jump Counter with Level Selection – Arduino Uno R3

## 📋 Project Summary

This project is a **Smart Jump Rope Counter** built using Arduino Uno R3, designed to encourage physical activity in a fun and interactive way.

- 🧠 Users choose a difficulty level (1 to 5)
- ⏱️ Each level has a specific jump goal and time duration
- 🧾 Feedback is provided via LCD and LEDs
- 🔔 Buzzer alerts when goal is reached

**The goal:** Promote fitness and consistency by tracking jumps with increasing difficulty.

---

## 🔧 Components Used

- Arduino Uno R3  
- LCD I2C Display x2 (16x2)  
- Keypad 4x4  
- Tilt Sensor  
- Green LED  
- Buzzer  
- Breadboard  
- Jumper Wires  

---

## 🖼️ Circuit Diagram

📌 The following image shows the full schematic of the jump counting circuit, including all components and connections:  
*(insert image here)*

---

## 🎥 Demo Video

▶️ A demonstration of the system in action:  
*(insert video link or upload here)*

---

## ⚙️ How It Works

1. The user selects a level using the keypad (1–5)  
2. Each level has a predefined jump goal and timer (1 min or 1:20 min)  
3. Tilt sensor detects valid jump motions  
4. LCD1 shows jumps; LCD2 shows countdown  
5. When jump goal is reached – buzzer beeps and LED turns on  
6. At the end, the user can continue, change level, or exit  

---

🎉 This project combines fitness, electronics, and real-time feedback – all in one!  
