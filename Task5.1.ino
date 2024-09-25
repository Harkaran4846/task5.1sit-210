from tkinter import *
import tkinter.font as tkFont
import RPi.GPIO as GPIO
from gpiozero import LED

# Initialize GPIO using BCM mode
GPIO.setmode(GPIO.BCM)

# LED setup on respective GPIO pins
leds = {
    'red': LED(6),
    'blue': LED(16),
    'green': LED(21)
}

# Initialize Tkinter window
window = Tk()
window.title("Shuffled LED Controller")
font_style = tkFont.Font(family='Arial', size=14, weight='bold')

# Define toggle states for LEDs
led_states = {
    'red': False,
    'blue': False,
    'green': False
}

# Function to update button text
def update_button_text():
    red_btn.config(text="Turn RED OFF" if led_states['red'] else "Turn RED ON")
    blue_btn.config(text="Turn BLUE OFF" if led_states['blue'] else "Turn BLUE ON")
    green_btn.config(text="Turn GREEN OFF" if led_states['green'] else "Turn GREEN ON")

# Function to toggle a specific LED
def toggle_led(color):
    for led_color, led in leds.items():
        if led_color == color:
            if led_states[led_color]:
                led.off()
            else:
                led.on()
            led_states[led_color] = not led_states[led_color]
        else:
            led.off()
            led_states[led_color] = False
    update_button_text()

# Close window and cleanup GPIO
def close_window():
    GPIO.cleanup()
    window.destroy()

# Header label
header_label = Label(window, text="LED Control Panel", font=font_style, pady=10)
header_label.grid(row=0, column=0, columnspan=2, padx=20, pady=10)

# Shuffled LED control layout
# Blue LED controls at the top
blue_label = Label(window, text="BLUE LED", font=font_style, fg="blue")
blue_label.grid(row=1, column=0, padx=20, pady=10)

blue_btn = Button(window, text="Turn BLUE ON", font=font_style, command=lambda: toggle_led('blue'), bg='blue', height=2, width=15)
blue_btn.grid(row=1, column=1, padx=20, pady=10)

# Green LED controls in the middle
green_label = Label(window, text="GREEN LED", font=font_style, fg="green")
green_label.grid(row=2, column=0, padx=20, pady=10)

green_btn = Button(window, text="Turn GREEN ON", font=font_style, command=lambda: toggle_led('green'), bg='green', height=2, width=15)
green_btn.grid(row=2, column=1, padx=20, pady=10)

# Red LED controls at the bottom
red_label = Label(window, text="RED LED", font=font_style, fg="red")
red_label.grid(row=3, column=0, padx=20, pady=10)

red_btn = Button(window, text="Turn RED ON", font=font_style, command=lambda: toggle_led('red'), bg='red', height=2, width=15)
red_btn.grid(row=3, column=1, padx=20, pady=10)

# Exit button at the bottom
exit_btn = Button(window, text="EXIT", font=font_style, command=close_window, bg='yellow', height=2, width=30)
exit_btn.grid(row=4, column=0, columnspan=2, padx=20, pady=20)

# Handle window close event
window.protocol("WM_DELETE_WINDOW", close_window)

# Run the Tkinter main loop
window.mainloop()
