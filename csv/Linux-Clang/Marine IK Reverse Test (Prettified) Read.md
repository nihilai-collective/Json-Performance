
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2507 | 0.088376 | 8734.46ms | 7351818 | 160 | 9.77395e+08 | 2.79667e+06 | 0.0508374 | 2.00385 | 8.81563 | 1.68859 | 0.00986932 | 0.0607929 | 0.0033769 | 1(Win) | true |
| Jsonifier | 2446.14 | 0.0762484 | 8919.43ms | 7351818 | 160 | 7.64206e+08 | 2.86625e+06 | 0.699858 | 2.0502 | 9.61495 | 2.27645 | 0.00677641 | 0.0336663 | 0.00049809 | 2(Loss) | true |
| simdjson (ondemand) | 2125.81 | 0.131828 | 10290.4ms | 7351818 | 30 | 5.67124e+08 | 3.29814e+06 | 0.00579653 | 2.36812 | 10.2109 | 1.61272 | 0.0110348 | 0.0609432 | 0.00221768 | 3(Loss) | true |
| Glaze | 2101.45 | 0.127617 | 5022.05ms | 7351818 | 80 | 1.45031e+09 | 3.33638e+06 | 0.211317 | 2.39211 | 11.0334 | 2.24385 | 0.00918008 | 0.0332305 | 0.000482335 | 4(Loss) | true |
