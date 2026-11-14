
----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4133.42 | 0.114978 | 7618.24ms | 10548466 | 30 | 2.34915e+08 | 2.43377e+06 | 0.357883 | 1.23815 | 4.3063 | 0.678223 | 0.00981906 | 0.0175674 | 1.10822e-05 | 1(Win) | true |
| simdjson (ondemand) | 3694.86 | 0.210208 | 8466.46ms | 10548466 | 40 | 1.31021e+09 | 2.72265e+06 | 0.0957329 | 1.37864 | 4.69 | 0.771548 | 0.00985439 | 0.0177114 | 0.000263316 | 2(Loss) | true |
