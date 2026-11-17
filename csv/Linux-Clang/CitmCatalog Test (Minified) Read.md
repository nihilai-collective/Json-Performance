
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2256.24 | 0.167214 | 5563.97ms | 500299 | 320 | 4.00116e+07 | 211468 | 0.00536843 | 2.22342 | 9.95813 | 1.92721 | 0.0108359 | 0.0064238 | 0.000169617 | 1(Win) | true |
| Glaze | 1795.85 | 0.0971262 | 7051.67ms | 500299 | 80 | 5.32697e+06 | 265680 | 0.026933 | 2.80995 | 12.5367 | 2.36647 | 0.0143075 | 0.00541591 | 5.13693e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1665.27 | 0.252303 | 7542.96ms | 500299 | 30 | 1.56768e+07 | 286514 | 0.00688787 | 3.02718 | 13.2996 | 2.30624 | 0.0155173 | 0.0358063 | 0.000111667 | 3(Loss) | true |
| simdjson (ondemand) | 1129.33 | 0.267028 | 5470.9ms | 500299 | 30 | 3.81811e+07 | 422481 | 0.0132962 | 4.44562 | 18.928 | 2.86647 | 0.0163998 | 0.0336231 | 0.000525086 | 4(Loss) | true |
