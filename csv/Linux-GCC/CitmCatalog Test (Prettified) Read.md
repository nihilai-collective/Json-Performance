
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2818.93 | 0.0772478 | 5048.4ms | 1151920 | 640 | 5.79999e+07 | 389707 | 0.0489165 | 1.7836 | 8.01461 | 1.39426 | 0.00633113 | 0.0332095 | 1.18227e-05 | 1(Win) | true |
| simdjson (ondemand) | 2558.38 | 0.0420799 | 5572.52ms | 1151920 | 640 | 2.08951e+07 | 429396 | 0.212694 | 1.99421 | 8.47188 | 1.32044 | 0.00856014 | 0.0345134 | 1.03089e-05 | 2(Loss) | true |
