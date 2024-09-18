from tkinter import *
import tkinter.font as tkFont
import RPi.GPIO as GPIO
from gpiozero import LED

# Set up GPIO using BCM mode
GPIO.setmode(GPIO.BCM)

# Define the LEDs connected to respective GPIO pins
red_light = LED(6)
blue_light = LED(16)
green_light = LED(21)

# Create a window using Tkinter
app = Tk()
app.title("LED Controller")
font_style = tkFont.Font(family='Helvetica', size=14, weight='bold')

# Function to toggle the red LED and update other LEDs
def toggle_red():
    if red_light.is_lit:
        red_light.off()
        red_button["text"] = "Turn RED ON"
    else:
        red_light.on()
        red_button["text"] = "Turn RED OFF"
    blue_light.off()
    blue_button["text"] = "Turn BLUE ON"
    green_light.off()
    green_button["text"] = "Turn GREEN ON"

# Function to toggle the blue LED and update other LEDs
def toggle_blue():
    if blue_light.is_lit:
        blue_light.off()
        blue_button["text"] = "Turn BLUE ON"
    else:
        blue_light.on()
        blue_button["text"] = "Turn BLUE OFF"
    red_light.off()
    red_button["text"] = "Turn RED ON"
    green_light.off()
    green_button["text"] = "Turn GREEN ON"

# Function to toggle the green LED and update other LEDs
def toggle_green():
    if green_light.is_lit:
        green_light.off()
        green_button["text"] = "Turn GREEN ON"
    else:
        green_light.on()
        green_button["text"] = "Turn GREEN OFF"
    red_light.off()
    red_button["text"] = "Turn RED ON"
    blue_light.off()
    blue_button["text"] = "Turn BLUE ON"

# Function to clean up GPIO pins and close the window
def close_app():
    GPIO.cleanup()
    app.destroy()

# Buttons for controlling each LED
red_button = Button(app, text="Turn RED ON", font=font_style, command=toggle_red, bg='red', height=2, width=30)
red_button.grid(row=0, column=1)

blue_button = Button(app, text="Turn BLUE ON", font=font_style, command=toggle_blue, bg='blue', height=2, width=30)
blue_button.grid(row=1, column=1)

green_button = Button(app, text="Turn GREEN ON", font=font_style, command=toggle_green, bg='green', height=2, width=30)
green_button.grid(row=2, column=1)

# Exit button to close the application
exit_button = Button(app, text="EXIT", font=font_style, command=close_app, bg='yellow', height=2, width=30)
exit_button.grid(row=3, column=1)

# Bind the window close button to the cleanup function
app.protocol("WM_DELETE_WINDOW", close_app)

# Run the Tkinter main loop
app.mainloop()
