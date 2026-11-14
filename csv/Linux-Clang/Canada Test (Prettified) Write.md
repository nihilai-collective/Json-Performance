
----
### Canada Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4930.57 | 1.17709 | 8056.95ms | 6661897 | 160 | 3.68077e+10 | 1.28855e+06 | 0.805883 | 1.02403 | 2.92475 | 0.261245 | 7.50002e-05 | 0.0280622 | 0.00013267 | 1(Win) | true |
| Glaze | 3180.13 | 0.640603 | 6269.13ms | 6661897 | 160 | 2.62061e+10 | 1.9978e+06 | 1.1331 | 1.58937 | 4.23031 | 0.469317 | 8.66608e-05 | 0.0631054 | 0.00512381 | 2(Loss) | true |
