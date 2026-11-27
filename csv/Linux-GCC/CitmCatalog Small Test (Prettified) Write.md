
----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14662.4 | 0.212718 | 48.1697ms | 6938 | 80 | 73.715 | 451.262 | 0.0193938 | 0.158785 | 1(Win) | true |
| Glaze | 3965.75 | 0.211454 | 175.59ms | 6960 | 40 | 501.025 | 1673.72 | 0.503805 | 0.614501 | 2(Loss) | true |
| simdjson (reflection) | 565.599 | 0.420993 | 1205.02ms | 6938 | 640 | 1.55233e+06 | 11698.4 | 0.169327 | 4.36747 | 3(Loss) | true |
