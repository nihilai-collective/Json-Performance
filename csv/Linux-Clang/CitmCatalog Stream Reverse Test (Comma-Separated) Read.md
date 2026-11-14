
----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 786.172 | 0.115928 | 8620.15ms | 4525119 | 40 | 1.61981e+09 | 5.48924e+06 | 0.104583 | 6.49996 | 31.75 | 6.41969 | 0.0155753 | 0.0787093 | 0.00361472 | 1(Win) | true |
| simdjson (ondemand) | 526.876 | 0.0771136 | 5949.91ms | 4525119 | 30 | 1.19682e+09 | 8.19072e+06 | 0.383178 | 9.75272 | 47.8417 | 9.07322 | 0.0268003 | 0.0947277 | 0.00482519 | 2(Loss) | true |
