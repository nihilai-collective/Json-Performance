
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1647.39 | 0.202011 | 8720.79ms | 500299 | 320 | 1.09539e+08 | 289623 | 0.478176 | 1.50267 | 1(Win) | true |
| Jsonifier (two-stage) | 1293.74 | 0.469788 | 5297.02ms | 500299 | 30 | 9.00517e+07 | 368793 | 0.0605212 | 1.91346 | 2(Loss) | true |
| Glaze | 759.936 | 0.239635 | 8594.06ms | 500299 | 40 | 9.05451e+07 | 627845 | 0.328385 | 3.25778 | 3(Loss) | true |
| simdjson (ondemand) | 586.717 | 0.360879 | 5354.61ms | 500299 | 30 | 2.58373e+08 | 813207 | 0.196366 | 4.21959 | 4(Loss) | true |
