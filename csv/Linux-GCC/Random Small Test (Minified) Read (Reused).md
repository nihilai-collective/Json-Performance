
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1928.51 | 0.039423 | 1034.64ms | 5094 | 2560 | 2524.71 | 2519.05 | 0.122794 | 2.71597 | 11.4798 | 1.8247 | 0.000572595 | 4.66235e-05 | 6.28803e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1809.6 | 0.0623801 | 1052.29ms | 5094 | 320 | 897.417 | 2684.58 | 0.16862 | 2.89224 | 12.7809 | 2.01649 | 0.00146005 | 4.96908e-05 | 3.6808e-06 | 2(Loss) | true |
| Glaze | 1597.57 | 0.120224 | 1086.6ms | 5094 | 640 | 8553.82 | 3040.88 | 0.171172 | 3.26756 | 14.0726 | 2.58402 | 0.00517367 | 3.58878e-05 | 1.28828e-05 | 3(Loss) | true |
| simdjson (reflection) | 1405.94 | 0.0941913 | 1138.48ms | 5094 | 2560 | 27117.3 | 3455.35 | 0.113336 | 3.70811 | 15.1869 | 2.42638 | 0.00306749 | 7.53031e-05 | 2.29283e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1299.71 | 0.118219 | 1156.59ms | 5094 | 80 | 1562.03 | 3737.76 | 0.0230806 | 4.00984 | 14.6211 | 2.319 | 0.00299617 | 3.19003e-05 | 0 | 5(Loss) | true |
