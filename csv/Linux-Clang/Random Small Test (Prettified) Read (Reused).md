
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2802.53 | 0.237399 | 1076.2ms | 8051 | 640 | 27073.1 | 2739.68 | 0.0608904 | 1.82352 | 8.32878 | 1.34927 | 0.000514494 | 2.46476e-05 | 6.98671e-06 | 1(Win) | true |
| Glaze | 2093.59 | 0.0705451 | 1166.28ms | 8051 | 4890 | 32731 | 3667.4 | 0.1013 | 2.44264 | 11.1102 | 2.11055 | 0.00307952 | 3.05567e-05 | 7.74714e-06 | 2(Loss) | true |
| Jsonifier | 1961.27 | 0.274198 | 1201.24ms | 8051 | 320 | 36872.7 | 3914.83 | 0.0114136 | 2.65448 | 10.0007 | 1.98696 | 0.00370451 | 3.72625e-05 | 1.82431e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1503.92 | 0.143433 | 1317.96ms | 8051 | 640 | 34318.5 | 5105.33 | 0.121111 | 3.39092 | 13.1701 | 2.09949 | 0.0025451 | 2.71705e-05 | 6.79263e-06 | 4(Loss) | true |
