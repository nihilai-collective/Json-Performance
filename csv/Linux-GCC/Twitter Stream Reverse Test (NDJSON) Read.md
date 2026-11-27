
----
### Twitter Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 771.051 | 0.0950985 | 8381.2ms | 4219120 | 80 | 1.97022e+09 | 5.21842e+06 | 1.55184 | 6.58761 | 26.1127 | 4.7654 | 0.0222817 | 0.0535131 | 0.00304413 | 1(Win) | true |
| simdjson (ondemand) | 316.305 | 0.134053 | 9214.54ms | 4219120 | 40 | 1.16318e+10 | 1.27208e+07 | 0.695013 | 16.017 | 61.8949 | 12.5267 | 0.0878033 | 0.0539878 | 0.015391 | 2(Loss) | true |
