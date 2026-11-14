
----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4556.54 | 0.128371 | 6894.15ms | 10548466 | 40 | 3.21295e+08 | 2.20777e+06 | 0.0246384 | 1.11978 | 3.97968 | 0.639409 | 0.0112896 | 0.0175468 | 0.00022034 | 1(Win) | true |
| simdjson (ondemand) | 3832.59 | 0.158232 | 8131.19ms | 10548466 | 40 | 6.89985e+08 | 2.6248e+06 | 0.19611 | 1.326 | 4.49725 | 0.722092 | 0.0101994 | 0.0178436 | 0.000165439 | 2(Loss) | true |
