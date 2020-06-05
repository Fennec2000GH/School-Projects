
import collections
import copy
import math
import numpy as np
import pytest
from pakuri import Pakuri


########################################################################################################################
# FIXTURES
@pytest.fixture
def pakuri_array_fix():
    """Sets up custom test array"""
    arr_fix = np.asarray(a=[Pakuri('Adam', 'Aardvark', 0),
                            Pakuri('Berry', 'Bear', 1),
                            Pakuri('Can Can', 'Crow', 2),
                            Pakuri('Darren', 'Dolphin', 3)],
                         dtype=Pakuri)

    print(type(arr_fix))
    print(arr_fix)
    return arr_fix


@pytest.fixture
def name_array_fix(pakuri_array_fix):
    """Derives names from each Pakuri in given array"""
    arr_fix = np.asarray(a=[pakuri.name for pakuri in pakuri_array_fix])
    print(type(arr_fix))
    print(arr_fix)
    return arr_fix


########################################################################################################################
# helper function
def pakuri_array():
    """Non-fixture version of pakuri_array"""
    arr = np.asarray(a=[Pakuri('Adam', 'Aardvark', 0),
                        Pakuri('Berry', 'Bear', 1),
                        Pakuri('Can Can', 'Crow', 2),
                        Pakuri('Darren', 'Dolphin', 3)],
                     dtype=Pakuri)

    print(type(arr))
    print(arr)
    return arr


# helper function
def name_array():
    """Non-fixture version of name_array"""
    arr = np.asarray(a=[pakuri.name for pakuri in pakuri_array()])
    print(type(arr))
    print(arr)
    return arr


# MAIN PROGRAM TESTS
@pytest.mark.main
@pytest.mark.parametrize(argnames=['name'], argvalues=[(name,) for name in name_array()])
def test_numpy_any_pakuri_array_fix(name_array_fix: np.array, name: str):
    """Checking to find Pakuri name in array holding Pakuri objects"""
    print(name)
    print(name_array().tolist())
    assert np.any(a=name == name_array_fix)


@pytest.mark.main
@pytest.mark.parametrize(argnames=['index', 'EXPECTED'], argvalues=[
    (int(np.argwhere(a='Adam' == name_array())[0]), 0),
    (int(np.argwhere(a='Berry' == name_array())[0]), 1),
    (int(np.argwhere(a='Can Can' == name_array())[0]), 2),
    (int(np.argwhere(a='Darren' == name_array())[0]), 3)])
def test_numpy_argwhere(index: int, EXPECTED: int):
    """Checking to see if correct indices are returned for each Pakuri with given name"""
    print(index)
    print(EXPECTED)
    assert index == EXPECTED


@pytest.mark.main
def test_list_pakuri(pakuri_array_fix):
    """List Pakuri"""
    try:
        if pakuri_array_fix.size == 0:
            raise RuntimeError('No Pakuri in Pakudex yet!')
    except RuntimeError as error:
        print(str(error))
        return

    # listing out each Pakuri object
    print('Pakuri In Pakudex:')
    OUTPUT = []
    for pakuri in pakuri_array_fix:
        line = f'{pakuri.name} ({pakuri.species}, level {pakuri.level})'
        print(line)
        OUTPUT.append(line)

    EXPECTED = ['Adam (Aardvark, level 0)',
                'Berry (Bear, level 1)',
                'Can Can (Crow, level 2)',
                'Darren (Dolphin, level 3)']
    assert OUTPUT == EXPECTED


@pytest.mark.main
@pytest.mark.xfail(raises=RuntimeError)
def test_list_pakuri_fail():
    """FAILURE: list Pakuri but list id empty"""
    pakuri_array_fix = np.asarray(a=[], dtype=Pakuri)
    try:
        if pakuri_array_fix.size == 0:
            raise RuntimeError('No Pakuri in Pakudex yet!')
    except RuntimeError as error:
        print(str(error))
        assert True  # debugging
        # return


@pytest.mark.main
@pytest.mark.parametrize(argnames=['pakuri', 'name', 'index'],
                         argvalues=[(pakuri, name, index) for pakuri, name, index in
                                    zip(pakuri_array(), name_array(), range(4))])
def test_show_pakuri(pakuri_array_fix: np.array, name_array_fix: np.array, pakuri: Pakuri, name: str, index: int):
    """Show Pakuri"""
    try:
        if not np.any(a=name == name_array_fix):
            raise ValueError('Error: No such Pakuri!')
    except ValueError as error:
        print(str(error))
        return

    # computing index for specified Pakuri
    pakuri_index = int(np.argwhere(a=name == name_array_fix)[0])
    assert type(pakuri_index) == int
    assert pakuri_index == index

    assert pakuri == pakuri_array_fix[pakuri_index]
    assert type(pakuri) == Pakuri

    print(f'Enter the name of the pakuri to display: {name}\n')
    OUTPUT = \
        f"""
Name: {pakuri.name}
Species: {pakuri.species}
Level: {pakuri.level}
CP: {pakuri.cp}
HP: {pakuri.hp}
"""
    print(OUTPUT)

    EXPECTED = \
        f"""
Name: {name}
Species: {pakuri_array_fix[pakuri_index].species}
Level: {pakuri_array_fix[pakuri_index].level}
CP: {pakuri_array_fix[pakuri_index].cp}
HP: {pakuri_array_fix[pakuri_index].hp}
"""
    assert OUTPUT == EXPECTED


@pytest.mark.xfail(raises=ValueError)
@pytest.mark.main
@pytest.mark.parametrize(argnames=['name'], argvalues=[(name,) for name in ['a', 'b', 'c', 'd']])
def test_show_pakuri_fail(name_array_fix: np.array, name: str):
    """FAILURE: show Pakuri but not in list"""
    try:
        if not np.any(a=name == name_array_fix):
            raise ValueError('Error: No such Pakuri!')
    except ValueError as error:
        print(str(error))
        assert True
    print('Exception ont caught!')  # debugging


@pytest.mark.main
@pytest.mark.parametrize(argnames=['name', 'species', 'level'], argvalues=[
    ('Peter', 'Rabbit', '32'),
    ('Patrick', 'Starfish', 0),
    ('Perry', 'Platypus', 48),
    ('Toothless', 'Dragon', 50)])
def test_add_pakuri(name: str, species: str, level: int):
    """Add Pakuri"""
    # temporary local Pakudex collection
    pakuri_array_copy = np.asarray(a=[Pakuri(name='Sam', species='Sea Turtle', level=32)])
    print(pakuri_array_copy)  # debugging

    print('Pakuri Information')
    print('------------------')
    print(f'Name: {name}')

    # error checking for duplicate
    try:
        if np.any(a=name == [(name,) for name in pakuri_array_copy]):
            raise ValueError('Error: Pakudex already contains this Pakuri!')
    except ValueError as error:
        print(str(error))
        return

    print(f'Species: {species}')

    # error checking for invalid level
    print(f'Level: {level}')
    # below is for failure tests only
    # valid_level = False
    # while not valid_level:
    #     try:
    #         int(level)
    #         if type(level) != int:
    #             raise ValueError('Invalid level!')
    #     except ValueError as error:
    #         print(str(error))
    #         continue
    #     try:
    #         if level < 0:
    #             raise ValueError('Level cannot be negative.')
    #     except ValueError as error:
    #         print(str(error))
    #         continue
    #     try:
    #         if level > 50:
    #             raise ValueError('Maximum level for Pakuri is 50.')
    #     except ValueError as error:
    #         print(str(error))

    pakuri_array_copy = np.append(arr=pakuri_array_copy, values=Pakuri(name=name, species=species, level=level))
    print(pakuri_array_copy)  # debugging
    print(f'Pakuri {name} ({species}, level {level}) added!')

    new_pakuri = pakuri_array_copy[1]  # note for debugging purposes, newly appended Pakuri are simply appended without sorting
    assert type(new_pakuri) == Pakuri
    assert new_pakuri.name == name
    assert new_pakuri.species == species
    assert new_pakuri.level == level


@pytest.mark.xfail
@pytest.mark.main
def test_add_pakuri_fail_duplicate():
    """FAILURE: add Pakuri duplicate"""
    # temporary local Pakudex collection
    pakuri_array_copy = np.asarray(a=[Pakuri(name='Sam', species='Sea Turtle', level=32)])
    print(pakuri_array_copy)  # debugging

    name = 'Sam'
    print('Pakuri Information')
    print('------------------')
    print(f'Name: {name}')

    # error checking for duplicate
    print([pakuri.name for pakuri in pakuri_array_copy]) # debugging
    try:
        if np.any(a=name == np.asarray(a=[pakuri.name for pakuri in pakuri_array_copy])):
            raise ValueError('Error: Pakudex already contains this Pakuri!')
    except ValueError as error:
        print(str(error))
        assert True
        return
    print('Exception not caught!')

@pytest.mark.main
def test_add_pakuri_fail_level_negative():
    """FAILURE: add negative level"""
    # temporary local Pakudex collection
    pakuri_array_copy = np.asarray(a=[Pakuri(name='Sam', species='Sea Turtle', level=32)])
    print(pakuri_array_copy)  # debugging

    Test_Case = collections.namedtuple(typename='Test_Case', field_names=['name', 'species', 'level_first', 'level_second', 'doc'])
    test_case = Test_Case(name='Arbor', species='Tree', level_first=-1, level_second=20, doc='Level cannot be negative.') # resembles Pakudex proeprties and more

    print('Pakuri Information')
    print('------------------')
    print(f'Name: {test_case.name}')

    # error checking for duplicate
    try:
        if np.any(a=test_case.name == np.asarray(a=[(name,) for name in pakuri_array_copy])):
            raise ValueError('Error: Pakudex already contains this Pakuri!')
    except ValueError as error:
        print(str(error))
        return

    print(f'Species: {test_case.species}')

    # error checking for invalid level
    print(f'Level: {test_case.level_first}')

    # below is for failure tests only
    level = test_case.level_first # debugging
    valid_level = False
    # while not valid_level:
    try:
        if level < 0:
            raise ValueError('Level cannot be negative.')
    except ValueError as error:
        print(str(error))
        level = test_case.level_second

    level = int(level)  # securing level as int type
    assert level in np.arange(0, 51)
    print('Level is now valid!')

@pytest.mark.main
def test_add_pakuri_fail_level_over_max():
    """FAILURE: add level greater than max limit"""
    # temporary local Pakudex collection
    pakuri_array_copy = np.asarray(a=[Pakuri(name='Sam', species='Sea Turtle', level=32)])
    print(pakuri_array_copy)  # debugging

    Test_Case = collections.namedtuple(typename='Test_Case', field_names=['name', 'species', 'level_first', 'level_second', 'doc'])
    test_case = Test_Case(name='Dory', species='Whale', level_first=120, level_second=20, doc='Maximum level for Pakuri is 50.')

    print('Pakuri Information')
    print('------------------')
    print(f'Name: {test_case.name}')

    # error checking for duplicate
    try:
        if np.any(a=test_case.name == np.asarray(a=[(name,) for name in pakuri_array_copy])):
            raise ValueError('Error: Pakudex already contains this Pakuri!')
    except ValueError as error:
        print(str(error))
        return

    print(f'Species: {test_case.species}')

    # error checking for invalid level
    print(f'Level: {test_case.level_first}')

    # below is for failure tests only
    level = test_case.level_first # debugging
    valid_level = False
    # while not valid_level:

    level = int(level)  # securing level as int type
    # continue
    try:
        if level > 50:
            raise ValueError('Maximum level for Pakuri is 50.')
    except ValueError as error:
        print(str(error))
        level = test_case.level_second
    assert level in np.arange(0, 51)
    print('Level is now valid!')

@pytest.mark.main
def test_add_pakuri_fail_level_invalid():
    """FAILURE: add invalid (non-integer) level"""
    # temporary local Pakudex collection
    pakuri_array_copy = np.asarray(a=[Pakuri(name='Sam', species='Sea Turtle', level=32)])
    print(pakuri_array_copy)  # debugging

    Test_Case = collections.namedtuple(typename='Test_Case', field_names=['name', 'species', 'level_first', 'level_second', 'doc'])
    test_case = Test_Case(name='Goku', species='Monkey', level_first='NINE-THOUSAND', level_second=20, doc='Invalid level!')

    print('Pakuri Information')
    print('------------------')
    print(f'Name: {test_case.name}')

    # error checking for duplicate
    try:
        if np.any(a=test_case.name == np.asarray(a=[(name,) for name in pakuri_array_copy])):
            raise ValueError('Error: Pakudex already contains this Pakuri!')
    except ValueError as error:
        print(str(error))
        return

    print(f'Species: {test_case.species}')

    # error checking for invalid level
    print(f'Level: {test_case.level_first}')

    # below is for failure tests only
    level = test_case.level_first  # debugging
    # valid_level = False
    # while not valid_level:
    try:
        level = int(level)
        if type(level) != int:
            raise ValueError('Invalid level!')
    except ValueError as error:
        print('Invalid level!')
        level = test_case.level_second
        # continue

    level = int(level)  # securing level as int type
    assert level in np.arange(0, 51)
    print('Level is now valid!')

@pytest.mark.main
def test_remove_pakuri(pakuri_array_fix: np.array, name_array_fix: np.array):
    """Remove Pakuri"""
    # temporary local Pakudex collection
    pakuri_array_copy = copy.deepcopy(x=pakuri_array_fix)
    print(pakuri_array_copy)  # debugging

    name = 'Adam'
    print(f'Enter the name of the Pakuri to remove: {name}')

    # error checking for valid name
    try:
        if not np.any(a=name == name_array_fix):
            raise RuntimeError('Error! No such Pakuri!')
    except RuntimeError as error:
        print(str(error))
        assert False
        # return

    # computing index for specified Pakuri
    pakuri_index = int(np.argwhere(a=name == name_array_fix)[0])
    print(type(pakuri_index)) # debugging
    print(pakuri_index) # debugging
    assert type(pakuri_index) == int
    assert pakuri_index == 0

    pakuri_array_copy = np.delete(arr=pakuri_array_copy, obj=pakuri_index)
    print(f'Pakuri {name} removed.')
    print(pakuri_array_copy)  # delete
    assert 'Adam' not in [pakuri.name for pakuri in pakuri_array_copy]
    assert pakuri_array_copy[0].name == 'Berry'


@pytest.mark.main
def test_change_pakuri_level(pakuri_array_fix: np.array):
    """Change Pakuri Level"""
    pakuri_array_copy = copy.deepcopy(x=pakuri_array_fix)  # debugging

    name = 'Darren'
    print(f'Enter the name of the Pakuri to remove: {name}')

    # error checking for valid name
    try:
        if not np.any(a=name == np.asarray(a=[pakuri.name for pakuri in pakuri_array_copy])):
            raise RuntimeError('Error! No such Pakuri!')
    except RuntimeError as error:
        print(str(error))
        assert False
        # return

    level = 42
    print(f'Enter the new level for the Pakuri: {level}')

    # error checking for valid level
    try:
        level = int(level)
        if type(level) != int:
            raise ValueError('Invalid level!')
    except ValueError:
        print('Invalid level!')
        assert False
        # return

    level = int(level) # securing level as int typ

    try:
        if level < 0:
            raise ValueError('Level cannot be negative.')
    except ValueError as error:
        print(str(error))
        assert False
        # return
    try:
        if level > 50:
            raise ValueError('Maximum level for Pakuri is 50.')
    except ValueError as error:
        print(str(error))
        assert False
        # return

    # setting new level
    index = int(np.argwhere(a=name == np.asarray(a=[pakuri.name for pakuri in pakuri_array_copy]))[0])
    print(type(index)) # debugging
    print(index) # debugging
    assert type(index) == int
    assert index == 3
    pakuri_array_copy[index].level = level
    assert pakuri_array_copy[3].level == 42

# @pytest.mark.main
# def test_change_pakuri_level_fail(pakuri_array_fix: np.array):
#
#     test_case = Test_Case
#     print(f'Enter the name of the Pakuri to change {}')
# # below is for failure tests only
#     valid_level = False
#     while not valid_level:
#         try:
#             int(level)
#             if type(level) != int:
#                 raise ValueError('Invalid level!')
#         except ValueError as error:
#             print(str(error))
#             continue
#         try:
#             if level < 0:
#                 raise ValueError('Level cannot be negative.')
#         except ValueError as error:
#             print(str(error))
#             continue
#         try:
#             if level > 50:
#                 raise ValueError('Maximum level for Pakuri is 50.')
#         except ValueError as error:
#             print(str(error))
########################################################################################################################

@pytest.mark.sorting
def test_sorting_list():
    """Tests for customized sorting of Pakuri"""
    pakuri_list = pakuri_array().tolist()
    EXPECTED = ['Darren', 'Can Can', 'Berry', 'Adam']
    print(pakuri_list)  # debugging
    print([pakuri.name for pakuri in pakuri_list])  # debugging

    # sort reversed
    pakuri_list = [
        Pakuri(name='Remy', species='Rat', level=24),
        Pakuri(name='Otis', species='Cow', level=12),
        Pakuri(name='Gromit', species='Dog', level=6),
        Pakuri(name='Wilbur', species='Pig', level=48)]
    print(pakuri_list) # debugging
    print([pakuri.name for pakuri in pakuri_list]) # debugging

    # sort
    EXPECTED = ['Gromit', 'Otis', 'Remy', 'Wilbur']
    pakuri_list.sort()
    assert [pakuri.name for pakuri in pakuri_list] == EXPECTED

    # sort reversed
    EXPECTED = ['Wilbur', 'Remy', 'Otis', 'Gromit']
    pakuri_list.sort(reverse=True)
    print(pakuri_list)  # debugging
    print([pakuri.name for pakuri in pakuri_list]) # debugging
    assert [pakuri.name for pakuri in pakuri_list] == EXPECTED

    # sort by species
    EXPECTED = ['Otis', 'Gromit', 'Wilbur', 'Remy']
    pakuri_list.sort(key=lambda x: x.species)
    print(pakuri_list)  # debugging
    print([pakuri.name for pakuri in pakuri_list])  # debugging
    assert [pakuri.name for pakuri in pakuri_list] == EXPECTED

    # sort by level
    EXPECTED = ['Gromit', 'Otis', 'Remy', 'Wilbur']
    pakuri_list.sort(key=lambda x: x.level)
    print(pakuri_list)  # debugging
    print([pakuri.name for pakuri in pakuri_list])  # debugging
    assert [pakuri.name for pakuri in pakuri_list] == EXPECTED

@pytest.mark.sorting
def test_sorting_numpy():
    """Tests for customized sorting of Pakuri (numpy version))"""
    pakuri_np_array = np.asarray(a=[
        Pakuri(name='Remy', species='Rat', level=24),
        Pakuri(name='Otis', species='Cow', level=12),
        Pakuri(name='Gromit', species='Dog', level=6),
        Pakuri(name='Wilbur', species='Pig', level=48)],
        dtype=[('pakuri', Pakuri)])

    # sort numpy array
    pakuri_np_array = np.sort(a=pakuri_np_array, axis=None, kind='quicksort', order='pakuri')
    print(pakuri_np_array) # debugging
    EXPECTED = ['Gromit', 'Otis', 'Remy', 'Wilbur']
    print(pakuri_np_array) # debugging
    assert [pakuri[0].name for pakuri in pakuri_np_array] == EXPECTED

    # sort numpy array reversed
    EXPECTED = ['Wilbur', 'Remy', 'Otis', 'Gromit']
    pakuri_np_array = pakuri_np_array[::-1]
    print(pakuri_np_array)  # debugging
    print([pakuri[0].name for pakuri in pakuri_np_array])  # debugging
    assert [pakuri[0].name for pakuri in pakuri_np_array] == EXPECTED
    assert np.flip(m=pakuri_np_array, axis=None).tolist() == pakuri_np_array[::-1].tolist()
