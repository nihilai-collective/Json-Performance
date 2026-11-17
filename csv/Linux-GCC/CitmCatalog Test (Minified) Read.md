
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1379.17 | 0.129625 | 9008.01ms | 500299 | 1280 | 2.57401e+08 | 345949 | 0.130895 | 1.79492 | 1(Win) | true |
| simdjson (ondemand) | 1272.39 | 0.209598 | 9691.27ms | 500299 | 320 | 1.97669e+08 | 374980 | 0.0351158 | 1.94556 | 2(Loss) | true |
