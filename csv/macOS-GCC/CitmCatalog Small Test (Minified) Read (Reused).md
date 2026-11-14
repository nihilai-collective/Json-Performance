
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1800.11 | 0.418066 | 232.39ms | 3223 | 4890 | 249185 | 1707.5 | 0.163463 | 1(Win) | true |
| Jsonifier (two-stage) | 1289.25 | 0.436195 | 298.48ms | 3223 | 2560 | 276854 | 2384.1 | 0.45083 | 2(Loss) | true |
| Glaze | 1132.15 | 0.331772 | 343.145ms | 3223 | 4890 | 396734 | 2714.91 | 0.34472 | 3(Loss) | true |
| simdjson (reflection) | 1062.24 | 0.636037 | 385.387ms | 3223 | 320 | 108391 | 2893.6 | 0.57724 | 4(Loss) | true |
| simdjson (ondemand) | 1032.41 | 0.511165 | 353.258ms | 3223 | 640 | 148224 | 2977.2 | 0.120773 | 5(Loss) | true |
