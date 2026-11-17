
----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1928.04 | 0.0439483 | 239.802ms | 4630 | 80 | 81.0405 | 2290.15 | 0.207841 | 1.26992 | 1(Win) | true |
| Glaze | 1509.26 | 0.0629868 | 299.2ms | 4630 | 80 | 271.658 | 2925.61 | 0.333088 | 1.62514 | 2(Loss) | true |
| simdjson (reflection) | 967.238 | 0.0175276 | 471.907ms | 4630 | 40 | 25.6096 | 4565.07 | 0.015149 | 2.54407 | 3(Loss) | true |
