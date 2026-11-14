
----
### Canada Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2063.81 | 0.518394 | 6177.13ms | 2090234 | 320 | 8.0227e+09 | 965884 | 0.0356812 | 2.45129 | 7.66632 | 0.373336 | 0.000315162 | 0.0511459 | 0.00020832 | 1(Win) | true |
| Glaze | 1518.34 | 0.258169 | 8407.85ms | 2090234 | 160 | 1.83815e+09 | 1.31288e+06 | 0.510799 | 3.32414 | 9.5901 | 0.597292 | 0.0115698 | 0.0438979 | 0.000203258 | 2(Loss) | true |
| simdjson (reflection) | 1037 | 0.54553 | 6033.19ms | 2090326 | 40 | 4.39912e+09 | 1.92236e+06 | 0.223272 | 4.90546 | 15.1539 | 1.43485 | 0.0163124 | 0.0508669 | 0.000227536 | 3(Loss) | true |
