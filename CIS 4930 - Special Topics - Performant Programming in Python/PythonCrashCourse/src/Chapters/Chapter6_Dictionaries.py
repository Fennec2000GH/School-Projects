# create dictionary
alien_0 = {'color': 'green', 'points': 5}
print(alien_0['color'])
print(alien_0['points'])

# assign variable to value in dictionary
new_points = alien_0['points']
print(f'You just earned {new_points} points!')
print(alien_0)

# adding new key-value pair
alien_0['x_position'] = 0
alien_0['y_position'] = 25
print(alien_0)

# starting with empty dictionary
alien_0 = {}
alien_0['color'] = 'green'
alien_0['points'] = 5
print(alien_0)

# modifying values in dictionary
alien_0['color'] = 'green'
print(f"The alien is {alien_0['color']}.")
alien_0['color'] = 'yellow'
print(f"The alien is now {alien_0['color']}.")

# more practice
alien_0 = {'x_position': 0, 'y_position': 25, 'speed': 'medium'}
print(f"Original position: {alien_0['x_position']}")

# Move the alien to the right.
# Determine how far to move the alien based on its current speed.
if alien_0['speed'] == 'slow':
    x_increment = 1
elif alien_0['speed'] == 'medium':
    x_increment = 2
else:
    # This must be a fast alien.
    x_increment = 3

# The new position is the old position plus the increment. v
alien_0['x_position'] = alien_0['x_position'] + x_increment
print(f"New position: {alien_0['x_position']}")
alien_0['speed'] = 'fast'

# removing key-value pairs
alien_0 = {'color': 'green', 'points': 5}
print(alien_0)
del alien_0['points']
print(alien_0)

# dictionary of similar objects
favorite_languages = {
    'jen': 'python',
    'sarah': 'c',
    'edward': 'ruby',
    'phil': 'python'
}
language = favorite_languages['sarah'].title()
print(f"Sarah's favorite language is {language}.")

# accesssing values in dictionary
alien_0 = {'color': 'green', 'speed': 'slow'}
point_value = alien_0.get('points', 'No point values assigned.')
print(point_value)

# looping through dictionary
# both keys and values
user_0 = {
    'username': 'efermi',
    'first': 'enrico',
    'last': 'fermi'
}
for key, value in user_0.items():
    print(f'\nKey: {key}')
    print(f'Value: {value}')

for name, language in favorite_languages.items():
    print(f"{name.title()}'s favorite language is {language.title()}.")

# keys only
for name in favorite_languages.keys():
    print(name.title())

friends = ['phil', 'sarah']
for name in favorite_languages.keys():
    print(name.title())

    if name in friends:
        language = favorite_languages[name].title()
        print(f'\t{name.title()}, I see you love {language}!')

if 'erin' not in favorite_languages.keys():
    print('Erin, please take our poll!')

# sorted keys
for name in sorted(favorite_languages.keys()):
    print(f'{name.title()}, thank you for taking the poll.')

# values only
print("The following languages have been mentioned:")
for language in favorite_languages.values():
    print(language.title())

# using set
for language in set(favorite_languages.values()):
    print(language.title())

# nesting
# list of dictionaries
alien_0 = {'color': 'green', 'points': 5}
alien_1 = {'color': 'yellow', 'points': 10}
alien_2 = {'color': 'red', 'points': 15}
aliens = [alien_0, alien_1, alien_2]
for alien in aliens:
    print(alien)

# list in dicitonary
pizza = {
    'crust': 'thick',
    'toppings': ['mushrooms', 'extra cheese']
}
print(f"You ordered a {pizza['crust']}-crust pizza with the following toppings:")
for topping in pizza['toppings']:
    print("\t" + topping)

favorite_languages = {
    'jen': ['python', 'ruby'],
    'sarah': ['c'],
    'edward': ['ruby', 'go'], 'phil': ['python', 'haskell']
}
for name, languages in favorite_languages.items():
    print(f"\n{name.title()}'s favorite languages are:")
    for language in languages:
        print(f"\t{language.title()}")

# dictionary in dictionary
users = {
    'aeinstein': {
        'first': 'albert',
        'last': 'einstein',
        'location': 'princeton'
    },
    'mcurie': {
        'first': 'marie',
        'last': 'curie',
        'location': 'paris'
    }
}

for username, user_info in users.items():
    print(f"\nUsername: {username}")
    full_name = f"{user_info['first']}" f"{user_info['last']}"
    location = user_info['location']
    print(f"\tFull name: {full_name.title()}")
    print(f"\tLocation: {location.title()}")


