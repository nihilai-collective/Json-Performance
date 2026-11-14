
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2637.9 | 0.0823877 | 5318.16ms | 1151920 | 640 | 7.53413e+07 | 416451 | 0.385164 | 0.938447 | 1(Win) | true |
| simdjson (ondemand) | 2555.51 | 0.186297 | 5534.26ms | 1151920 | 640 | 4.1047e+08 | 429878 | 0.2288 | 0.968718 | 2(Loss) | true |
