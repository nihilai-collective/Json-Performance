
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1585.38 | 0.111887 | 8144.45ms | 4197496 | 40 | 3.19254e+08 | 2.52498e+06 | 0.00372657 | 3.21085 | 15.7568 | 3.07156 | 0.000503884 | 0.0819465 | 0.000678345 | 1(Win) | true |
| simdjson (ondemand) | 1360.29 | 0.0482855 | 9436.45ms | 4197496 | 160 | 3.23051e+08 | 2.94279e+06 | 0.0703152 | 3.71807 | 18.5659 | 2.76464 | 0.00881265 | 0.0817383 | 0.00165708 | 2(Loss) | true |
