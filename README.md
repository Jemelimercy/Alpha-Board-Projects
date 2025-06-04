# Alpha-Board-Project:LIGHT GUARD
##  What It Does

- **Arm the System**: Press **Button A4** to activate the security system. The  **orange LED will flash**.
- **Disarm the System**: Use **Button A5** to input a timed password sequence.The **green LED will flash**

# While Armed:
- The system continuously monitors ambient light using the onboard **LDR**.
- If light drops below a predefined threshold (e.g., someone blocking the LDR), the **alarm is triggered**.
- The **buzzer sounds** and **red LED flash** to indicate intrusion.
- To **disarm**, the user must press **Button A5** in a specific timed sequence (i.e  a password).
  - Each press is timestamped and stored in a buffer.
  - If the pattern of press timings matches the preset password, the system disarms and the **green LED flash**.

# While Disarmed:
- The system remains **inactive and silent** — no alarms or monitoring.
