
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2756.86 | 1.0223 | 5170.03ms | 1151920 | 320 | 5.31035e+09 | 398481 | 0.149284 | 1.83096 | 8.01192 | 1.39408 | 0.00639899 | 0.0333485 | 2.22834e-05 | 1(Win) | true |
| simdjson (ondemand) | 2479.42 | 0.0515689 | 5776.59ms | 1151920 | 640 | 3.34118e+07 | 443070 | 0.296414 | 2.04182 | 8.47093 | 1.32101 | 0.0100484 | 0.0343001 | 4.5728e-05 | 2(Loss) | true |
