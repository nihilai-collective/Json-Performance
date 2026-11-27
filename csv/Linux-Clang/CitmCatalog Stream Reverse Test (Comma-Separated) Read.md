
----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 793.786 | 0.894143 | 8590.43ms | 4525119 | 30 | 7.08906e+10 | 5.43659e+06 | 0.172345 | 6.40307 | 31.0507 | 6.32069 | 0.0161555 | 0.0778183 | 0.00877604 | 1(Win) | true |
| simdjson (ondemand) | 526.682 | 0.18309 | 5965.24ms | 4525119 | 30 | 6.75167e+09 | 8.19372e+06 | 0.675269 | 9.61712 | 47.4756 | 9.02779 | 0.0271977 | 0.09431 | 0.00867098 | 2(Loss) | true |
