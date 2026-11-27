
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2660.08 | 0.109765 | 5257.19ms | 1151920 | 160 | 3.28779e+07 | 412979 | 0.321344 | 0.930644 | 1(Win) | true |
| simdjson (ondemand) | 2650.69 | 0.0802006 | 5283.58ms | 1151920 | 320 | 3.53534e+07 | 414441 | 0.0476574 | 0.933932 | 2(Loss) | true |
