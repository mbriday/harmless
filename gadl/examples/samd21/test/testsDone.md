
Datasheet: `ARM DDI 0403E.b`
Update:2017/03/08

# OK
* Load Multiple and Store Multiple p. 142

```sh
./manyTests.py -v -fr 0xe8800000 -tr 0xe8bfffff
./manyTests.py -v -fr 0xe9000000 -tr 0xe9400000
```


# En cours:

```
./manyTests.py -v -fr 0xe9800000 -tr 0xe98b0000
```

# Fail

```
./compileTest.py -fr 0xe9800000 -tr 0xe9820000
```