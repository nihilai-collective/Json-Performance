
----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 26266.7 | 0.138069 | 35.8603ms | 9255 | 160 | 34.4396 | 336.025 | 0.0371858 | 0.0869152 | 1(Win) | true |
| Glaze | 4873.79 | 0.199039 | 187.733ms | 9255 | 80 | 1039.4 | 1810.96 | 0.0696657 | 0.500978 | 2(Loss) | true |
| simdjson (reflection) | 557.075 | 0.130503 | 1597.17ms | 9255 | 1280 | 547240 | 15843.9 | 0.205657 | 4.43551 | 3(Loss) | true |
