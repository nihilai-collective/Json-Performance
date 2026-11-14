
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1317.27 | 0.108028 | 5230.52ms | 4525119 | 80 | 1.00201e+09 | 3.27609e+06 | 0.391645 | 3.86742 | 18.8618 | 3.5689 | 0.0104733 | 0.078078 | 0.00507569 | 1(Win) | true |
| simdjson (ondemand) | 976.021 | 0.0763324 | 7043.84ms | 4525119 | 80 | 9.11276e+08 | 4.42151e+06 | 0.798603 | 5.23603 | 22.1113 | 3.6087 | 0.0164491 | 0.0942075 | 0.00186638 | 2(Loss) | true |
