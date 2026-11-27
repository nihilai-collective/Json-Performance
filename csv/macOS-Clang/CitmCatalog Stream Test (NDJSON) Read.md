
----
### CitmCatalog Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1030.78 | 0.167448 | 6739.07ms | 4525120 | 30 | 1.47439e+09 | 4.18663e+06 | 0.455488 | 1(Win) | true |
| simdjson (ondemand) | 903.027 | 0.174442 | 7588.4ms | 4525120 | 40 | 2.77985e+09 | 4.77892e+06 | 0.287121 | 2(Loss) | true |
