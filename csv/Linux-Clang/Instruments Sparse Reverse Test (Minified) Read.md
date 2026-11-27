
----
### Instruments Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3426.22 | 0.0240084 | 3746.32ms | 108313 | 2560 | 134121 | 30148.4 | 0.0189878 | 1.49857 | 7.98944 | 1.4489 | 0.00149432 | 3.89136e-06 | 1.51471e-06 | 1(Win) | true |
| simdjson (ondemand) | 2533.34 | 0.0473156 | 4805.59ms | 108313 | 1280 | 476423 | 40774.4 | 0.138685 | 2.014 | 10.3325 | 1.59398 | 0.00342149 | 5.00575e-06 | 2.08453e-06 | 2(Loss) | true |
