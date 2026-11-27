
----
### CitmCatalog Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 8949.74 | 0.2013 | 6009.7ms | 500299 | 2560 | 2.94828e+07 | 53311.3 | 4.23934 | 1(Win) | true |
| Jsonifier | 8839.96 | 0.10442 | 5515.86ms | 500299 | 30 | 95290.9 | 53973.3 | 0.0791139 | 2(Loss) | true |
| Glaze | 2357.49 | 0.149778 | 5187.76ms | 500299 | 160 | 1.4702e+07 | 202386 | 0.120811 | 3(Loss) | true |
