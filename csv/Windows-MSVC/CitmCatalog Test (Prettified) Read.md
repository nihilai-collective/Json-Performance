
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2528.38 | 0.279732 | 5767.46ms | 1151920 | 40 | 5.90886e+07 | 434490 | 1.70354 | 0.979097 | 1(Win) | true |
| Jsonifier | 2199.41 | 0.160624 | 6438.96ms | 1151920 | 640 | 4.11943e+08 | 499479 | 0.181706 | 1.12556 | 2(Loss) | true |
| Glaze | 1500.16 | 0.320763 | 9484.66ms | 1151920 | 30 | 1.65524e+08 | 732293 | 0.173128 | 1.65027 | 3(Loss) | true |
| simdjson (ondemand) | 1280.37 | 0.18781 | 5671.78ms | 1151920 | 40 | 1.03865e+08 | 857998 | 0.100036 | 1.93359 | 4(Loss) | true |
