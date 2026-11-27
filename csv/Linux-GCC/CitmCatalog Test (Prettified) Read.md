
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2890.69 | 0.0533818 | 9922.65ms | 1151920 | 640 | 2.63394e+07 | 380032 | 0.0498772 | 1.74756 | 7.84234 | 1.34547 | 0.00747644 | 0.0366238 | 5.54563e-05 | 1(Win) | true |
| simdjson (ondemand) | 2410.18 | 0.154531 | 5891.22ms | 1151920 | 640 | 3.17511e+08 | 455799 | 0.11581 | 2.099 | 8.4507 | 1.36134 | 0.0106199 | 0.0360693 | 4.0834e-05 | 2(Loss) | true |
