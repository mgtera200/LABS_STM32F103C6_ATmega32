## Lab3: Interrupt Controller On Atmega32

Write C Code using the 3 external interrupts
- External Interrupt 0 (INT0) - PD2. >> irq occur when “any logical change”
- External Interrupt 1 (INT1) - PD3. >> irq occur when “rising edge”
- External Interrupt 2 (INT2) - PB2. >> irq occur when “Falling edge”
- We have also 3 leds (PD5,6,7) (led0,1,2).
- Each interrupt just make the led 0N for 1 sec
- The main function is always make all the leds off
