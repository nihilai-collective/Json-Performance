
----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 825.502 | 0.0689809 | 8259.87ms | 4525120 | 80 | 1.04033e+09 | 5.22772e+06 | 0.185043 | 6.1634 | 30.694 | 6.251 | 0.0151679 | 0.0779186 | 0.00369576 | 1(Win) | true |
| simdjson (ondemand) | 626.53 | 0.0952577 | 5039.06ms | 4525120 | 30 | 1.29151e+09 | 6.88792e+06 | 0.335103 | 8.12515 | 41.228 | 8.08556 | 0.0258047 | 0.0772245 | 0.00492836 | 2(Loss) | true |
