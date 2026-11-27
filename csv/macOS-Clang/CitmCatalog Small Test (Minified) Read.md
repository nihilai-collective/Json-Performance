
----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1244.57 | 0.249336 | 266.49ms | 3223 | 40 | 1516.74 | 2469.68 | 0.234385 | 1(Win) | true |
| Jsonifier (two-stage) | 1010.75 | 0.0807705 | 308.885ms | 3223 | 4890 | 29501.5 | 3040.99 | 0.0213102 | 2(Loss) | true |
| Glaze | 828.463 | 0.122559 | 368.476ms | 3223 | 4890 | 101106 | 3710.12 | 0.402251 | 3(Loss) | true |
| simdjson (ondemand) | 683.96 | 0.272604 | 454.777ms | 3223 | 1280 | 192102 | 4493.96 | 0.341882 | 4(Loss) | true |
