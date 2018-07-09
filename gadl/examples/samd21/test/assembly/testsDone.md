
Datasheet: [`ARM DDI 0403E.b`](file:///Users/briday-m/ownCloud/datasheet/Cortex/DDI0403E_B_armv7m_arm.pdf)
Update:2017/03/08

# OK
* Load Multiple and Store Multiple p. 142

```sh
./manyTests.py -v -fr 0xe8800000 -tr 0xe8bfffff
./manyTests.py -v -fr 0xe9000000 -tr 0xe9400000
```

dual with update
```
./manyTests.py -v -fr 0xe9400000 -tr 0xe9500000
```

Load store exclusive.
les instructions avec 'pc' en Rt ne passent pas… mais c'est marqué unpredictable sur la datasheet => exception

```
./manyTests.py -fr 0xe8400000 -tr 0xe8500000
```

# En cours:

```
./manyTests.py -v -fr 0xe9800000 -tr 0xe98b0000
```

Table Branch:
```
./manyTests.py -v -fr 0xe9800000 -tr 0xe98b0000
```

# Fail

```
./compileTest.py -fr 0xe9800000 -tr 0xe9820000
```

Les loads/store exclusives ne sont pas complets!!!

```
h:'no syntax for cortexM0Plus_Rd_Rn_Rt_byte_exclusive_imm10_load'	o:'ldrexb	r2, [r0]' => opcode e8d0 2f4f
```

# Ok

Load byte memory hints. A5-146

4 lignes pour 4 valeurs de op1 => Ok (15/5/18)
```
 ./manyTests.py -v -fr 0xf8100000 -tr 0xf81fffff
 ./manyTests.py -v -fr 0xf8900000 -tr 0xf89fffff
 ./manyTests.py -v -fr 0xf9100000 -tr 0xf91fffff
 ./manyTests.py -v -fr 0xf9900000 -tr 0xf99fffff
```

Load half memory hints. A5-146

4 lignes pour 4 valeurs de op1 (00 à 11) => Ok (15/5/18)
```
 ./manyTests.py -v -fr 0xf8300000 -tr 0xf83fffff
 ./manyTests.py -v -fr 0xf8b00000 -tr 0xf8bfffff
 ./manyTests.py -v -fr 0xf9300000 -tr 0xf93fffff
 ./manyTests.py -v -fr 0xf9b00000 -tr 0xf9bfffff
```

Load memory hints. A5-146

4 lignes pour 4 valeurs de op1 (00 à 11)
(pour op1=2 et op1= 3 => unpredictable => filtrage dans script.)
Ok le 15/5/18.
```
 ./manyTests.py -v -fr 0xf8500000 -tr 0xf85fffff
 ./manyTests.py -v -fr 0xf9500000 -tr 0xf95fffff
 ./manyTests.py -v -fr 0xf8d00000 -tr 0xf8dfffff
 ./manyTests.py -v -fr 0xf9d00000 -tr 0xf9dfffff
```

#En cours

Data processing (register) p.150

 * lsl, lsr, asr, ror
 * sxtah, sxth, uxtah, uxth, sxtab16, sxtb16, uxtab16, uxtb16, sxtab, sxtb, uxtab, uxtb
 * parallel addtion ans subtraction (signed/unsigned)
 * misc saturating
 * misc rev
 * misc sel, clz
**not all tested: this should be 0xfaf.. instead of 0xfab.. because of crc32 related instructions.**

```
./manyTests.py -v -fr 0xfa000000 -tr 0xfabfffff
```

