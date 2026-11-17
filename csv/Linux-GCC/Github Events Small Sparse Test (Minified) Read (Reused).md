
----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5046.33 | 0.0945505 | 742.528ms | 1691 | 4890 | 446.45 | 319.572 | 0.0444452 | 1.15318 | 4.3702 | 0.635128 | 0.000592334 | 4.81316e-05 | 3.08381e-05 | 1(Win) | true |
| simdjson (ondemand) | 4416.44 | 0.185325 | 747.995ms | 1691 | 80 | 36.6354 | 365.15 | 0.0479485 | 1.31678 | 4.79539 | 0.64518 | 0.00113838 | 4.43525e-05 | 0 | 2(Loss) | true |
