
----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10439.1 | 0.110308 | 4534.82ms | 500299 | 1280 | 3.25355e+06 | 45705.5 | 0.176111 | 0.237007 | 1(Win) | true |
| simdjson (reflection) | 8504.27 | 0.194085 | 5608.26ms | 500299 | 640 | 7.58838e+06 | 56103.9 | 0.158001 | 0.290976 | 2(Loss) | true |
| Glaze | 3692.8 | 0.0542674 | 6692.97ms | 500299 | 2560 | 1.25854e+07 | 129204 | 0.112791 | 0.670261 | 3(Loss) | true |
