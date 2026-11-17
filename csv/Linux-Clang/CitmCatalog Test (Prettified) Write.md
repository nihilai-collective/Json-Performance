
----
### CitmCatalog Test (Prettified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15327.5 | 0.0238341 | 9788.68ms | 1439562 | 4890 | 2.22856e+06 | 89569.4 | 0.122595 | 0.32854 | 1.34917 | 0.258045 | 0.000823013 | 0.0181772 | 1.56657e-05 | 1(Win) | true |
| Glaze | 5286.66 | 0.100902 | 6842.33ms | 1439584 | 640 | 4.3943e+07 | 259690 | 0.132625 | 0.947054 | 3.07289 | 0.528478 | 0.0010116 | 0.0630969 | 1.42695e-05 | 2(Loss) | true |
