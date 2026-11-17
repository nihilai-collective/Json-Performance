
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 728.8 | 0.147873 | 8502.12ms | 2090234 | 40 | 6.54353e+08 | 2.73519e+06 | 0.0167317 | 6.92031 | 33.851 | 7.0314 | 0.0225314 | 0.155594 | 5.5257e-05 | 1(Win) | true |
| simdjson (ondemand) | 724.105 | 0.235693 | 8547.52ms | 2090234 | 80 | 3.368e+09 | 2.75292e+06 | 0.188012 | 6.98442 | 34.6601 | 6.57596 | 0.0232925 | 0.180978 | 0.000135445 | 2(Loss) | true |
