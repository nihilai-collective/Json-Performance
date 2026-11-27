
----
### Random Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2765.29 | 0.175777 | 6619.51ms | 676745 | 640 | 1.07714e+08 | 233391 | 0.0739894 | 1.09899 | 1(Win) | true |
| simdjson (ondemand) | 2122.25 | 0.378513 | 8500.36ms | 676745 | 160 | 2.12002e+08 | 304109 | 0.279544 | 1.43201 | 2(Loss) | true |
