
----
### Instruments Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4746.17 | 0.0952641 | 807.771ms | 4669 | 640 | 511.211 | 938.169 | 0.0479888 | 1.13207 | 4.89848 | 0.701007 | 0.00107156 | 2.17525e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4480.39 | 0.0318305 | 810.764ms | 4669 | 2560 | 256.18 | 993.822 | 0.0718771 | 1.19579 | 5.36496 | 0.640609 | 0.00143508 | 2.03302e-05 | 1.92426e-06 | 2(Loss) | true |
