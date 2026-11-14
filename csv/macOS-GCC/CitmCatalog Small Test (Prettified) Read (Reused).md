
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2217.47 | 0.584263 | 315.179ms | 5839 | 1280 | 275543 | 2511.2 | 0.96494 | 1(Win) | true |
| Jsonifier (two-stage) | 2071 | 0.963776 | 342.997ms | 5839 | 320 | 214892 | 2688.8 | 0.508373 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1676.45 | 0.814398 | 405.181ms | 5839 | 320 | 234163 | 3321.6 | 0.727802 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1649.05 | 0.434494 | 396.119ms | 5839 | 1280 | 275543 | 3376.8 | 0.31881 | 3(Tie) | true |
| Glaze | 1586.17 | 0.231272 | 412.845ms | 5839 | 4890 | 322353 | 3510.66 | 0.189932 | 5(Loss) | true |
