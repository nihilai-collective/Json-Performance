
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3928.76 | 0.1222 | 7330.6ms | 1151920 | 160 | 1.86808e+07 | 279619 | 0.134152 | 0.630062 | 1(Win) | true |
| Jsonifier | 3202.52 | 0.296168 | 9092.5ms | 1151920 | 40 | 4.12853e+07 | 343028 | 0.0780351 | 0.773006 | 2(Loss) | true |
| Glaze | 2451.04 | 0.108215 | 5720.28ms | 1151920 | 640 | 1.50557e+08 | 448201 | 0.158912 | 1.01003 | 3(Loss) | true |
| simdjson (ondemand) | 2383.67 | 0.0798023 | 5918.65ms | 1151920 | 320 | 4.32844e+07 | 460867 | 0.101729 | 1.03856 | 4(Loss) | true |
