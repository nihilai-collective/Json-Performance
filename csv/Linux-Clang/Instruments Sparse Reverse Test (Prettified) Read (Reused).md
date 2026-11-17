
----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4894.62 | 0.118032 | 4318.02ms | 183677 | 640 | 1.14196e+06 | 35787.9 | 0.0159909 | 1.04549 | 5.4911 | 0.87153 | 0.000759664 | 2.53502e-06 | 5.52941e-07 | 1(Win) | true |
| simdjson (ondemand) | 4100.07 | 0.0602397 | 5001.86ms | 183677 | 1280 | 847817 | 42723.2 | 0.0489472 | 1.25449 | 6.49251 | 0.932823 | 0.00194123 | 1.61629e-06 | 1.53122e-07 | 2(Loss) | true |
