
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1426.47 | 0.0897098 | 5285.1ms | 4506447 | 80 | 5.84404e+08 | 3.01281e+06 | 0.055322 | 3.54292 | 15.8911 | 3.00069 | 0.00861423 | 0.0804471 | 0.00431197 | 1(Win) | true |
| simdjson (ondemand) | 1091.18 | 0.0859865 | 6671.25ms | 4506447 | 80 | 9.17548e+08 | 3.93857e+06 | 0.0571526 | 4.64347 | 18.3172 | 3.1405 | 0.0176421 | 0.0787664 | 0.00373431 | 2(Loss) | true |
