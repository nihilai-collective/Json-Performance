
----
### CitmCatalog Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10386.2 | 0.0428227 | 5374.62ms | 500299 | 1280 | 495339 | 45938 | 0.0765782 | 0.484956 | 2.16603 | 0.353759 | 0.00210543 | 0.00193238 | 6.1635e-06 | 1(Win) | true |
| Glaze | 5055.17 | 0.0782802 | 5257.32ms | 500299 | 2560 | 1.39744e+07 | 94383.1 | 0.155578 | 0.995489 | 4.19185 | 0.585246 | 0.00112071 | 0.0252637 | 1.6651e-05 | 2(Loss) | true |
