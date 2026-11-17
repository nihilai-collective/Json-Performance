
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2799.5 | 0.0996574 | 5352.57ms | 500299 | 160 | 4.61569e+06 | 170431 | 0.119976 | 1.80152 | 8.80504 | 1.64787 | 0.00761034 | 0.0032026 | 2.70963e-05 | 1(Win) | true |
| Glaze | 2138.22 | 0.0387904 | 6814.09ms | 500299 | 1280 | 9.58986e+06 | 223140 | 0.127347 | 2.35274 | 11.3989 | 2.0915 | 0.00950959 | 0.00175153 | 3.54554e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1945.29 | 0.0461945 | 7394.1ms | 500299 | 1280 | 1.64316e+07 | 245270 | 0.107225 | 2.59251 | 12.1486 | 2.02831 | 0.0114918 | 0.0257227 | 0.000196503 | 3(Loss) | true |
| simdjson (ondemand) | 1294.85 | 0.0855718 | 5175.91ms | 500299 | 640 | 6.36303e+07 | 368478 | 0.159858 | 3.87297 | 17.7699 | 2.58181 | 0.00874268 | 0.0206846 | 6.36088e-05 | 4(Loss) | true |
