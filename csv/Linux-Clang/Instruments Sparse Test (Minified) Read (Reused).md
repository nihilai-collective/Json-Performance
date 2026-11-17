
----
### Instruments Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5353.87 | 0.0583221 | 2699.46ms | 108313 | 80 | 10129.4 | 19293.6 | 0.0227355 | 0.964299 | 5.35389 | 0.803671 | 0.000803689 | 2.76975e-06 | 1.96191e-06 | 1(Win) | true |
| simdjson (ondemand) | 4483.7 | 0.0422139 | 3045.76ms | 108313 | 1280 | 121063 | 23038 | 0.0656162 | 1.14163 | 5.92018 | 0.723718 | 0.00110382 | 2.71205e-06 | 7.93418e-07 | 2(Loss) | true |
