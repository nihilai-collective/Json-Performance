
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 861.412 | 0.150285 | 6294.6ms | 1834197 | 40 | 3.7253e+08 | 2.03065e+06 | 0.00611261 | 5.83633 | 25.449 | 5.41699 | 0.03149 | 0.0841036 | 9.78494e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 737.414 | 0.135142 | 7405.25ms | 1834197 | 40 | 4.11064e+08 | 2.37211e+06 | 0.219733 | 6.81125 | 28.907 | 5.86207 | 0.0376877 | 0.147789 | 0.000220137 | 2(Loss) | true |
| Glaze | 660.812 | 0.0653024 | 8254.69ms | 1834197 | 30 | 8.96428e+07 | 2.64709e+06 | 0.100364 | 7.64257 | 32.3366 | 6.31554 | 0.0348532 | 0.0839919 | 3.24211e-05 | 3(Loss) | true |
| simdjson (reflection) | 623.973 | 0.0650478 | 8766.06ms | 1834197 | 40 | 1.3301e+08 | 2.80337e+06 | 0.00757781 | 8.10163 | 34.8564 | 6.51703 | 0.0370526 | 0.136536 | 0.00135055 | 4(Loss) | true |
| simdjson (ondemand) | 524.098 | 0.0661283 | 5029.5ms | 1834197 | 40 | 1.94851e+08 | 3.3376e+06 | 0.36554 | 9.62842 | 37.4491 | 7.33897 | 0.0425116 | 0.148786 | 0.000176658 | 5(Loss) | true |
