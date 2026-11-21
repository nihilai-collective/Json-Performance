
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 804.105 | 0.391714 | 424.058ms | 3223 | 40 | 8967.95 | 3822.5 | 0.108885 | 3.04445 | 1(Win) | true |
| Jsonifier (two-stage) | 698.956 | 0.189318 | 454.526ms | 3223 | 4890 | 338934 | 4397.55 | 0.148851 | 3.50683 | 2(Loss) | true |
| Glaze | 482.148 | 0.229869 | 656.778ms | 3223 | 40 | 8589.74 | 6375 | 0.0261506 | 5.09527 | 3(Loss) | true |
| simdjson (ondemand) | 471.12 | 0.230487 | 674.716ms | 3223 | 2560 | 578882 | 6524.22 | 0.11989 | 5.23166 | 4(Loss) | true |
