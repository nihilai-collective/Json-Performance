
----
### Random Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2861.99 | 0.0745777 | 894.012ms | 4926 | 1280 | 1918.14 | 1641.44 | 0.00280804 | 1.84436 | 8.15185 | 1.43402 | 0.00219039 | 4.09181e-05 | 1.91903e-05 | 1(Win) | true |
| simdjson (ondemand) | 2298.6 | 0.108966 | 935.199ms | 4926 | 80 | 396.766 | 2043.76 | 0.0312022 | 2.28727 | 9.64657 | 1.46813 | 0.00330644 | 1.77629e-05 | 2.53756e-06 | 2(Loss) | true |
