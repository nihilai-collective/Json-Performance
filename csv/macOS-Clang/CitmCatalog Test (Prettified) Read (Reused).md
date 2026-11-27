
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3652.48 | 0.0698998 | 8963.88ms | 1151920 | 320 | 1.41439e+07 | 300770 | 0.126419 | 1(Win) | true |
| Jsonifier (two-stage) | 3096.9 | 0.17213 | 10104.1ms | 1151920 | 30 | 1.11847e+07 | 354728 | 0.379168 | 2(Loss) | true |
| Glaze | 2176.4 | 0.0936789 | 6900.45ms | 1151920 | 160 | 3.57742e+07 | 504758 | 0.0846778 | 3(Loss) | true |
| simdjson (ondemand) | 1892.86 | 0.134333 | 7933.14ms | 1151920 | 80 | 4.86252e+07 | 580369 | 0.105621 | 4(Loss) | true |
