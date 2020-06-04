import hashlib
import math
import pytest
from pakuri import Pakuri

########################################################################################################################
@pytest.mark.primary
@pytest.mark.parametrize(argnames=['name', 'species', 'level'], argvalues=[
    ('Adam', 'Aardvark', 0),
    ('Berry', 'Bear', 1),
    ('Can Can', 'Crow', 2),
    ('Darren', 'Dolphin', 3)])
def test_init(name: str, species: str, level: int):
    """Tests initialization of Pakuri objects"""
    Pakuri(name=name, species=species, level=level)
    assert True

@pytest.mark.primary
@pytest.mark.property
@pytest.mark.parametrize(argnames=['pakuri', 'EXPECTED'], argvalues=[
    (Pakuri(name='Adam', species='Aardvark', level=0), 'Adam'),
    (Pakuri(name='Berry', species='Bear', level=1), 'Berry'),
    (Pakuri(name='Can Can', species='Crow', level=2), 'Can Can'),
    (Pakuri(name='Darren', species='Dolphin', level=3), 'Darren')])
def test_name(pakuri: Pakuri, EXPECTED: str):
    """Tests for name property getter"""
    assert pakuri.name == EXPECTED


@pytest.mark.primary
@pytest.mark.property
@pytest.mark.parametrize(argnames=['pakuri', 'EXPECTED'], argvalues=[
    (Pakuri(name='Adam', species='Aardvark', level=0), 'Aardvark'),
    (Pakuri(name='Berry', species='Bear', level=1), 'Bear'),
    (Pakuri(name='Can Can', species='Crow', level=2), 'Crow'),
    (Pakuri(name='Darren', species='Dolphin', level=3), 'Dolphin')])
def test_species(pakuri: Pakuri, EXPECTED: str):
    """Tests for species property getter"""
    assert pakuri.species == EXPECTED


@pytest.mark.primary
@pytest.mark.property
@pytest.mark.parametrize(argnames=['pakuri', 'EXPECTED'], argvalues=[
    (Pakuri(name='Adam', species='Aardvark', level=0), 0),
    (Pakuri(name='Berry', species='Bear', level=1), 1),
    (Pakuri(name='Can Can', species='Crow', level=2), 2),
    (Pakuri(name='Darren', species='Dolphin', level=3), 3)])
def test_level(pakuri: Pakuri, EXPECTED: int):
    """Tests for level property getter"""
    assert pakuri.level == EXPECTED


########################################################################################################################
# helper function
def get_attribute(attribute: str, species: str, name: str):
    """Computes either 'Attack', 'Defense', or 'Stamina'"""
    try:
        if attribute not in ['Attack', 'Defense', 'Stamina']:
            raise ValueError('Invalid attribute!')
    except ValueError as error:
        print(str(error))

    # needed variables
    species_part = None
    individual_part = None

    # computing correct attribute value
    if attribute == 'Attack':
        species_part = int.from_bytes(bytes=hashlib.md5(species.encode()).digest(), byteorder='little') % 16
        individual_part = int.from_bytes(bytes=hashlib.md5(name.encode()).digest(), byteorder='little') % 16
    elif attribute == 'Defense':
        species_part = (int.from_bytes(bytes=hashlib.md5(species.encode()).digest(), byteorder='little') + 5) % 16
        individual_part = (int.from_bytes(bytes=hashlib.md5(name.encode()).digest(), byteorder='little') + 5) % 16
    elif attribute == 'Stamina':
        species_part = (int.from_bytes(bytes=hashlib.md5(species.encode()).digest(), byteorder='little') + 11) % 16
        individual_part = (int.from_bytes(bytes=hashlib.md5(name.encode()).digest(), byteorder='little') + 11) % 16

    return species_part + individual_part


@pytest.mark.primary
@pytest.mark.attribute
@pytest.mark.parametrize(argnames=['pakuri', 'EXPECTED'], argvalues=[
    (Pakuri(name='Adam', species='Aardvark', level=0),
     get_attribute(attribute='Attack', species='Aardvark', name='Adam')),
    (Pakuri(name='Berry', species='Bear', level=1), get_attribute(attribute='Attack', species='Bear', name='Berry')),
    (
    Pakuri(name='Can Can', species='Crow', level=2), get_attribute(attribute='Attack', species='Crow', name='Can Can')),
    (Pakuri(name='Darren', species='Dolphin', level=3),
     get_attribute(attribute='Attack', species='Dolphin', name='Darren'))])
def test_attack(pakuri: Pakuri, EXPECTED: int):
    """Tests for attack attribute setter"""
    print(pakuri.get_attack())
    print(EXPECTED)
    assert pakuri.get_attack() == EXPECTED


@pytest.mark.primary
@pytest.mark.attribute
@pytest.mark.parametrize(argnames=['pakuri', 'EXPECTED'], argvalues=[
    (Pakuri(name='Adam', species='Aardvark', level=0),
     get_attribute(attribute='Defense', species='Aardvark', name='Adam')),
    (Pakuri(name='Berry', species='Bear', level=1), get_attribute(attribute='Defense', species='Bear', name='Berry')),
    (Pakuri(name='Can Can', species='Crow', level=2),
     get_attribute(attribute='Defense', species='Crow', name='Can Can')),
    (Pakuri(name='Darren', species='Dolphin', level=3),
     get_attribute(attribute='Defense', species='Dolphin', name='Darren'))])
def test_defense(pakuri: Pakuri, EXPECTED: int):
    """Tests for defense attribute setter"""
    print(pakuri.get_defense())
    print(EXPECTED)
    assert pakuri.get_defense() == EXPECTED


@pytest.mark.primary
@pytest.mark.attribute
@pytest.mark.parametrize(argnames=['pakuri', 'EXPECTED'], argvalues=[
    (Pakuri(name='Adam', species='Aardvark', level=0),
     get_attribute(attribute='Stamina', species='Aardvark', name='Adam')),
    (Pakuri(name='Berry', species='Bear', level=1), get_attribute(attribute='Stamina', species='Bear', name='Berry')),
    (Pakuri(name='Can Can', species='Crow', level=2),
     get_attribute(attribute='Stamina', species='Crow', name='Can Can')),
    (Pakuri(name='Darren', species='Dolphin', level=3),
     get_attribute(attribute='Stamina', species='Dolphin', name='Darren'))])
def test_stamina(pakuri: Pakuri, EXPECTED: int):
    """Tests for defense attribute setter"""
    print(pakuri.get_stamina())
    print(EXPECTED)
    assert pakuri.get_stamina() == EXPECTED


########################################################################################################################
# helper function
def get_hp(name: str, species: str, level: int):
    """Computes hp"""
    stamina = get_attribute(attribute='Stamina', species=species, name=name)
    return math.floor(stamina * level / 6)


# helper funciton
def get_cp(name: str, species: str, level: int):
    """Computes cp"""
    attack = get_attribute(attribute='Attack', species=species, name=name)
    defense = get_attribute(attribute='Defense', species=species, name=name)
    stamina = get_attribute(attribute='Stamina', species=species, name=name)
    return math.floor(attack * math.sqrt(defense) * math.sqrt(stamina) * level * 0.08)


@pytest.mark.secondary
@pytest.mark.parametrize(argnames=['pakuri'], argvalues=[
    (Pakuri(name='Adam', species='Aardvark', level=0),),
    (Pakuri(name='Berry', species='Bear', level=1),),
    (Pakuri(name='Can Can', species='Crow', level=2),),
    (Pakuri(name='Darren', species='Dolphin', level=3),)])
def test_hp(pakuri: Pakuri):
    """Tests for health points (HP) propertyr"""
    EXPECTED = get_hp(name=pakuri.name, species=pakuri.species, level=pakuri.level)
    print(pakuri.hp)
    print(EXPECTED)
    assert pakuri.hp == EXPECTED


@pytest.mark.secondary
@pytest.mark.parametrize(argnames=['pakuri'], argvalues=[
    (Pakuri(name='Adam', species='Aardvark', level=0),),
    (Pakuri(name='Berry', species='Bear', level=1),),
    (Pakuri(name='Can Can', species='Crow', level=2),),
    (Pakuri(name='Darren', species='Dolphin', level=3),)])
def test_cp(pakuri: Pakuri):
    """Tests for combat power (CP) property"""
    EXPECTED = get_cp(name=pakuri.name, species=pakuri.species, level=pakuri.level)
    print(pakuri.cp)
    print(EXPECTED)
    assert pakuri.cp == EXPECTED
