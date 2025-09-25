# 🔐 Door Locker Security System (ATmega32)

## 📖 Project Overview
This project implements a **Door Locker Security System** using an **ATmega32 microcontroller** and two Electronic Control Units (ECUs).  
The system ensures secure access by requiring password authentication, and includes features such as door unlocking, password change, and alarm activation on failed attempts.  

- **ECU 1 (HMI_ECU):** Handles user interaction through **LCD** and **Keypad**.  
- **ECU 2 (Control_ECU):** Processes inputs, verifies passwords, controls the **Motor**, **Buzzer**, and manages **EEPROM** storage.  

---

## 🛠️ Hardware Used
- **ATmega32 Microcontroller**  
- **HMI_ECU:**  
  - 2×16 LCD (8-bit mode)  
  - 4×4 Keypad  
- **Control_ECU:**  
  - EEPROM  
  - Buzzer  
  - DC Motor + H-Bridge  

---

## 🧩 Software Drivers
- **HMI_ECU**  
  - MCAL: GPIO, UART, Timer  
  - HAL: LCD, Keypad  
  - APP  

- **Control_ECU**  
  - MCAL: GPIO, UART, Timer, I2C  
  - HAL: EEPROM, Buzzer, DC Motor + H-Bridge  
  - APP  

---

## ⚡ System Specifications
### ECU 1: HMI_ECU  
- Collects password input from the keypad  
- Displays system messages on LCD  
- Sends data to **Control_ECU** via UART  

### ECU 2: Control_ECU  
- Verifies password with EEPROM storage  
- Controls motor (door locking/unlocking)  
- Handles password change logic  
- Activates buzzer on security breach  

---

## 💻 System Requirements

<img width="588" height="598" alt="Image" src="https://github.com/user-attachments/assets/deff9998-f3a5-469c-9248-f5b4d658beb0" />

---

## 🔄 System Workflow

### **Step 1 – Create a System Password**
1. LCD → “Please Enter Password”  
2. User enters **5-digit password** → LCD shows `*****`  
3. Press Enter → Ask user to **re-enter password**  
4. Both passwords sent to **Control_ECU** via UART  
   - ✅ Match → Save password in EEPROM, proceed to Step 2  
   - ❌ Mismatch → Repeat Step 1  

---

### **Step 2 – Main Options**
LCD always displays:  
  : Open Door
  : Change Password


---

### **Step 3 – Open Door (+)**  
1. LCD → “Please Enter Password”  
2. Password sent to **Control_ECU**  
   - ✅ Match →  
     - Rotate motor **CW (15s)** → “Door Unlocking”  
     - Hold (3s)  
     - Rotate motor **CCW (15s)** → “Door Locking”  
   - ❌ Mismatch → Go to Step 5  

---

### **Step 4 – Change Password (-)**  
1. LCD → “Please Enter Password”  
2. If ✅ Match → Repeat **Step 1 (Password Creation)**  
3. If ❌ Mismatch → Go to Step 5  

---

### **Step 5 – Failed Attempts**  
- If password is entered incorrectly **3 consecutive times**:  
  - 🚨 Activate buzzer (1 minute)  
  - ❌ Display error on LCD (1 minute)  
  - 🔒 Lock system (no inputs accepted during this time)  
- After timeout → Return to **Step 2**  

---

## 🖼️ Project Simulation
Designed and tested using **Proteus**.  
<img width="1117" height="845" alt="Image" src="https://github.com/user-attachments/assets/8a9470af-09ce-4c7b-896b-fcbde30769e2" />

---

## 💻 System Requirements
To run, build, or simulate this project you need:  
- **Proteus Design Suite** (for simulation)  
- **AVR-GCC / Atmel Studio / Microchip Studio** (for compiling C code)  
- **AVRDUDE or USBasp Programmer** (for uploading to hardware)  
- **ATmega32 Microcontroller Board**  
- **Basic Embedded C knowledge**  

---

## 👤 Author
**Youssef Alaa**  
- GitHub: [@Youssef-Al-eng](https://github.com/Youssef-Al-eng)  
- LinkedIn: [Youssef Alaa](https://www.linkedin.com/in/youssef-alaa-1b9580332/)  
