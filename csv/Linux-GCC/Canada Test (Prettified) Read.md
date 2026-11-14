
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2285.94 | 0.783071 | 6992.01ms | 5373214 | 30 | 9.24402e+09 | 2.24165e+06 | 0.0747341 | 2.20817 | 12.0777 | 2.54016 | 0.00342967 | 0.0383608 | 0.000114481 | 1(Win) | true |
| Jsonifier (two-stage) | 2187.95 | 0.681428 | 7224.98ms | 5373214 | 160 | 4.07525e+10 | 2.34206e+06 | 1.61286 | 2.29334 | 11.8653 | 2.16767 | 0.00493088 | 0.0627858 | 0.000164229 | 2(Loss) | true |
| simdjson (reflection) | 1798.5 | 0.543682 | 8841.36ms | 5373214 | 160 | 3.83935e+10 | 2.8492e+06 | 0.290379 | 2.79355 | 13.2173 | 2.31135 | 0.00466951 | 0.0627291 | 0.000155733 | 3(Loss) | true |
| simdjson (ondemand) | 1717.41 | 0.226174 | 9339.75ms | 5373214 | 160 | 7.28662e+09 | 2.98374e+06 | 0.057797 | 2.93639 | 13.6421 | 2.49435 | 0.00636792 | 0.064898 | 0.000274163 | 4(Loss) | true |
| Glaze | 1599.12 | 0.317899 | 10011.5ms | 5373214 | 160 | 1.66037e+10 | 3.20444e+06 | 0.386713 | 3.15678 | 15.9031 | 2.91921 | 0.00471263 | 0.0406742 | 0.00164064 | 5(Loss) | true |
