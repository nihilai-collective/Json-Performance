
----
### Canada Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7587.25 | 0.138581 | 6904.88ms | 2090234 | 80 | 1.06052e+07 | 262731 | 0.0460712 | 0.668257 | 3.18839 | 0.436402 | 0.0063996 | 0.0506512 | 3.80938e-06 | 1(Win) | true |
| simdjson (ondemand) | 7248.36 | 0.11431 | 7247.68ms | 2090234 | 160 | 1.58124e+07 | 275014 | 0.00662737 | 0.704394 | 3.6662 | 0.41839 | 0.00285939 | 0.050828 | 2.81069e-06 | 2(Loss) | true |
