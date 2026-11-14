
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14878.5 | 0.0295431 | 8097.66ms | 1151920 | 1280 | 609040 | 73835 | 0.167644 | 0.341455 | 1.85059 | 0.0847481 | 0.000535529 | 1.82257e-05 | 1.30896e-07 | 1(Win) | true |
| simdjson (stage-1) | 13806.7 | 0.0164591 | 8694.21ms | 1151920 | 4890 | 838650 | 79566.7 | 0.00481507 | 0.371048 | 1.73799 | 0.0731258 | 0.000252162 | 4.51367e-06 | 4.28555e-07 | 2(Loss) | true |
