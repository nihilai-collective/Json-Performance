
----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12527.5 | 0.186502 | 55.71ms | 6938 | 30 | 29.1092 | 528.167 | 0.23925 | 0.187119 | 1(Win) | true |
| Glaze | 4385.07 | 0.112968 | 156.916ms | 6960 | 80 | 233.918 | 1513.67 | 0.0429603 | 0.554723 | 2(Loss) | true |
