
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3633.79 | 0.123409 | 949.635ms | 7932 | 40 | 263.999 | 2081.72 | 0.0332367 | 1.47201 | 6.14183 | 0.980585 | 0.000658724 | 2.83661e-05 | 0 | 1(Win) | true |
| Jsonifier | 2991.97 | 0.155161 | 986.634ms | 7932 | 640 | 9849.04 | 2528.28 | 0.00673675 | 1.73442 | 6.29501 | 1.38944 | 0.000969372 | 2.40324e-05 | 4.92467e-06 | 2(Loss) | true |
| simdjson (reflection) | 2700.76 | 0.0744419 | 1013.14ms | 7932 | 2560 | 11129.3 | 2800.89 | 0.138255 | 1.92166 | 7.86674 | 1.14713 | 0.000774996 | 0.000119423 | 7.74651e-05 | 3(Loss) | true |
| Glaze | 2550.1 | 0.129677 | 1026.55ms | 7932 | 40 | 591.881 | 2966.38 | 0.231788 | 2.04919 | 8.07526 | 1.55648 | 0.00223147 | 2.20625e-05 | 3.15179e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2338.62 | 0.0569373 | 1064.77ms | 7932 | 80 | 271.351 | 3234.62 | 0.0301517 | 2.23131 | 8.89725 | 1.50277 | 0.000803707 | 5.67322e-05 | 3.46697e-05 | 5(Loss) | true |
