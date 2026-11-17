
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2725.98 | 0.693357 | 5384.08ms | 1151920 | 40 | 3.12302e+08 | 402995 | 1.3564 | 1(Win) | true |
| Jsonifier (two-stage) | 2303.5 | 0.485764 | 6458.2ms | 1151920 | 640 | 3.43479e+09 | 476908 | 2.3041 | 2(Loss) | true |
| simdjson (ondemand) | 1965.48 | 0.266709 | 7384.71ms | 1151920 | 40 | 8.88877e+07 | 558925 | 0.652217 | 3(Loss) | true |
| simdjson (reflection) | 1887.03 | 1.39832 | 7593.5ms | 1151920 | 30 | 1.98803e+09 | 582161 | 1.5571 | 4(Loss) | true |
| Glaze | 1595.75 | 0.724038 | 8446.43ms | 1151920 | 320 | 7.95041e+09 | 688428 | 0.802653 | 5(Loss) | true |
