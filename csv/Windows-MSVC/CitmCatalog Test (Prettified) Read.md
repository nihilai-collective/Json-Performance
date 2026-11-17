
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1474.56 | 0.0743363 | 9471.65ms | 1151920 | 640 | 1.96292e+08 | 745008 | 0.0399375 | 2.06104 | 1(Win) | true |
| simdjson (ondemand) | 1324.57 | 0.799996 | 5198.89ms | 1151920 | 160 | 7.04354e+09 | 829369 | 0.199302 | 2.29417 | 2(Loss) | true |
