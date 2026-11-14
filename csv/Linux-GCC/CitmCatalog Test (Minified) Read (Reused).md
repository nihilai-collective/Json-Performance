
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1594.19 | 0.0495992 | 8687.16ms | 500299 | 1280 | 2.82059e+07 | 299289 | 0.182087 | 3.18356 | 15.6564 | 2.85605 | 0.00953883 | 0.0127944 | 1.50816e-05 | 1(Win) | true |
| simdjson (ondemand) | 1354.33 | 0.0411491 | 10032.9ms | 500299 | 1280 | 2.68992e+07 | 352293 | 0.0704578 | 3.74758 | 16.6246 | 2.69129 | 0.0149765 | 0.0151486 | 7.50957e-06 | 2(Loss) | true |
