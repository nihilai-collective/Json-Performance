
----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 813.287 | 0.246418 | 382.132ms | 3223 | 4890 | 424118 | 3779.35 | 0.537489 | 3.71525 | 1(Win) | true |
| Jsonifier (two-stage) | 699.61 | 0.124784 | 447.358ms | 3223 | 1280 | 38471.4 | 4393.44 | 0.192417 | 4.32312 | 2(Loss) | true |
| Glaze | 623.19 | 0.828171 | 503.634ms | 3223 | 1280 | 2.13565e+06 | 4932.19 | 1.45598 | 4.85844 | 3(Loss) | true |
| simdjson (ondemand) | 540.37 | 0.122116 | 579.75ms | 3223 | 160 | 7719.73 | 5688.12 | 0.25336 | 5.60248 | 4(Loss) | true |
