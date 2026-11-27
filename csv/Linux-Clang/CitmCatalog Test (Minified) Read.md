
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2164.66 | 0.272707 | 5488.16ms | 500299 | 80 | 2.89042e+07 | 220414 | 0.326433 | 1.14352 | 1(Win) | true |
| Jsonifier (two-stage) | 1850.32 | 0.149982 | 6510.92ms | 500299 | 160 | 2.3931e+07 | 257859 | 0.123948 | 1.33777 | 2(Loss) | true |
| Glaze | 1556.83 | 0.0755349 | 7863.52ms | 500299 | 640 | 3.42968e+07 | 306471 | 0.112649 | 1.59009 | 3(Loss) | true |
| simdjson (ondemand) | 1046.95 | 0.150998 | 5830.01ms | 500299 | 30 | 1.4206e+07 | 455726 | 0.0368288 | 2.36451 | 4(Loss) | true |
