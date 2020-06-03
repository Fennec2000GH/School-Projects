# Author: Caijun Qin
# Date 05/27/2020

from math import log
from statistics import mean


class SciCalculator:
    """Scientific Calculator (simple)"""

    # MEMBER FUNCTIONS
    def __init__(self):
        self.current_value = 0.0
        self.results = []

    def main(self):
        menu_choice = None
        while True:
            if menu_choice != 7 and menu_choice != -1:
                self.print_current_value()
                SciCalculator.print_menu()
            menu_choice = int(input('Enter Menu Selection: '))

            # exiting program
            if menu_choice == 0:
                print('\nThanks for using this calculator. Goodbye!')
                return

            # checking for valid menu choice
            try:
                if menu_choice < 0 or menu_choice > 7:
                    raise IndexError('Error: Invalid selection!')
            except IndexError:
                print('\nError: Invalid selection!\n')
                menu_choice = -1
                continue

            # determining type of computation from menu_choice
            if menu_choice == 7:  # average
                # checking for empty result array
                try:
                    if len(self.results) == 0:
                        raise RuntimeError('Error: No calculations yet to average!')
                except RuntimeError:
                    print('\nError: No calculations yet to average!\n')
                    continue

                # printing out summary statistics
                print('\nSum of calculations: {}'.format(sum(self.results)))
                print('Number of calculations: {}'.format(len(self.results)))
                print('Average of calculations: {0:.2f}\n'.format(mean(self.results)))
                continue

            param1 = input('Enter first operand: ')
            param2 = input('Enter second operand: ')
            self.calculate(menu_choice=menu_choice, param1=param1, param2=param2)
            print('')

    @staticmethod
    def print_menu():
        print(
            """
Calculator Menu 
--------------- 
0. Exit Program 
1. Addition
2. Subtraction
3. Multiplication 
4. Division
5. Exponentiation 
6. Logarithm
7. Display Average
"""
        )

    def print_current_value(self):
        print('Current Result: {}'.format(self.current_value))

    def calculate(self, menu_choice, param1, param2):
        """Choose and execute specified computation based on menu choice."""

        # check for use of special string RESULT
        if param1 == 'RESULT' or param2 == 'RESULT':
            try:
                if len(self.results) == 0:
                    raise RuntimeError('Error: No calculations yet!').with_traceback(tb=param1)
            except RuntimeError:
                print('Calculation failed!')
            if param1 == 'RESULT':
                param1 = float(self.results[len(self.results) - 1])
            if param2 == 'RESULT':
                param2 = float(self.results[len(self.results) - 1])

        # convert to float
        param1 = float(param1)
        param2 = float(param2)

        # selecting menu option
        if menu_choice == 1:  # addition
            self.current_value = param1 + param2
        elif menu_choice == 2:  # subtraction
            self.current_value = param1 - param2
        elif menu_choice == 3:  # multiplication
            self.current_value = param1 * param2
        elif menu_choice == 4:  # division
            try:
                param1 / param2
            except ZeroDivisionError:
                print('\nError: cannot divide by zero!')
                return
            self.current_value = param1 / param2
        elif menu_choice == 5:  # exponentiation
            self.current_value = pow(param1, param2)
        elif menu_choice == 6:  # logarithm
            self.current_value = log(param2, param1)

        if menu_choice != 7:
            self.results.append(self.current_value)


if __name__ == '__main__':
    c = SciCalculator()
    c.main()
