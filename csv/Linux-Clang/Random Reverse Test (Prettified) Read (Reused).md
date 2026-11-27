
----
### Random Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1432.73 | 0.0672681 | 6376.55ms | 676745 | 160 | 1.46914e+07 | 450466 | 0.0567665 | 3.53622 | 16.4046 | 3.27024 | 0.00669359 | 0.0100306 | 8.72744e-06 | 1(Win) | true |
| simdjson (ondemand) | 796.333 | 0.163458 | 5505.12ms | 676745 | 40 | 7.01992e+07 | 810458 | 0.184009 | 6.40068 | 29.0765 | 5.18503 | 0.0204388 | 0.0170054 | 4.17439e-05 | 2(Loss) | true |
