
from collections import namedtuple

# collections.namedtuple(typename, field_names, *, rename=False, defaults=None, module=None)
# Returns a new tuple subclass named typename. The new subclass is used to create tuple-like objects that have fields
# accessible by attribute lookup as well as being indexable and iterable. Instances of the subclass also have a helpful
# docstring (with typename and field_names) and a helpful __repr__() method which lists the tuple contents in a name=value
# format. The field_names are a sequence of strings such as ['x', 'y']. Alternatively, field_names can be a single string
# with each fieldname separated by whitespace and/or commas, for example 'x y' or 'x, y'. Any valid Python identifier may
# be used for a fieldname except for names starting with an underscore. Valid identifiers consist of letters, digits, and
# underscores but do not start with a digit or underscore and cannot be a keyword such as class, for, return, global, pass,
# or raise. If rename is true, invalid fieldnames are automatically replaced with positional names. For example,
# ['abc', 'def', 'ghi', 'abc'] is converted to ['abc', '_1', 'ghi', '_3'], eliminating the keyword def and the duplicate
# fieldname abc. defaults can be None or an iterable of default values. Since fields with a default value must come after
# any fields without a default, the defaults are applied to the rightmost parameters. For example, if the fieldnames are
# ['x', 'y', 'z'] and the defaults are (1, 2), then x will be a required argument, y will default to 1, and z will
# default to 2.If module is defined, the __module__ attribute of the named tuple is set to that value. Named tuple instances
# do not have per-instance dictionaries, so they are lightweight and require no more memory than regular tuples.

Address = namedtuple(typename='Address',
           field_names=['Street_No', 'Street', 'APT', 'City', 'State', 'Zip_Code'],
           rename=False,
           defaults=[None, None, None, None, None, None],
           module=None
        )

UF_address = Address(Street_No=245, Street='Gale Lemerand Dr.', APT=None, City='Gainesville', State='FL', Zip_Code=32611)
print(UF_address)
print(type(UF_address))

# classmethod somenamedtuple._make(iterable)
# Class method that makes a new instance from an existing sequence or iterable.
best_buy = Address._make(iterable=[3750, 'SW Archer Rd.', None, 'Gainesville', 'FL', 32608])

# somenamedtuple._asdict()
# Return a new dict which maps field names to their corresponding values:
print(best_buy._asdict())

# somenamedtuple._replace(**kwargs)
# Return a new instance of the named tuple replacing specified fields with new values:
default_address = Address()
print(default_address)
default_address = default_address._replace(Street_No='0000', Street='Street St.', APT=None, City=None, State=None, Zip_Code=None)
print(default_address)

# somenamedtuple._fields
# Tuple of strings listing the field names. Useful for introspection and for creating new named tuple types from existing named tuples.
print(Address._fields)

# somenamedtuple._field_defaults
# Dictionary mapping field names to default values.
print(Address._field_defaults)
