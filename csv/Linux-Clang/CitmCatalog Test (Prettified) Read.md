
----
### CitmCatalog Test (Prettified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14810.7 | 0.173329 | 8232.45ms | 1151920 | 4890 | 8.0825e+07 | 74173 | 0.172166 | 0.343926 | 1.85059 | 0.0847481 | 0.000530078 | 0.00340018 | 1.93915e-06 | 1(Win) | true |
| simdjson (stage-1) | 13727 | 0.0704266 | 8870.69ms | 1151920 | 30 | 95298.7 | 80028.8 | 0.0263586 | 0.375068 | 1.73799 | 0.0731258 | 0.000374013 | 0.00620098 | 2.51754e-06 | 2(Loss) | true |
