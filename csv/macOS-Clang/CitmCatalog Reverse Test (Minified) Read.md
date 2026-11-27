
----
### CitmCatalog Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 544.371 | 0.205368 | 5642.31ms | 500299 | 80 | 2.59194e+08 | 876466 | 0.204487 | 1(Win) | true |
| simdjson (ondemand) | 303.64 | 0.11171 | 10004.7ms | 500299 | 320 | 9.85999e+08 | 1.57134e+06 | 0.0464248 | 2(Loss) | true |
