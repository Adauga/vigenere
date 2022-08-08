
# Vigenere Decrypter

The library that implements vigenere encrypt/decrypt (with/without key).



## Appendix

Used recommendation from article (https://www.cipherchallenge.org/wp-content/uploads/2020/12/Five-ways-to-crack-a-Vigenere-cipher.pdf)

Implemented Variational method (#4) with tethragram frequency statistic table.

Tethragram statistic table was initialized by "romeo and juliet" and "machbet" novels. 
## Installation

Install with cmake

Supported_platform: Linux

```bash
  cmake . -Bbuild -DWITH_MEMCHECK=ON
  cd build
  make vigenere_run //OR make vigenere-run-tests
```
    
## Running Tests

To run tests, run the following command

```bash
  make utest_alphabet
  make utest_frequency
  make utest_key
  make vigenere
  
  OR
  
  make vigenere-run-tests
```


## Usage/Examples

```javascript
make vigenere_run
./vigenere_run "/home/adauga/AdaProjects/Vigenere/cmake-build-debug/encrypted_text.txt"

 Founded key = birdsign
 Decrypted text = EventhoughtheyarelittlebitmoreverbosethepertargetcommandsallowareasonablyfinegrainedcontroloverthedifferentbuildoptionsandinmypersonalexperiencearetheleastlikelytocauseheadachesinthelongruninteractiveusecasesaredefinedintermsoflinesofinputItsraretoseeacasewhereifenoughobjectsarenotfoundmorelineswillsolvetheproblemyetthatsthedefaultmodeforscanfIfauserdidntknowtoenteranumberonthefirstlineasecondandthirdlinewillprobablynothelp
Process finished with exit code 0
```


## Roadmap

- Add more method for finding best fitness of decrypted_text

- Add more english texts from different themes for frequency table

- Add mono, dia, three - grams for decrypting meaningless text


![Logo](https://upload.wikimedia.org/wikipedia/commons/1/14/Bathingbayc_a_mechanical_dove_by_beeple_low_camera_angle_cute_2daa1f69-e280-45d0-956d-8b89208ac53e.png)

## Authors

- Dmitriy Popov.
- Elapsed time: 14 h 25 m (29 pomodoros).
- IDE: CLion 2021.1, Sublime 3
- gcc 9.4.0

