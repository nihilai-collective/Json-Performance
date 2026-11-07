
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1853.87 | 0.218629 | 49.3377ms | 905 | 2560 | 2652.11 | 465.552 | 0.644246 | 1.26243 | 1(Win) | true |
| Glaze | 1556.63 | 0.071011 | 59.5192ms | 905 | 160 | 24.8025 | 554.45 | 0.0180391 | 1.51941 | 2(Loss) | true |
| Jsonifier (two-stage) | 526.407 | 0.0201512 | 167.2ms | 905 | 320 | 34.9306 | 1639.56 | 0.0543505 | 4.6279 | 3(Loss) | true |
| simdjson (ondemand) | 262.854 | 0.0417242 | 329.878ms | 905 | 40 | 75.0763 | 3283.47 | 0.0900165 | 9.34552 | 4(Loss) | true |
