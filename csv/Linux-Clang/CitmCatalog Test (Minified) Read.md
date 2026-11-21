
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2267.87 | 0.28437 | 5496.35ms | 500299 | 80 | 2.8634e+07 | 210383 | 0.329934 | 1.09153 | 1(Win) | true |
| Jsonifier (two-stage) | 1924.13 | 0.18681 | 6446.71ms | 500299 | 40 | 8.58327e+06 | 247968 | 0.213412 | 1.28651 | 2(Loss) | true |
| Glaze | 1490.41 | 0.0578501 | 8160.71ms | 500299 | 1280 | 4.39e+07 | 320128 | 0.0403329 | 1.66094 | 3(Loss) | true |
| simdjson (ondemand) | 1114.09 | 0.088024 | 5526.49ms | 500299 | 320 | 4.54745e+07 | 428260 | 0.0300382 | 2.22206 | 4(Loss) | true |
