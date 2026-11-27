
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2975.29 | 0.0665372 | 9460.87ms | 1151920 | 1280 | 7.72546e+07 | 369226 | 0.115778 | 0.832025 | 1(Win) | true |
| simdjson (ondemand) | 2908.64 | 0.173911 | 9793.78ms | 1151920 | 40 | 1.72576e+07 | 377687 | 0.0543871 | 0.8511 | 2(Loss) | true |
