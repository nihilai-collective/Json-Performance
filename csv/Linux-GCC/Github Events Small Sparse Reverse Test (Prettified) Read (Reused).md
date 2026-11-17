
----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3892.25 | 0.162018 | 769.155ms | 2158 | 160 | 117.421 | 528.75 | 0.0449374 | 1.42547 | 5.54866 | 0.921223 | 0.0013757 | 4.05468e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3474.38 | 0.111595 | 772.152ms | 2158 | 160 | 69.9125 | 592.344 | 0.0896057 | 1.58288 | 6.65477 | 1.0848 | 0.000489458 | 8.6886e-06 | 2.8962e-06 | 2(Loss) | true |
