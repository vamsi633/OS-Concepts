import time

#example1
class SimpleExample:
    def __init__(self):
        self.message="Hello from thread"

    def my_task(self):
        print(self.message)
        time.sleep(2)
        print("Task finished")

example=SimpleExample()
example.my_task()

#example2
class MyRobot:
    def __init__(self,color):
        self.my_color=color
        print(f"Robot built! Color is {self.my_color}")
    
    def paint_house(self):
        print(f"I am painting the house {self.my_color}!")

bot=MyRobot("Blue")
bot.paint_house()


#example 3
class MiniCore:
    # 1. The Setup: Put the tool in the backpack
    def __init__(self):
        self.message = "The machine is ready!" 

    # 2. The Action: Reach into the backpack and use the tool
    def print_message(self):
        print(self.message)

# --- HOW IT RUNS ---
# This creates the object (calls __init__ automatically)
my_machine = MiniCore()

# This uses the method to print the message from the backpack
my_machine.print_message()