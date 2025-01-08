require random.fs

: genarray { u -- addr }
    u 2* cells allocate throw { a }
    a u 2* cells bounds ?do
        rnd rnd <<# `#s #36 base-execute #>
        drop i 4 rshift #15 and 7 + save-mem #>> i 2!
    2 cells +loop
    a ;

: genfile { u1 u2 addr -- }
    \ generate u2 random number pairs up to u1 and print names from addr
    u2 0 do
        u1 random 2* cells addr + 2@ type ', emit
        u1 random 2* cells addr + 2@ type cr
    loop ;

: main { u1 u2 -- }
    \ generate u2 random number pairs up to u1
    u1 genarray { a }
    u1 u2 a `genfile "f1.csv" w/o create-file throw outfile-execute
    u1 u2 a `genfile "f2.csv" w/o create-file throw outfile-execute
    u1 u2 a `genfile "f3.csv" w/o create-file throw outfile-execute
    u1 u2 a `genfile "f4.csv" w/o create-file throw outfile-execute ;

: main5 { u1 u2 u3 u4 u5 -- }
    \ generate u1 random strings, and then files containing u2..u5
    \ records of two fields each, with each field being randomly
    \ chosen from the strings
    u1 genarray { a }
    u1 u2 a `genfile "f1.csv" w/o create-file throw outfile-execute
    u1 u3 a `genfile "f2.csv" w/o create-file throw outfile-execute
    u1 u4 a `genfile "f3.csv" w/o create-file throw outfile-execute
    u1 u5 a `genfile "f4.csv" w/o create-file throw outfile-execute ;
