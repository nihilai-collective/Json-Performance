
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 407.031 | 0.111021 | 6533.94ms | 1834197 | 40 | 9.10555e+08 | 4.29752e+06 | 0.385998 | 12.5852 | 60.0116 | 13.3054 | 0.0386351 | 0.344376 | 0.00790905 | 1(Win) | true |
| simdjson (ondemand) | 271.168 | 0.180317 | 9720.94ms | 1834197 | 30 | 4.05894e+09 | 6.45072e+06 | 1.25183 | 18.7271 | 101.938 | 21.1703 | 0.0480201 | 0.790254 | 0.00566698 | 2(Loss) | true |
