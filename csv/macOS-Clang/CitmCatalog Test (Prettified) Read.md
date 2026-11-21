
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2880.73 | 0.236384 | 5279.05ms | 1151920 | 40 | 3.2504e+07 | 381347 | 0.463355 | 1(Win) | true |
| Jsonifier (two-stage) | 2202.56 | 0.303086 | 6663.37ms | 1151920 | 640 | 1.46252e+09 | 498764 | 0.760008 | 2(Loss) | true |
| Glaze | 1724.64 | 0.86655 | 7543.11ms | 1151920 | 30 | 9.14018e+08 | 636976 | 0.872727 | 3(Loss) | true |
| simdjson (ondemand) | 1530.58 | 0.484056 | 9142.46ms | 1151920 | 320 | 3.86254e+09 | 717738 | 0.979324 | 4(Loss) | true |
