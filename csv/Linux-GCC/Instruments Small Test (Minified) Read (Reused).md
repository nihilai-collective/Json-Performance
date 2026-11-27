
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3613.21 | 0.332775 | 842.71ms | 4669 | 320 | 5381.62 | 1232.34 | 0.114235 | 1.48508 | 6.3791 | 1.25723 | 0.000606393 | 3.54733e-05 | 2.20872e-05 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2335.65 | 0.200716 | 912.708ms | 4669 | 320 | 4685.42 | 1906.41 | 0.249845 | 2.26353 | 8.88263 | 1.65282 | 0.00100798 | 1.27169e-05 | 0 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2326.64 | 0.0614486 | 912.227ms | 4669 | 2560 | 3540.43 | 1913.8 | 0.179152 | 2.25631 | 9.48212 | 1.65839 | 0.00109549 | 3.4804e-05 | 4.76882e-06 | 2(Tie) | true |
| simdjson (reflection) | 1829.91 | 0.0410116 | 969.2ms | 4669 | 4890 | 4869.82 | 2433.29 | 0.267607 | 2.86127 | 12.081 | 1.7342 | 0.00094186 | 4.16969e-05 | 9.28545e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1533.59 | 0.0978907 | 1020.37ms | 4669 | 40 | 323.126 | 2903.45 | 0.236514 | 3.469 | 13.8604 | 2.3776 | 0.00124224 | 1.07089e-05 | 0 | 5(Loss) | true |
