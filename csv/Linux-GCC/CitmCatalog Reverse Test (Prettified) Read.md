
----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1476.66 | 0.0594723 | 9529.3ms | 1151920 | 640 | 1.25283e+08 | 743947 | 0.0484255 | 3.45171 | 16.2835 | 3.30716 | 0.00883042 | 0.0365391 | 2.33293e-05 | 1(Win) | true |
| simdjson (ondemand) | 951.247 | 0.0510737 | 7334.68ms | 1151920 | 320 | 1.11328e+08 | 1.15486e+06 | 0.0564328 | 5.3648 | 28.3075 | 5.69766 | 0.0134117 | 0.0583113 | 1.97252e-05 | 2(Loss) | true |
