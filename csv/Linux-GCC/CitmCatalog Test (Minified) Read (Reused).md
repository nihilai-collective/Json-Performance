
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2483.23 | 0.30701 | 5851.54ms | 500299 | 40 | 1.39184e+07 | 192138 | 0.129466 | 0.996852 | 1(Win) | true |
| Jsonifier (two-stage) | 2124.69 | 0.210708 | 6698.94ms | 500299 | 1280 | 2.86578e+08 | 224561 | 0.0657725 | 1.16506 | 2(Loss) | true |
| simdjson (ondemand) | 1878.05 | 0.0844868 | 7384.1ms | 500299 | 1280 | 5.89705e+07 | 254053 | 0.472928 | 1.31811 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1796.98 | 0.152965 | 7727.6ms | 500299 | 320 | 5.2784e+07 | 265513 | 0.381034 | 1.37757 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 1793.15 | 0.275923 | 7685.23ms | 500299 | 30 | 1.61705e+07 | 266080 | 0.111983 | 1.38054 | 4(Tie) | true |
