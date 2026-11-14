
----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 377.136 | 0.116259 | 8450.86ms | 500299 | 160 | 3.4613e+08 | 1.26512e+06 | 0.230697 | 6.56458 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 234.19 | 0.0720899 | 6663.59ms | 500299 | 30 | 6.47133e+07 | 2.03733e+06 | 2.62275 | 10.5717 | -(Loss) | false |
