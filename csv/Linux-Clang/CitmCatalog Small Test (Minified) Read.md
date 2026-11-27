
----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1928.77 | 0.0469421 | 163.436ms | 3223 | 160 | 89.5371 | 1593.6 | 0.0997166 | 1.26212 | 1(Win) | true |
| Jsonifier (two-stage) | 1589.98 | 0.245533 | 196.005ms | 3223 | 4890 | 110170 | 1933.16 | 0.37254 | 1.5353 | 2(Loss) | true |
| Glaze | 1371.84 | 0.0594806 | 229.1ms | 3223 | 160 | 284.173 | 2240.56 | 0.0924173 | 1.78333 | 3(Loss) | true |
| simdjson (ondemand) | 1067.77 | 0.129348 | 290.563ms | 3223 | 40 | 554.554 | 2878.6 | 0.0728989 | 2.29645 | 4(Loss) | true |
