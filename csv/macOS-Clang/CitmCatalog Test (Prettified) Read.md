
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3203.92 | 0.11459 | 8888.21ms | 1151920 | 160 | 2.46998e+07 | 342879 | 0.121762 | 1(Win) | true |
| Jsonifier (two-stage) | 2761.81 | 0.0593908 | 5236.1ms | 1151920 | 640 | 3.57169e+07 | 397766 | 0.238573 | 2(Loss) | true |
| Glaze | 2011.9 | 0.208669 | 7062.77ms | 1151920 | 160 | 2.07714e+08 | 546029 | 0.144085 | 3(Loss) | true |
| simdjson (ondemand) | 1785.57 | 0.142475 | 7900.77ms | 1151920 | 40 | 3.07345e+07 | 615241 | 0.0189104 | 4(Loss) | true |
