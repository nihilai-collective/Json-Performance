
----
### CitmCatalog Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 9475.01 | 4.05314 | 36.108ms | 3223 | 1280 | 221286 | 324.4 | 2.75779 | 1(Win) | true |
| Jsonifier | 8581.16 | 1.97395 | 39.6119ms | 3223 | 4890 | 244460 | 358.191 | 0.086306 | 2(Loss) | true |
| Glaze | 2176.71 | 0.518683 | 144.668ms | 3223 | 4890 | 262322 | 1412.08 | 0.425534 | 3(Loss) | true |
