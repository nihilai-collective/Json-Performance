
----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7420.3 | 0.253054 | 776.912ms | 3223 | 4890 | 5372.95 | 414.227 | 0.676462 | 0.752612 | 2.3503 | 0.408936 | 0.000492688 | 7.86144e-05 | 3.74989e-05 | 1(Win) | true |
| Glaze | 2931.99 | 0.591358 | 842.982ms | 3223 | 320 | 12298.3 | 1048.33 | 0.0759562 | 1.7956 | 5.17778 | 0.77009 | 0.000325783 | 3.78141e-05 | 5.81756e-06 | 2(Loss) | true |
