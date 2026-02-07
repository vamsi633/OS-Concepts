import argparse

class Core:
    # 1. THE SETUP: This runs the moment you create a "Core" object.
    def __init__(self, args_list):
        # We create a "Parser" (a tool that reads commands).
        # We save it to 'self.parser' so the whole class can see it.
        self.parser = argparse.ArgumentParser(description='My Parser')
        
        # We take your list of settings and add them one by one.
        for arg in args_list:
            self.add_arg_parser_argument(arg)

    # 2. THE RULE-MAKER: This adds specific rules to our tool.
    def add_arg_parser_argument(self, arg):
        # This line uses the 'parser' tool we saved in the backpack (self).
        # arg[0] is the flag (like '-n')
        # arg[1] is the variable name (like 'num_threads')
        self.parser.add_argument(arg[0], dest=arg[1], default=arg[2], help=arg[3])

    # 3. THE RUNNER: This actually looks at what the user typed.
    def parse_args(self, input_data):
        # This tells the tool to "Go!" and sort the input.
        return self.parser.parse_args(input_data)

# --- HOW TO RUN THIS CODE ---

# This is a list of information: [Flag, Name, Default, Description]
my_settings = [['-n', 'num_threads', 1, 'number of threads']]

# We build the Core machine
my_machine = Core(my_settings)

# We simulate a user typing '-n 10' in the command line
results = my_machine.parse_args(['-n', '10'])

# Now we can see the result!
print(f"The number of threads is: {results.num_threads}")