
----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 452.756 | 0.0889888 | 6670.62ms | 500299 | 160 | 1.40709e+08 | 1.05382e+06 | 0.136282 | 6.71271 | 1(Win) | true |
| simdjson (ondemand) | 316.645 | 0.11922 | 9480.45ms | 500299 | 320 | 1.03268e+09 | 1.50681e+06 | 0.229966 | 9.5983 | 2(Loss) | true |
