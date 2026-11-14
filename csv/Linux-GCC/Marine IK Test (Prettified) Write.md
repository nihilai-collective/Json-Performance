
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6296.21 | 0.0567295 | 9528.95ms | 9930848 | 160 | 1.16507e+08 | 1.50421e+06 | 0.003219 | 0.79925 | 2.51578 | 0.147546 | 0.000458831 | 0.0249905 | 0.000211577 | 1(Win) | true |
| Glaze | 3151.51 | 0.240844 | 9357.46ms | 9930228 | 30 | 1.57135e+09 | 3.00497e+06 | 0.0847554 | 1.59533 | 4.41437 | 0.474336 | 0.000695781 | 0.0757416 | 0.00806365 | 2(Loss) | true |
| simdjson (reflection) | 386.862 | 0.265972 | 7509.79ms | 10018896 | 30 | 1.29456e+11 | 2.46981e+07 | 1.00246 | 13.0261 | 38.7489 | 5.79802 | 0.0228246 | 0.3133 | 0.151331 | 3(Loss) | true |
