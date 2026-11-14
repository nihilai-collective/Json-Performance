
----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 818.022 | 0.0455315 | 7690.01ms | 4203059 | 80 | 3.98212e+08 | 4.90005e+06 | 0.098896 | 6.27503 | 27.6627 | 5.60198 | 0.0223246 | 0.088355 | 0.00694301 | 1(Win) | true |
| simdjson (ondemand) | 731.036 | 0.0718283 | 8575.85ms | 4203059 | 80 | 1.2409e+09 | 5.48311e+06 | 0.0653106 | 7.0022 | 27.0165 | 5.18336 | 0.0338016 | 0.0876683 | 0.00281059 | 2(Loss) | true |
