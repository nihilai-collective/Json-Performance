
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 747.505 | 0.147209 | 8595.73ms | 500299 | 160 | 1.4126e+08 | 638286 | 0.0182161 | 4.06583 | 1(Win) | true |
| simdjson (ondemand) | 703.828 | 0.183293 | 9114.3ms | 500299 | 80 | 1.23512e+08 | 677896 | 0.0669799 | 4.31815 | 2(Loss) | true |
