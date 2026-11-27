
----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 612.348 | 0.119703 | 5133.38ms | 4525120 | 40 | 2.84665e+09 | 7.04745e+06 | 0.532865 | 1(Win) | true |
| simdjson (ondemand) | 417.667 | 0.120669 | 7468.37ms | 4525120 | 40 | 6.21804e+09 | 1.03324e+07 | 0.242591 | 2(Loss) | true |
