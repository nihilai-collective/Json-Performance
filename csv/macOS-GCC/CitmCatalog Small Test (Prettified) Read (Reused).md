
----
### CitmCatalog Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1993.59 | 0.45135 | 355.535ms | 5839 | 2560 | 406884 | 2793.2 | 0.569557 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1988.75 | 1.19881 | 392.501ms | 5839 | 160 | 180276 | 2800 | 0.114416 | 1(Tie) | true |
| simdjson (reflection) | 1447.19 | 0.323734 | 463.554ms | 5839 | 4890 | 758771 | 3847.8 | 3.37986 | 3(Loss) | true |
| simdjson (ondemand) | 1399.26 | 0.827707 | 453.32ms | 5839 | 640 | 694403 | 3979.6 | 0.616909 | 4(Loss) | true |
| Glaze | 1271.12 | 1.25426 | 472.285ms | 5839 | 160 | 483060 | 4380.8 | 4.74369 | 5(Loss) | true |
