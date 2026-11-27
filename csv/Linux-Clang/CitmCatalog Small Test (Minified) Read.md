
----
### CitmCatalog Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1161.27 | 0.0753552 | 1153.34ms | 5092 | 640 | 6355.05 | 4181.74 | 0.0635919 | 4.47616 | 18.541 | 3.38119 | 0.00294825 | 5.0324e-05 | 1.4729e-05 | 1(Win) | true |
| simdjson (ondemand) | 1125.77 | 0.119746 | 1161.49ms | 5092 | 320 | 8537.92 | 4313.59 | 0.0987903 | 4.57903 | 18.6974 | 3.14022 | 0.00250086 | 3.55951e-05 | 9.81932e-06 | 2(Loss) | true |
