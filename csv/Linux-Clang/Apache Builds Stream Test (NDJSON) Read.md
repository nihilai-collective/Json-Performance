
----
### Apache Builds Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1847.47 | 0.139584 | 8610.39ms | 4212000 | 80 | 7.36857e+08 | 2.17425e+06 | 0.0930522 | 2.74231 | 11.4589 | 2.05248 | 0.0142257 | 0.0665785 | 0.00483036 | 1(Win) | true |
| simdjson (ondemand) | 1576.13 | 0.201769 | 9841.45ms | 4212000 | 40 | 1.0577e+09 | 2.54857e+06 | 0.686275 | 3.22061 | 13.524 | 2.36416 | 0.0104417 | 0.0664632 | 0.00575842 | 2(Loss) | true |
