
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2234.28 | 0.0555492 | 153.907ms | 3223 | 80 | 46.719 | 1375.7 | 0.134296 | 1.0858 | 1(Win) | true |
| Jsonifier (two-stage) | 1931.17 | 0.0760461 | 182.223ms | 3223 | 80 | 117.199 | 1591.62 | 0.128634 | 1.26025 | 2(Loss) | true |
| simdjson (ondemand) | 1602.91 | 0.106337 | 252.074ms | 3223 | 30 | 124.737 | 1917.57 | 0.0156424 | 1.52487 | 3(Loss) | true |
| Glaze | 1487.46 | 0.0818677 | 224.954ms | 3223 | 80 | 228.952 | 2066.4 | 0.30581 | 1.64231 | 4(Loss) | true |
| simdjson (reflection) | 1397.8 | 0.3223 | 246.003ms | 3223 | 1280 | 64293 | 2198.96 | 0.201748 | 1.74943 | 5(Loss) | true |
