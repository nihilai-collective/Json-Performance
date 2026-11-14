
----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 877.086 | 0.0862257 | 7006.43ms | 4197495 | 30 | 4.64613e+08 | 4.56403e+06 | 0.0126483 | 5.78477 | 27.6255 | 5.73481 | 0.000845242 | 0.084265 | 0.000247949 | 1(Win) | true |
| simdjson (ondemand) | 684.639 | 0.0641586 | 9031.99ms | 4197495 | 80 | 1.12579e+09 | 5.84694e+06 | 0.479813 | 7.45107 | 35.9674 | 7.16649 | 0.00833553 | 0.103462 | 0.00120874 | 2(Loss) | true |
