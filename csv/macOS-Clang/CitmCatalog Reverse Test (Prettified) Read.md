
----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1067.44 | 0.631484 | 6402.26ms | 1151920 | 30 | 1.26708e+09 | 1.02915e+06 | 0.108485 | 1(Win) | true |
| simdjson (ondemand) | 592.638 | 0.217908 | 5786.57ms | 1151920 | 160 | 2.61056e+09 | 1.85367e+06 | 1.91421 | 2(Loss) | true |
