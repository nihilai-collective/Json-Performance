
----
### Discord Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3192.99 | 0.0898437 | 3252.63ms | 83958 | 320 | 162426 | 25076.4 | 0.107667 | 1.58713 | 7.21292 | 1.22015 | 0.00213727 | 3.30895e-05 | 2.3412e-05 | 1(Win) | true |
| simdjson (ondemand) | 3021.52 | 0.0595201 | 3427.38ms | 83958 | 1280 | 318427 | 26499.4 | 0.293746 | 1.68739 | 7.41611 | 1.16037 | 0.00325909 | 2.2649e-05 | 1.32972e-05 | 2(Loss) | true |
