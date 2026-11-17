
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2211.26 | 0.0404411 | 1087.84ms | 8051 | 4890 | 9642.17 | 3472.24 | 0.00367392 | 2.30076 | 10.1353 | 1.63284 | 0.000931866 | 4.98611e-05 | 2.10062e-05 | 1(Win) | true |
| Jsonifier | 1910.07 | 0.0366601 | 1138.81ms | 8051 | 4890 | 10619.4 | 4019.77 | 0.0352527 | 2.66654 | 11.1009 | 2.0908 | 0.00183262 | 4.72702e-05 | 1.86693e-05 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1604.23 | 0.0395807 | 1221.3ms | 8051 | 4890 | 17548.5 | 4786.11 | 0.133283 | 3.14579 | 10.6683 | 1.69309 | 0.00192071 | 5.28075e-05 | 2.18698e-05 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1602.74 | 0.0341106 | 1216.17ms | 8051 | 4890 | 13057.5 | 4790.56 | 0.126033 | 3.17142 | 13.5927 | 2.61123 | 0.00362231 | 4.51112e-05 | 1.56721e-05 | 3(Tie) | true |
| simdjson (ondemand) | 1591.53 | 0.0468132 | 1224.38ms | 8051 | 2560 | 13057 | 4824.3 | 0.0523829 | 3.17814 | 11.5345 | 1.87356 | 0.00282171 | 4.84703e-05 | 1.94075e-05 | 5(Loss) | true |
