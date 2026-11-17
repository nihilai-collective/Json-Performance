
----
### CitmCatalog Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1606.78 | 0.205142 | 8912.54ms | 4525120 | 30 | 9.10701e+08 | 2.68579e+06 | 0.105058 | 1.54082 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1605.22 | 0.157764 | 9020.15ms | 4525120 | 160 | 2.87824e+09 | 2.68841e+06 | 0.646897 | 1.54233 | 1(Tie) | true |
