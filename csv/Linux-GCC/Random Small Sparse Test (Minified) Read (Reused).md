
----
### Random Small Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3202.76 | 0.0882647 | 888.091ms | 4926 | 320 | 536.369 | 1466.8 | 0.0889205 | 1.6441 | 7.54689 | 1.3175 | 0.00112033 | 2.41068e-05 | 5.07511e-06 | 1(Win) | true |
| simdjson (ondemand) | 2344.58 | 0.0368746 | 929.574ms | 4926 | 2560 | 1397.51 | 2003.69 | 0.00257332 | 2.2514 | 9.36947 | 1.50345 | 0.00185075 | 3.14023e-05 | 1.36394e-05 | 2(Loss) | true |
