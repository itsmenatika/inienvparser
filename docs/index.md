

# .ini file

## basics

you can create a key-value pair using ``KEY=VALUE``. The value will be always interpreted as a ``std::string``. 

an example:
```
name=adam
age=23
country = germany
```

Any leading and trailing space will be cut off. 
There's no difference between ``country = germany`` and ``country=germany``.


## comments

you can add comments to your file by using either ``;`` or ``#``.
There's no multiline comments.

an example:
```
# that's a comment
; that's also a comment
name=adam
age=23
country = germany # everything after # is also a comment
```


In the future you will also be able to write those symbols by using ``\#`` and ``\;``.
It is yet to be implemented

## groups

you can organize your data into groups, like that:
```
# that's a comment
; that's also a comment
[person]
name=adam
age=23
[country]
country = germany # everything after # is also a comment
```

using ``[]`` will set the current group to ``default`` which is also a defaultly used group



# functions

* mergeResults -> allows you to merge results
* mergeGroups -> allows you to merge groups
* isIniError -> checks if there was an error in a result
* getGroup -> gets a group from a result
* getValue -> gets a value from a group
* getValueQuick -> gets a value from a result
* initIniFile -> loads a file and returns a result

