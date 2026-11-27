
----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24059.7 | 0.405442 | 5609.25ms | 1439562 | 1280 | 6.85088e+07 | 57061.1 | 0.121539 | 0.10284 | 1(Win) | true |
| Glaze | 6043.28 | 0.315011 | 5811.32ms | 1439584 | 40 | 2.04852e+07 | 227177 | 0.333123 | 0.409627 | 2(Loss) | true |
| simdjson (reflection) | 562.493 | 0.224885 | 7782.59ms | 1439562 | 160 | 4.82025e+09 | 2.44069e+06 | 0.188485 | 4.40136 | 3(Loss) | true |
