
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1619.56 | 0.194442 | 8564.45ms | 500299 | 320 | 1.05002e+08 | 294600 | 0.0429792 | 1.52852 | 1(Win) | true |
| Jsonifier (two-stage) | 1340.73 | 0.114857 | 5025.67ms | 500299 | 320 | 5.34617e+07 | 355868 | 0.0147505 | 1.84644 | 2(Loss) | true |
| Glaze | 849.259 | 0.251478 | 7747.13ms | 500299 | 40 | 7.98435e+07 | 561810 | 0.0148352 | 2.91517 | 3(Loss) | true |
| simdjson (ondemand) | 587.437 | 0.285646 | 5411.26ms | 500299 | 30 | 1.61479e+08 | 812210 | 0.0533239 | 4.21429 | 4(Loss) | true |
