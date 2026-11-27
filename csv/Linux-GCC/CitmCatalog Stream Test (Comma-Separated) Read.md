
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1382.03 | 1.1458 | 10369.7ms | 4525119 | 160 | 2.04816e+11 | 3.12258e+06 | 1.30776 | 3.68022 | 17.1258 | 3.19207 | 0.0104373 | 0.0774004 | 0.0051814 | 1(Win) | true |
| simdjson (ondemand) | 897.096 | 2.01765 | 7754.24ms | 4525119 | 30 | 2.82615e+11 | 4.81051e+06 | 0.0992653 | 5.64951 | 21.4765 | 4.24757 | 0.0177299 | 0.093125 | 0.00887265 | 2(Loss) | true |
