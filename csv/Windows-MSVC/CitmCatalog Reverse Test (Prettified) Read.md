
----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1004.08 | 0.208982 | 6880.77ms | 1151920 | 160 | 8.36462e+08 | 1.0941e+06 | 0.0653936 | 3.02673 | 1(Win) | true |
| simdjson (ondemand) | 705.468 | 0.134495 | 9832.54ms | 1151920 | 160 | 7.01812e+08 | 1.5572e+06 | 0.452723 | 4.30796 | 2(Loss) | true |
