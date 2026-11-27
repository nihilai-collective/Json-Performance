
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3630.54 | 0.0707548 | 7754.9ms | 1151920 | 1280 | 5.86711e+07 | 302588 | 0.652541 | 0.681853 | 1(Win) | true |
| Jsonifier | 3564.08 | 0.127963 | 7964.55ms | 1151920 | 320 | 4.97819e+07 | 308230 | 0.45601 | 0.694582 | 2(Loss) | true |
| simdjson (ondemand) | 3140.21 | 0.108121 | 8863.79ms | 1151920 | 160 | 2.28912e+07 | 349835 | 0.774784 | 0.788333 | 3(Loss) | true |
| simdjson (reflection) | 3051.26 | 0.168958 | 9221.15ms | 1151920 | 640 | 2.36825e+08 | 360034 | 0.319085 | 0.811307 | 4(Loss) | true |
| Glaze | 2467.25 | 0.202941 | 5485.99ms | 1151920 | 160 | 1.30641e+08 | 445256 | 0.131383 | 1.0034 | 5(Loss) | true |
