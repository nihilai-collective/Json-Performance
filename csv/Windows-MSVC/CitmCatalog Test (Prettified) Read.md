
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2424.78 | 0.158831 | 5836.01ms | 1151920 | 160 | 8.28494e+07 | 453054 | 0.169832 | 1.02093 | 1(Win) | true |
| Jsonifier | 2150.71 | 0.4246 | 6658.28ms | 1151920 | 30 | 1.41111e+08 | 510787 | 0.03001 | 1.15103 | 2(Loss) | true |
| Glaze | 1371.34 | 0.349763 | 5239.32ms | 1151920 | 80 | 6.28044e+08 | 801081 | 0.190261 | 1.80531 | 3(Loss) | true |
| simdjson (ondemand) | 1234.3 | 0.193077 | 5866.42ms | 1151920 | 30 | 8.85903e+07 | 890027 | 0.225218 | 2.00579 | 4(Loss) | true |
