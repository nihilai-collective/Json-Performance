
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2688.52 | 0.332005 | 5260.1ms | 1151920 | 640 | 1.17785e+09 | 408611 | 0.202596 | 0.920777 | 1(Win) | true |
| simdjson (ondemand) | 2634.47 | 0.156413 | 5312.7ms | 1151920 | 640 | 2.72261e+08 | 416993 | 0.21094 | 0.939674 | 2(Loss) | true |
