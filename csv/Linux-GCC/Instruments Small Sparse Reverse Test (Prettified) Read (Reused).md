
----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5160.34 | 0.185901 | 874.716ms | 7932 | 160 | 1188.2 | 1465.9 | 0.126362 | 1.00729 | 4.7587 | 0.775845 | 0.000828133 | 1.26072e-05 | 9.45537e-06 | 1(Win) | true |
| simdjson (ondemand) | 4380.29 | 0.0402607 | 898.454ms | 7932 | 320 | 154.693 | 1726.95 | 0.16043 | 1.20363 | 5.97037 | 0.894856 | 0.00147228 | 1.4577e-05 | 3.93974e-07 | 2(Loss) | true |
