
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1104.84 | 0.0497347 | 1126.96ms | 4630 | 2560 | 10114 | 3996.53 | 0.0212045 | 4.6753 | 21.73 | 4.43866 | 0.00491774 | 0.000159709 | 7.90531e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 916.162 | 0.0495621 | 1209.61ms | 4630 | 2560 | 14606.8 | 4819.57 | 0.0121641 | 5.58343 | 24.4181 | 4.75896 | 0.0056223 | 7.05319e-05 | 2.48043e-05 | 2(Loss) | true |
| Glaze | 770.369 | 0.11332 | 1303.37ms | 4630 | 1280 | 53999.2 | 5731.68 | 0.263678 | 6.59841 | 30.1328 | 5.74687 | 0.00542285 | 8.89241e-05 | 3.29036e-05 | 3(Loss) | true |
| simdjson (reflection) | 749.807 | 0.107387 | 1320.45ms | 4630 | 320 | 12797.3 | 5888.87 | 0.261609 | 6.78347 | 27.8104 | 5.11426 | 0.00949784 | 4.52214e-05 | 1.34989e-05 | 4(Loss) | true |
| simdjson (ondemand) | 671.766 | 0.0561006 | 1392.55ms | 4630 | 1280 | 17404.9 | 6572.99 | 0.0242292 | 7.58288 | 30.8244 | 5.94255 | 0.00684969 | 0.000230832 | 0.000114572 | 5(Loss) | true |
