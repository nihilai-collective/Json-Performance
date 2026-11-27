
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2159.07 | 0.267492 | 8438.17ms | 728486 | 320 | 2.37073e+08 | 321777 | 0.10473 | 2.33944 | 10.7925 | 2.0408 | 0.00588458 | 0.0403292 | 2.49361e-05 | 1(Win) | true |
| simdjson (reflection) | 1764.92 | 0.197204 | 5127.88ms | 728486 | 160 | 9.64153e+07 | 393638 | 0.13894 | 2.85418 | 12.2623 | 2.04325 | 0.00751254 | 0.0576742 | 0.000214984 | 2(Loss) | true |
| Jsonifier (two-stage) | 1601.08 | 0.704136 | 5625.3ms | 728486 | 640 | 5.97461e+09 | 433918 | 0.0820229 | 3.16868 | 13.3802 | 2.24404 | 0.0160075 | 0.0723827 | 0.000165448 | 3(Loss) | true |
| simdjson (ondemand) | 1492.41 | 0.222422 | 6024.03ms | 728486 | 320 | 3.43063e+08 | 465515 | 0.00512362 | 3.38145 | 13.3501 | 2.28171 | 0.00863794 | 0.0740479 | 7.74337e-05 | 4(Loss) | true |
| Glaze | 1436.79 | 0.199938 | 6262.11ms | 728486 | 640 | 5.98173e+08 | 483535 | 0.295815 | 3.537 | 15.1964 | 2.98069 | 0.0145905 | 0.0325081 | 0.000322831 | 5(Loss) | true |
