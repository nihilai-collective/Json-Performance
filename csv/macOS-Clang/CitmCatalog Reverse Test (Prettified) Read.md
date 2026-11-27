
----
### CitmCatalog Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1125.59 | 0.359027 | 6237.34ms | 1151920 | 40 | 4.91137e+08 | 975987 | 0.10418 | 1(Win) | true |
| simdjson (ondemand) | 664.816 | 0.16529 | 5235.05ms | 1151920 | 160 | 1.1936e+09 | 1.65242e+06 | 0.074232 | 2(Loss) | true |
