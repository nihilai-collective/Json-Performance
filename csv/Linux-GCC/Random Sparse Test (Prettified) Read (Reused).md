
----
### Random Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4358.07 | 0.0455662 | 8900.04ms | 676745 | 1280 | 5.8285e+06 | 148092 | 0.039926 | 1.16246 | 5.56839 | 0.912184 | 0.00333387 | 0.000410921 | 1.36487e-05 | 1(Win) | true |
| simdjson (ondemand) | 3423.5 | 0.0318962 | 5484.1ms | 676745 | 1280 | 4.62806e+06 | 188519 | 0.0579003 | 1.48362 | 6.35492 | 0.967453 | 0.00510378 | 0.000366694 | 1.23292e-05 | 2(Loss) | true |
