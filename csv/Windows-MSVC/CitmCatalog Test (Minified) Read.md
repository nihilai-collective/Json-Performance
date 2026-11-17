
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1325.33 | 0.136236 | 9308.12ms | 500299 | 320 | 7.69749e+07 | 360003 | 0.110538 | 1.8678 | 1(Win) | true |
| Jsonifier (two-stage) | 1139.06 | 0.416399 | 5469.07ms | 500299 | 80 | 2.43374e+08 | 418872 | 0.135299 | 2.17334 | 2(Loss) | true |
| Glaze | 717.787 | 0.194567 | 8520.61ms | 500299 | 160 | 2.67623e+08 | 664712 | 0.423197 | 3.44904 | 3(Loss) | true |
| simdjson (ondemand) | 573.387 | 0.204917 | 5415.96ms | 500299 | 40 | 1.163e+08 | 832112 | 0.0135216 | 4.31756 | 4(Loss) | true |
