
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1025.76 | 0.0839365 | 6618.46ms | 500299 | 320 | 4.87773e+07 | 465139 | 0.0168181 | 1(Win) | true |
| simdjson (ondemand) | 921.67 | 0.0642279 | 7107.11ms | 500299 | 320 | 3.53758e+07 | 517672 | 0.0768947 | 2(Loss) | true |
