
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8609.78 | 2.66608 | 39.019ms | 3223 | 2560 | 231912 | 357 | 1.97694 | 1(Win) | true |
| simdjson (reflection) | 6993.73 | 1.64231 | 47.873ms | 3223 | 4890 | 254754 | 439.493 | 0.22864 | 2(Loss) | true |
| Glaze | 2044.9 | 0.687375 | 162.198ms | 3223 | 2560 | 273277 | 1503.1 | 1.42314 | 3(Loss) | true |
