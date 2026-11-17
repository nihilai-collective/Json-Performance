
----
### CitmCatalog Small Test (Minified) Write Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7578.55 | 0.109131 | 43.4888ms | 3223 | 320 | 62.6898 | 405.578 | 0.451777 | 0.303474 | 1(Win) | true |
| simdjson (reflection) | 6462.77 | 0.0933167 | 51.1516ms | 3223 | 320 | 63.0307 | 475.6 | 0.181022 | 0.361462 | 2(Loss) | true |
| Glaze | 2594.27 | 0.241638 | 118.56ms | 3223 | 30 | 245.89 | 1184.8 | 0.0225023 | 0.931451 | 3(Loss) | true |
