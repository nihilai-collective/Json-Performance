
----
### CitmCatalog Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1418.49 | 0.170301 | 10193.4ms | 4525119 | 80 | 2.14749e+09 | 3.04231e+06 | 0.286854 | 1.74534 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1184.73 | 0.389443 | 6025.41ms | 4525119 | 40 | 8.04946e+09 | 3.64258e+06 | 2.84816 | 2.08974 | -(Loss) | false |
