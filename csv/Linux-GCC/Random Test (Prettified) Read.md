
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1628.96 | 0.0610069 | 5530.31ms | 728486 | 160 | 1.08318e+07 | 426492 | 0.05951 | 3.10193 | 12.7204 | 2.19876 | 0.0149068 | 0.0749189 | 4.80534e-05 | 1(Win) | true |
| Jsonifier | 1499.79 | 0.0282757 | 5992.77ms | 728486 | 640 | 1.09797e+07 | 463225 | 0.112912 | 3.36591 | 13.411 | 2.59403 | 0.0126257 | 0.0415664 | 7.19064e-05 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1473.17 | 0.22534 | 6074.86ms | 728486 | 80 | 9.03452e+07 | 471595 | 0.0108132 | 3.39449 | 13.4126 | 2.30412 | 0.00802258 | 0.0764095 | 7.05916e-05 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1470.56 | 0.0758953 | 6114.37ms | 728486 | 640 | 8.22781e+07 | 472430 | 0.292138 | 3.41852 | 12.3394 | 2.08009 | 0.00709085 | 0.0583537 | 5.69911e-05 | 3(Tie) | true |
| Glaze | 1435.7 | 0.0377536 | 6268.64ms | 728486 | 640 | 2.13606e+07 | 483903 | 0.0633313 | 3.51864 | 15.2108 | 2.98489 | 0.0148749 | 0.0314392 | 9.33336e-05 | 5(Loss) | true |
