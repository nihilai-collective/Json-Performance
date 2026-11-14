
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2600.26 | 0.0613283 | 5498.01ms | 1151920 | 320 | 2.14824e+07 | 422480 | 0.00309399 | 1.95808 | 8.58584 | 1.51221 | 0.00718792 | 0.0342628 | 1.49235e-05 | 1(Win) | true |
| simdjson (ondemand) | 2422.08 | 0.0474797 | 5866.13ms | 1151920 | 320 | 1.484e+07 | 453558 | 0.0379479 | 2.08809 | 8.78375 | 1.33636 | 0.00953626 | 0.0350642 | 1.43158e-05 | 2(Loss) | true |
