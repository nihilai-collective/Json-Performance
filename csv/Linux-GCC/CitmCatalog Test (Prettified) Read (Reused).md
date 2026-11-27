
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 4243.86 | 0.179989 | 7653.98ms | 1151920 | 80 | 1.73663e+07 | 258858 | 0.342726 | 0.583315 | 1(Win) | true |
| Jsonifier | 4073.73 | 0.105293 | 7917.61ms | 1151920 | 160 | 1.28996e+07 | 269668 | 1.15111 | 0.607675 | 2(Loss) | true |
| simdjson (ondemand) | 3723.33 | 0.100613 | 8498.02ms | 1151920 | 320 | 2.81996e+07 | 295047 | 0.404484 | 0.664864 | 3(Loss) | true |
| simdjson (reflection) | 3515.08 | 0.129221 | 8872.14ms | 1151920 | 320 | 5.21906e+07 | 312526 | 0.118977 | 0.704255 | 4(Loss) | true |
| Glaze | 2793.7 | 0.0811332 | 5489.91ms | 1151920 | 320 | 3.25712e+07 | 393227 | 0.681857 | 0.886134 | 5(Loss) | true |
