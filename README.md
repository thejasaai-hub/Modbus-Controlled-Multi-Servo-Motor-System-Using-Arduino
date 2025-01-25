# Modbus-Controlled Multi-Servo Motor System Using Arduino

This project demonstrates the control of multiple servo motors using the Modbus RTU protocol via RS-485 communication. The Arduino acts as a Modbus slave, receiving PWM values from a Modbus master to control the servo motor positions.

---

## How It Works

### **1. Servo Motor Control**
- Four servo motors are connected to the Arduino on pins `6`, `9`, `10`, and `11`.
- The servo motors receive positional values (`0 to 180` degrees) via the Modbus RTU protocol and adjust their angles accordingly.

### **2. Modbus Communication**
- The Arduino is configured as a Modbus slave:
  - **Slave ID:** `1`.
  - **Communication Medium:** RS-485.
  - **Baud Rate:** `9600 bps`.
- A Modbus master writes values into a Modbus array (`modbus_array[]`), which the Arduino reads to control the servos.

### **3. Modbus Array**
- The Modbus array (`modbus_array[]`) is initialized with four values:
  ```cpp
  uint16_t modbus_array[] = {0, 0, 0, 0};
  '''

- Each element in the `modbus_array[]` corresponds to the PWM values for a specific servo motor:
  - `modbus_array[0]`: Controls the servo motor connected to pin 6.
  - `modbus_array[1]`: Controls the servo motor connected to pin 9.
  - `modbus_array[2]`: Controls the servo motor connected to pin 10.
  - `modbus_array[3]`: Controls the servo motor connected to pin 11.

### 4. Arduino Code Logic

- **Initialization (`setup`):**
  1. The servo motors are attached to their respective pins using the `Servo` library:
     ```cpp
     servo.attach(6);
     servo1.attach(9);
     servo2.attach(10);
     servo3.attach(11);
     ```
  2. Modbus communication is initialized:
     - `bus = Modbus(2, 1, 4);`: Configures the Modbus slave with ID `1` and sets RS-485 DE/RE pins.
     - `bus.begin(9600);`: Starts Modbus communication at `9600 bps`.

- **Main Loop (`loop`):**
  1. The Arduino continuously polls the Modbus master for data:
     ```cpp
     bus.poll(modbus_array, sizeof(modbus_array) / sizeof(modbus_array[0]));
     ```
     This function updates the `modbus_array[]` with values received from the master.
  2. The values in the Modbus array are read and assigned to individual PWM values:
     ```cpp
     int pwm = modbus_array[0];
     int pwm1 = modbus_array[1];
     int pwm2 = modbus_array[2];
     int pwm3 = modbus_array[3];
     ```
  3. These PWM values are written to their respective servo motors to update their positions:
     ```cpp
     servo.write(pwm);
     servo1.write(pwm1);
     servo2.write(pwm2);
     servo3.write(pwm3);
     ```
  4. A delay of `200 ms` ensures smooth operation between updates:
     ```cpp
     delay(200);
     ```
### Features
1. **Multi-Servo Control:**
   - Controls up to four servo motors with independent PWM values.
2. **Modbus RTU Communication:**
   - Enables reliable communication with a Modbus master over RS-485.
3. **Real-Time Updates:**
   - Dynamically updates servo positions based on the Modbus master’s input.
4. **Flexible Integration:**
   - Can be integrated into larger Modbus-based automation systems.

---

### Components Required
1. **Arduino Board:**
   - Executes the code for Modbus communication and servo control.
2. **Servo Motors (x4):**
   - Controlled by the Arduino based on Modbus input.
3. **RS-485 Module:**
   - Provides a communication interface for the Modbus RTU protocol.
4. **Power Supply:**
   - Powers the Arduino and servo motors.
5. **Connecting Wires:**
   - For connecting components such as servo motors and the RS-485 module.

---

### Installation and Usage

#### 1. Wiring
- Connect the servo motors to the Arduino:
  - Servo 1 → Pin 6
  - Servo 2 → Pin 9
  - Servo 3 → Pin 10
  - Servo 4 → Pin 11
- Connect the RS-485 module to the Arduino:
  - DE/RE pins → Pin 4 (for RS-485 direction control).
  - DI pin → TX pin on Arduino.
  - RO pin → RX pin on Arduino.
- Provide power to the servo motors and RS-485 module using an external power supply if necessary.

#### 2. Modbus Master Configuration
- Configure a Modbus master to write PWM values (`0 to 180`) to the following registers:
  - Register 0: Servo on pin 6.
  - Register 1: Servo on pin 9.
  - Register 2: Servo on pin 10.
  - Register 3: Servo on pin 11.

#### 3. Upload the Code
1. Open the Arduino IDE.
2. Copy and paste the provided code into the IDE.
3. Connect the Arduino to your computer via USB.
4. Select the correct **COM Port** and **Board Type** in the Arduino IDE.
5. Upload the code to the Arduino.

#### 4. Operation
- Once the code is uploaded, the Arduino will:
  1. Continuously poll the Modbus master for data.
  2. Update the servo motor positions based on the received Modbus input.

---

### Applications
1. **Robotics:**
   - Control robotic arms or joints via Modbus communication.
2. **Industrial Automation:**
   - Integrate servo motors into Modbus-based automation systems.
3. **Prototyping:**
   - Develop multi-servo systems for educational or research purposes.

---

### Limitations
1. **Limited Servo Count:**
   - Supports only four servos; requires modification for additional servos.
2. **Fixed Baud Rate:**
   - The baud rate is hardcoded to `9600 bps`.
3. **Dependency on Modbus Master:**
   - Requires a Modbus master to send control signals.

---

### Future Enhancements
1. **Expand Servo Control:**
   - Support more servos using additional hardware or logic.
2. **Dynamic Communication Settings:**
   - Allow configurable baud rate and slave ID.
3. **Error Handling:**
   - Implement error detection and recovery for Modbus communication failures.
4. **Real-Time Feedback:**
   - Add sensors for closed-loop control to improve accuracy.
