
----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 579.022 | 0.209404 | 5520.37ms | 4525120 | 40 | 9.74315e+09 | 7.45306e+06 | 1.33446 | 1(Win) | true |
| simdjson (ondemand) | 414.04 | 0.879475 | 7605.64ms | 4525120 | 30 | 2.52083e+11 | 1.04229e+07 | 0.664847 | 2(Loss) | true |
