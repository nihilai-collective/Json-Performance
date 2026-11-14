
----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 560.829 | 0.0807281 | 5670.38ms | 500299 | 80 | 3.77344e+07 | 850744 | 0.0198889 | 1(Win) | true |
| simdjson (ondemand) | 314.895 | 0.0814619 | 9999.8ms | 500299 | 80 | 1.21878e+08 | 1.51518e+06 | 0.0888366 | 2(Loss) | true |
