
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2668.6 | 0.196503 | 5252.05ms | 1151920 | 80 | 5.23485e+07 | 411660 | 0.125187 | 0.927659 | 1(Win) | true |
| simdjson (ondemand) | 2550.29 | 0.10526 | 5529.4ms | 1151920 | 160 | 3.28939e+07 | 430758 | 0.351843 | 0.97071 | 2(Loss) | true |
