
----
### Random Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3932.79 | 0.0329016 | 9906.98ms | 676745 | 2560 | 7.46316e+06 | 164106 | 0.0804694 | 1.29248 | 5.78246 | 0.961379 | 0.00453852 | 0.000338896 | 4.38854e-06 | 1(Win) | true |
| simdjson (ondemand) | 3458.32 | 0.113797 | 5418.15ms | 676745 | 1280 | 5.77285e+07 | 186621 | 0.017838 | 1.46369 | 6.45235 | 0.948282 | 0.00402245 | 0.00064002 | 6.47285e-06 | 2(Loss) | true |
