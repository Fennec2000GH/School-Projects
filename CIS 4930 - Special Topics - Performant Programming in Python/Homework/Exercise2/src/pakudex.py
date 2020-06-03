import numpy as np
from pakuri import Pakuri

pakuri_array = np.asarray(a=[], dtype=Pakuri)


def print_menu():
    """Prints out menu of choices"""
    print("""
Pakudex Main Menu
-----------------
1. List Pakuri
2. Show Pakuri
3. Add Pakuri
4. Remove Pakuri
5. Change Pakuri Level
6. Exit\n
"""
          )


def execute(menu_choice: int, pakuri_array: np.array):
    """Executes appropriate action based on menu choice"""
    if menu_choice == 1:
        """List Pakuri"""
        try:
            if pakuri_array.size == 0:
                raise RuntimeError('No Pakuri in Pakudex yet!').with_traceback(tb=pakuri_array)
        except RuntimeError:
            print('No Pakuri in Pakudex yet!')
            return

        # listing out each Pakuri object
        for pakuri in pakuri_array:
            print(f'{pakuri.name()} ({pakuri.species()}, level {pakuri.level()})')

    elif menu_choice == 2:
        """Show Pakuri"""
        pakuri_name = input(__prompt='Enter the name of the pakuri to display: ')
        try:
            if not np.any(a=pakuri.name() for pakuri in pakuri_array == pakuri_name):
                raise ValueError('Error: No such Pakuri!')
        except ValueError:
            print('Error: No such Pakuri!')
            return
        pakuri_index = np.argwhere(a=pakuri_name in [pakuri.name() for pakuri in pakuri_array])[0]
        pakuri_obj = pakuri_array[pakuri_index]
        print(f"""
Name: {pakuri_obj.name()}
Species: {pakuri_obj.species()}
Level: {pakuri_obj.level()}
CP: {pakuri_obj.cp()}
HP: {pakuri_obj.hp()}
""")

    elif menu_choice == 3:
        """Add Pakuri"""
        print('Pakuri Information')
        print('------------------')
        pakuri_name = input(__prompt='Name: ')

        # error checking for duplicate
        try:
            if np.any(a=pakuri_name in [pakuri.name() for pakuri in pakuri_array]):
                raise ValueError('Error: Pakudex already contains this Pakuri!')
        except ValueError:
            print('Error: Pakudex already contains this Pakuri!')
            return
        pakuri_species = input(__prompt='Species: ')
        pakuri_level = input(__prompt='Level: ')

        # error checking for invalid level
        try:
            if type(pakuri_level) != int:
                raise ValueError('Invalid level!')
        except ValueError:
            print('Invalid level!')
            return
        try:
            if int(pakuri_level) < 0:
                raise ValueError('Level cannot be negative.')
        except ValueError:
            print('Level cannot be negative.')
            return
        try:
            if int(pakuri_level) > 50:
                raise ValueError('Maximum level for Pakuri is 50.')
        except ValueError:
            print('Maximum level for Pakuri is 50.')
            return

        pakuri_array = np.append(arr=pakuri_array,
                                 values=Pakuri(name=pakuri_name, species=pakuri_species, level=int(pakuri_level)))
        print(f'Pakuri {pakuri_name} ({pakuri_species}, level {pakuri_level}) added!')

    elif menu_choice == 4:
        """Remove Pakuri"""
        pakuri_name = input(__prompt='Enter the name of the Pakuri to remove: ')

        # error checking for valid name
        try:
            if pakuri_name not in [pakuri.name() for pakuri in pakuri_array]:
                raise RuntimeError('Error! No such Pakuri!')
        except RuntimeError:
            print('Error! No such Pakuri!')
            return
        pakuri_index = np.argwhere(a=pakuri_name in [pakuri.name() for pakuri in pakuri_array])
        del pakuri_array[pakuri_index]
        print(f'Pakuri {pakuri_name} removed.')

    elif menu_choice == 5:
        """Change Pakuri Level"""
        pakuri_name = input(__prompt='Enter the name of the Pakuri to remove: ')

        # error checking for valid name
        try:
            if pakuri_name not in [pakuri.name() for pakuri in pakuri_array]:
                raise RuntimeError('Error! No such Pakuri!')
        except RuntimeError:
            print('Error! No such Pakuri!')
            return

        pakuri_level = input(__prompt='Enter the new level for the Pakuri: ')
        # error checking for valid level
        try:
            if type(pakuri_level) != int:
                raise ValueError('Invalid level!')
        except ValueError:
            print('Invalid level!')
            return
        try:
            if int(pakuri_level) < 0:
                raise ValueError('Level cannot be negative.')
        except ValueError:
            print('Level cannot be negative.')
            return
        try:
            if int(pakuri_level) > 50:
                raise ValueError('Maximum level for Pakuri is 50.')
        except ValueError:
            print('Maximum level for Pakuri is 50.')
            return

        # setting new level
        pakuri_index = np.argwhere(a=pakuri_name in [pakuri.name() for pakuri in pakuri_array])[0]
        pakuri_array[pakuri_index].Level = pakuri_level

if __name__ == '__main__':
    print('Welcome to Pakudex: Let\'s Go!')
    while menu_choice != 6:
        print_menu()
        menu_choice = input(__prompt='What would you like to do?')
        try:
            if menu_choice <= 0 or menu_choice >= 7:
                raise ValueError('Invalid menu choice! Please try again!')
        except ValueError:
            print('Invalid menu choice! Please try again!')
            continue
        execute(menu_choice=menu_choice)
