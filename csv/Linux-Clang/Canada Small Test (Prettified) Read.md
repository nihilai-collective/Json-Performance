
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1833.72 | 0.127918 | 1322.35ms | 11579 | 30 | 1780.17 | 6021.97 | 0.208246 | 2.83304 | 13.6276 | 2.32516 | 0.00265999 | 1.72726e-05 | 0 | 1(Win) | true |
| Jsonifier (generic) | 1779.29 | 0.0573103 | 1344.77ms | 11579 | 160 | 2024.12 | 6206.19 | 0.0504282 | 2.91478 | 13.7778 | 2.62363 | 0.00222763 | 1.4034e-05 | 2.69885e-06 | 2(Loss) | true |
