
----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9993.36 | 0.0346688 | 5569.84ms | 500299 | 4890 | 1.33974e+06 | 47743.9 | 0.0498111 | 0.50222 | 2.16603 | 0.353759 | 0.00247928 | 0.00238085 | 3.56204e-05 | 1(Win) | true |
| Glaze | 4987.89 | 0.524971 | 5453.01ms | 500299 | 80 | 2.01738e+07 | 95656.1 | 0.91799 | 1.01347 | 4.19185 | 0.585246 | 0.00114117 | 0.0260445 | 1.47162e-05 | 2(Loss) | true |
