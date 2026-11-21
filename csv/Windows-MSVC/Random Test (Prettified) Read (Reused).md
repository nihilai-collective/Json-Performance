
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1414.1 | 0.330205 | 7560.33ms | 728486 | 40 | 1.05271e+08 | 491292 | 0.0222252 | 1.75073 | 1(Win) | true |
| Jsonifier | 1331.43 | 0.313797 | 8151.92ms | 728486 | 30 | 8.04317e+07 | 521800 | 0.0146949 | 1.85945 | 2(Loss) | true |
| Glaze | 1156.84 | 0.371231 | 9144.54ms | 728486 | 30 | 1.49109e+08 | 600547 | 0.337495 | 2.13999 | 3(Loss) | true |
| simdjson (ondemand) | 1020.41 | 0.358565 | 9990.04ms | 728486 | 30 | 1.78791e+08 | 680840 | 0.0435926 | 2.42608 | 4(Loss) | true |
