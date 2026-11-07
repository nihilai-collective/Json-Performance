
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2706.14 | 0.233349 | 5537.53ms | 500299 | 80 | 1.35413e+07 | 176311 | 0.0596817 | 0.914685 | 1(Win) | true |
| Jsonifier (two-stage) | 2249.07 | 0.238848 | 6311.91ms | 500299 | 30 | 7.70223e+06 | 212142 | 0.527893 | 1.10063 | 2(Loss) | true |
| Glaze | 1818.42 | 0.176041 | 7695.31ms | 500299 | 160 | 3.41367e+07 | 262383 | 0.00794464 | 1.36137 | 3(Loss) | true |
| simdjson (ondemand) | 1306.18 | 0.143264 | 5157.51ms | 500299 | 80 | 2.19089e+07 | 365281 | 0.200112 | 1.89531 | 4(Loss) | true |
