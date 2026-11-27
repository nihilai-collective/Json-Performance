
----
### Stream Formats Large Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Large%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 19875.4 | 0.234865 | 5077.89ms | 16197085 | 40 | 1.33271e+08 | 777177 | 0.968125 | 0.254806 | 1.17451 | 0.0719474 | 6.98845e-05 | 0.0157249 | 0.000479381 | 1(Win) | true |
| simdjson (ondemand) | 16463.9 | 0.988676 | 6076.43ms | 16197085 | 80 | 6.88342e+09 | 938217 | 0.298962 | 0.309457 | 1.32914 | 0.0888035 | 0.000120816 | 0.0157682 | 0.000634365 | 2(Loss) | true |
