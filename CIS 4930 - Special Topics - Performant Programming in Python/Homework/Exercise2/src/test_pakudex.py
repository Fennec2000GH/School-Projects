
import copy
import math
import numpy as np
import pytest
from pakuri import Pakuri

# FIXTURES
@pytest.fixture
def pakuri_array():
    """Sets up custom test array"""
    arr = np.asarray(a=[Pakuri('Adam', 'Aardvark', 0),
                        Pakuri('Berry', 'Bear', 1),
                        Pakuri('Can Can', 'Crow', 2),
                        Pakuri('Darren', 'Dolphin', 3)
                        ],
                      dtype=Pakuri
                      )
    print(type(arr))
    print(arr)
    return arr

@pytest.fixture
def name_array(pakuri_array):
    """Derives names from each Pakuri in given array"""
    arr = np.asarray(a=[pakuri.name() for pakuri in pakuri_array])
    print(type(arr))
    print(arr)
    return arr

@pytest.mark.execute
def test_numpy_any_pakuri_array(pakuri_array):
    """Checking to find Pakuri name in array holding Pakuri objects"""
    assert np.any(a='Darren' in [pakuri.name() for pakuri in pakuri_array])

@pytest.mark.execute
def test_numpy_argwhere(pakuri_array, name_array):
    """Checking to see if correct indices are returned for each Pakuri with given name"""
    OUTPUT = []
    OUTPUT.append(int(np.argwhere(a='Adam' == name_array)[0]))
    OUTPUT.append(int(np.argwhere(a='Berry' == name_array)[0]))
    OUTPUT.append(int(np.argwhere(a='Can Can' == name_array)[0]))
    OUTPUT.append(int(np.argwhere(a='Darren' == name_array)[0]))
    print(OUTPUT)
    EXPECTED = list(range(4))
    assert OUTPUT == EXPECTED

@pytest.mark.execute
def test_list_pakuri(pakuri_array):
    """List Pakuri"""
    try:
        if pakuri_array.size == 0:
            raise RuntimeError('No Pakuri in Pakudex yet!').with_traceback(tb=pakuri_array)
    except RuntimeError:
        print('No Pakuri in Pakudex yet!')
        return

    # listing out each Pakuri object
    OUTPUT = []
    for pakuri in pakuri_array:
        line = f'{pakuri.name()} ({pakuri.species()}, level {pakuri.level()})'
        print(line)
        OUTPUT.append(line)

    EXPECTED = ['Adam (Aardvark, level 0)', 'Berry (Bear, level 1)', 'Can Can (Crow, level 2)', 'Darren (Dolphin, level 3)']
    assert OUTPUT == EXPECTED

@pytest.mark.execute
def test_show_pakuri(pakuri_array, name_array):
    """Show Pakuri"""
    try:
        if not np.any(a='Darren' in [pakuri.name() for pakuri in pakuri_array]):
            raise ValueError('Error: No such Pakuri!')
    except ValueError:
        print('Error: No such Pakuri!')
        return

    # computing index for specified Pakuri
    pakuri_index = int(np.argwhere(a='Darren' == name_array)[0])
    print(type(pakuri_index))
    print(pakuri_index)
    assert type(pakuri_index) == int
    assert pakuri_index == 3

    pakuri_obj = pakuri_array[pakuri_index]
    print(type(pakuri_obj))
    assert type(pakuri_obj) == Pakuri

    OUTPUT = \
f"""
Name: {pakuri_obj.name()}
Species: {pakuri_obj.species()}
Level: {pakuri_obj.level()}
CP: {pakuri_obj.cp()}
HP: {pakuri_obj.hp()}
"""
    print(OUTPUT)

    EXPECTED = \
f"""
Name: Darren
Species: Dolphin
Level: 3
CP: 0
HP: 0
"""
    assert OUTPUT == EXPECTED

@pytest.mark.execute
def test_add_pakuri(pakuri_array):
    """Add Pakuri"""
    print('Pakuri Information')
    print('------------------')
    pakuri_name = 'Easter'

    # error checking for duplicate
    try:
        if np.any(a=pakuri_name in [pakuri.name() for pakuri in pakuri_array]):
            raise ValueError('Error: Pakudex already contains this Pakuri!')
    except ValueError:
        print('Error: Pakudex already contains this Pakuri!')
        return

    pakuri_species = 'Bunny'
    pakuri_level = 50
    print(f'Species: {pakuri_species}')
    print(f'Level: {pakuri_level}')

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

    pakuri_array_copy = copy.deepcopy(x=pakuri_array) # delete
    pakuri_array_copy = np.append(arr=pakuri_array_copy, values=Pakuri(name=pakuri_name, species=pakuri_species, level=pakuri_level))
    print(f'Pakuri {pakuri_name} ({pakuri_species}, level {pakuri_level}) added!')

    new_pakuri = pakuri_array_copy[4]
    assert type(new_pakuri) == Pakuri
    assert new_pakuri.name() == 'Easter'
    assert new_pakuri.species() == 'Bunny'
    assert new_pakuri.level() == 50

@pytest.mark.execute
def test_remove_pakuri(pakuri_array, name_array):
    """Remove Pakuri"""
    pakuri_name = 'Adam'
    print(f'Enter the name of the Pakuri to remove: {pakuri_name}')

    # error checking for valid name
    try:
        if pakuri_name not in name_array:
            raise RuntimeError('Error! No such Pakuri!')
    except RuntimeError:
        print('Error! No such Pakuri!')
        return

    # computing index for specified Pakuri
    pakuri_index = int(np.argwhere(a=pakuri_name == name_array)[0])
    print(type(pakuri_index))
    print(pakuri_index)
    assert type(pakuri_index) == int
    assert pakuri_index == 0

    pakuri_array_copy = copy.deepcopy(x=pakuri_array)
    pakuri_array_copy = np.delete(arr=pakuri_array_copy, obj=pakuri_index)
    print(f'Pakuri {pakuri_name} removed.')
    print(pakuri_array_copy) # delete
    assert 'Adam' not in np.asarray(a=[pakuri.name() for pakuri in pakuri_array_copy])
    assert pakuri_array_copy[0].name() == 'Berry'

@pytest.mark.execute
def test_change_pakuri_level(pakuri_array, name_array):
    """Change Pakuri Level"""
    pakuri_array_copy = copy.deepcopy(x=pakuri_array) # delete
    name_array_copy = copy.deepcopy(x=np.asarray(a=[pakuri.name() for pakuri in pakuri_array_copy]))

    pakuri_name = 'Darren'
    print(f'Enter the name of the Pakuri to remove: {pakuri_name}')

    # error checking for valid name
    try:
        if pakuri_name not in name_array_copy:
            raise RuntimeError('Error! No such Pakuri!')
    except RuntimeError:
        print('Error! No such Pakuri!')
        return

    pakuri_level = 42
    print(f'Enter the new level for the Pakuri: {pakuri_level}')

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
    pakuri_index = int(np.argwhere(a=pakuri_name == name_array_copy)[0])
    print(type(pakuri_index))
    print(pakuri_index)
    assert type(pakuri_index) == int
    assert pakuri_index == 3
    pakuri_array_copy[pakuri_index].Level = pakuri_level
    assert pakuri_array_copy[3].level() == 42

