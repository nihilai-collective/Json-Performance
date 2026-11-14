
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 887.517 | 0.0709683 | 6948.13ms | 4197496 | 40 | 4.09842e+08 | 4.51038e+06 | 0.200862 | 5.73985 | 27.6973 | 5.68588 | 0.000882228 | 0.0819066 | 0.00238885 | 1(Win) | true |
| simdjson (ondemand) | 854.754 | 0.134261 | 7186.97ms | 4197496 | 80 | 3.16293e+09 | 4.68327e+06 | 0.0495038 | 5.92144 | 30.2757 | 5.38904 | 0.00579674 | 0.081399 | 0.00319579 | 2(Loss) | true |
