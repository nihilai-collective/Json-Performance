
----
### CitmCatalog Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2867.99 | 0.0286084 | 5386.58ms | 1151920 | 640 | 7.68525e+06 | 383041 | 0.0289421 | 1.76218 | 8.08584 | 1.39173 | 0.00521427 | 0.0308611 | 8.06263e-06 | 1(Win) | true |
| simdjson (ondemand) | 2699.65 | 0.0633082 | 5697.69ms | 1151920 | 320 | 2.12373e+07 | 406925 | 0.441231 | 1.88573 | 8.28641 | 1.21638 | 0.00729602 | 0.0315005 | 3.39922e-06 | 2(Loss) | true |
