
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3014.4 | 0.158463 | 9473.78ms | 1151920 | 30 | 1.0005e+07 | 364436 | 0.106617 | 1(Win) | true |
| Jsonifier (two-stage) | 2825.93 | 0.171841 | 5035.83ms | 1151920 | 30 | 1.33875e+07 | 388742 | 0.474345 | 2(Loss) | true |
| Glaze | 1988.7 | 0.319563 | 7088.1ms | 1151920 | 40 | 1.24647e+08 | 552400 | 0.215273 | 3(Loss) | true |
| simdjson (ondemand) | 1784.54 | 0.103124 | 7880.14ms | 1151920 | 640 | 2.57924e+08 | 615597 | 0.0339605 | 4(Loss) | true |
