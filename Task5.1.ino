from tkinter import *           # Import Tkinter for GUI
import tkinter.font as tkFont    # Import font module for customizing text styles
import RPi.GPIO as GPIO          # Import RPi.GPIO for GPIO control
from gpiozero import LED         # Import LED class from gpiozero for easy LED handling

# Initialize GPIO using BCM mode (GPIO numbering rather than physical pin numbers)
GPIO.setmode(GPIO.BCM)

# Define LEDs connected to specific GPIO pins
leds = {
    'red': LED(6),      # Red LED connected to GPIO pin 6
    'blue': LED(16),    # Blue LED connected to GPIO pin 16
    'green': LED(21)    # Green LED connected to GPIO pin 21
}

# Initialize Tkinter window
window = Tk()
window.title("Shuffled LED Controller")  # Set the title of the window
font_style = tkFont.Font(family='Arial', size=14, weight='bold')  # Define font style for labels and buttons

# Define initial toggle states for LEDs (all start in the off position)
led_states = {
    'red': False,   # Red LED is initially off
    'blue': False,  # Blue LED is initially off
    'green': False  # Green LED is initially off
}

# Function to update the button text based on each LED's state
def update_button_text():
    red_btn.config(text="Turn RED OFF" if led_states['red'] else "Turn RED ON")  # Update red button text
    blue_btn.config(text="Turn BLUE OFF" if led_states['blue'] else "Turn BLUE ON")  # Update blue button text
    green_btn.config(text="Turn GREEN OFF" if led_states['green'] else "Turn GREEN ON")  # Update green button text

# Function to toggle the specified LED and turn others off
def toggle_led(color):
    for led_color, led in leds.items():  # Loop through all LEDs
        if led_color == color:  # If the current LED matches the one to toggle
            if led_states[led_color]:  # If the LED is on, turn it off
                led.off()
            else:  # If the LED is off, turn it on
                led.on()
            led_states[led_color] = not led_states[led_color]  # Toggle the LED state
        else:
            led.off()  # Turn off all other LEDs
            led_states[led_color] = False  # Set their states to off
    update_button_text()  # Update button text to reflect the new states

# Function to handle the window close event (clean up GPIO and close window)
def close_window():
    GPIO.cleanup()  # Clean up all GPIO pins used in the program
    window.destroy()  # Close the Tkinter window

# Header label for the GUI
header_label = Label(window, text="LED Control Panel", font=font_style, pady=10)  # Create a header label
header_label.grid(row=0, column=0, columnspan=2, padx=20, pady=10)  # Place header label in the grid layout

# Blue LED controls (label and button)
blue_label = Label(window, text="BLUE LED", font=font_style, fg="blue")  # Label for blue LED
blue_label.grid(row=1, column=0, padx=20, pady=10)  # Place label in grid

blue_btn = Button(window, text="Turn BLUE ON", font=font_style, command=lambda: toggle_led('blue'), bg='blue', height=2, width=15)
# Button for toggling blue LED
blue_btn.grid(row=1, column=1, padx=20, pady=10)  # Place button in grid

# Green LED controls (label and button)
green_label = Label(window, text="GREEN LED", font=font_style, fg="green")  # Label for green LED
green_label.grid(row=2, column=0, padx=20, pady=10)  # Place label in grid

green_btn = Button(window, text="Turn GREEN ON", font=font_style, command=lambda: toggle_led('green'), bg='green', height=2, width=15)
# Button for toggling green LED
green_btn.grid(row=2, column=1, padx=20, pady=10)  # Place button in grid

# Red LED controls (label and button)
red_label = Label(window, text="RED LED", font=font_style, fg="red")  # Label for red LED
red_label.grid(row=3, column=0, padx=20, pady=10)  # Place label in grid

red_btn = Button(window, text="Turn RED ON", font=font_style, command=lambda: toggle_led('red'), bg='red', height=2, width=15)
# Button for toggling red LED
red_btn.grid(row=3, column=1, padx=20, pady=10)  # Place button in grid

# Exit button to close the window and clean up resources
exit_btn = Button(window, text="EXIT", font=font_style, command=close_window, bg='yellow', height=2, width=30)
# Button to close the window
exit_btn.grid(row=4, column=0, columnspan=2, padx=20, pady=20)  # Place exit button at the bottom

# Handle the window close event to ensure GPIO is cleaned up properly
window.protocol("WM_DELETE_WINDOW", close_window)  # Bind the window close event to the cleanup function

# Run the Tkinter main loop to display the window and handle events
window.mainloop()
