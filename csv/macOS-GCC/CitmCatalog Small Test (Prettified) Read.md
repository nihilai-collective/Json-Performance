
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 1396.17 | 0.486261 | 403.923ms | 5839 | 1280 | 481445 | 3988.4 | 0.170204 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1375.62 | 2.00647 | 355.702ms | 5839 | 80 | 527762 | 4048 | 0.396825 | 1(Tie) | true |
| simdjson (ondemand) | 1236.65 | 0.288749 | 473.272ms | 5839 | 4890 | 826666 | 4502.88 | 0.048386 | 3(Loss) | true |
| Glaze | 1207.29 | 0.423991 | 509.198ms | 5839 | 1280 | 489528 | 4612.4 | 0.987464 | 4(Loss) | true |
| simdjson (reflection) | 1164.18 | 0.595357 | 460.279ms | 5839 | 2560 | 2.07602e+06 | 4783.2 | 0.366606 | 5(Loss) | true |
