
----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8942.95 | 2.74298 | 37.1661ms | 3223 | 2560 | 227534 | 343.7 | 0.555881 | 1(Win) | true |
| simdjson (reflection) | 6773.23 | 2.2962 | 44.8771ms | 3223 | 2560 | 277963 | 453.8 | 3.24094 | 2(Loss) | true |
| Glaze | 1956.77 | 1.26018 | 173.597ms | 3223 | 640 | 250778 | 1570.8 | 3.03704 | 3(Loss) | true |
