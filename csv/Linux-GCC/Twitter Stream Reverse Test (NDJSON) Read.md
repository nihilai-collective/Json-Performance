
----
### Twitter Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 722.836 | 0.109166 | 8806.03ms | 4219120 | 80 | 2.95414e+09 | 5.5665e+06 | 0.100603 | 7.07129 | 27.3303 | 5.16271 | 0.020239 | 0.0569465 | 0.00121388 | 1(Win) | true |
| simdjson (ondemand) | 330.305 | 0.0725056 | 8716.29ms | 4219120 | 40 | 3.12044e+09 | 1.21817e+07 | 0.100313 | 15.2825 | 61.9272 | 12.5319 | 0.0829527 | 0.0548194 | 0.00801171 | 2(Loss) | true |
