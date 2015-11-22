#reinitializes the values so we can start the test
restart
wave add /

isim force add clk 1 -value 0 -time 5 ns -repeat 10 ns
isim force add data 1 -value 0 -time 7 ns -repeat 13 ns

run 50 ms