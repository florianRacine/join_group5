# Join for 185.190 Efficient Programs group 5

## Installation 

### To get started with the project, follow these steps:

 ```bash
 git clone https://github.com/florianRacine/join_group5.git
 cd join_group5
 tar -xvf data.tar.xz
```

### Run make to compile the yourjoin.cpp file:
  
 ```bash
make
```

### You can run the program given as an example with the following commands:

To compare the output with the expected result:

 ```bash
./myjoin data/a.csv data/b.csv data/c.csv data/d.csv | sort | diff - data/abcd.csv
 ```

Or to just view the joined result:

 ```bash
./myjoin data/a.csv data/b.csv data/c.csv data/d.csv | sort
 ```

### Alternatively, you can try our version:

To compare the output with the expected result:

 ```bash
./yourjoin data/a.csv data/b.csv data/c.csv data/d.csv | sort | diff - data/abcd.csv
 ```

Or just view the joined result:

 ```bash
./yourjoin data/a.csv data/b.csv data/c.csv data/d.csv | sort
 ```
