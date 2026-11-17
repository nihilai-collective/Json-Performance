
----
### CitmCatalog Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 802.682 | 0.146693 | 8497.69ms | 4525119 | 30 | 1.866e+09 | 5.37634e+06 | 0.0616657 | 6.36737 | 31.7503 | 6.41975 | 0.0156354 | 0.0783227 | 0.00793359 | 1(Win) | true |
| simdjson (ondemand) | 512.375 | 0.0987565 | 6176.12ms | 4525119 | 40 | 2.76742e+09 | 8.42252e+06 | 0.0253416 | 9.95981 | 47.8543 | 9.07752 | 0.0294476 | 0.0958454 | 0.00631938 | 2(Loss) | true |
