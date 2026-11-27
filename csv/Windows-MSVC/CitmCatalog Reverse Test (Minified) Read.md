
----
### CitmCatalog Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 464.671 | 0.221525 | 6477.48ms | 500299 | 30 | 1.55216e+08 | 1.0268e+06 | 0.0227296 | 6.54066 | 1(Win) | true |
| simdjson (ondemand) | 313.159 | 0.233428 | 9700.08ms | 500299 | 30 | 3.79452e+08 | 1.52358e+06 | 0.00787558 | 9.70529 | 2(Loss) | true |
