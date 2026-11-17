
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1856.13 | 0.225845 | 237.712ms | 3223 | 320 | 4475.85 | 1655.97 | 0.442209 | 1(Win) | true |
| Jsonifier (two-stage) | 1242.43 | 0.415074 | 334.887ms | 3223 | 640 | 67485.6 | 2473.95 | 1.0262 | 2(Loss) | true |
| Glaze | 971.395 | 0.779267 | 391.036ms | 3223 | 640 | 389118 | 3164.2 | 0.471824 | 3(Loss) | true |
| simdjson (ondemand) | 770.298 | 0.395761 | 461.4ms | 3223 | 4890 | 1.21949e+06 | 3990.26 | 0.561793 | 4(Loss) | true |
