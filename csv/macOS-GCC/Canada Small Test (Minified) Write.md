
----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2202.91 | 0.489471 | 197.236ms | 4630 | 2560 | 246413 | 2004.4 | 1.97574 | 1(Win) | true |
| Glaze | 1439.59 | 1.6539 | 314.802ms | 4630 | 160 | 411741 | 3067.2 | 0.15674 | 2(Loss) | true |
| simdjson (reflection) | 876.685 | 0.260649 | 512.037ms | 4630 | 1280 | 220596 | 5036.6 | 0.963505 | 3(Loss) | true |
