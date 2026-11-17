
----
### Github Events Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8770.53 | 0.0678761 | 1336.2ms | 53331 | 320 | 4957.83 | 5799.01 | 0.0572507 | 0.59032 | 2.86698 | 0.364797 | 0.000726887 | 6.91437e-06 | 2.81262e-06 | 1(Win) | true |
| simdjson (ondemand) | 7139.8 | 0.0444797 | 1456.17ms | 53331 | 160 | 1606.31 | 7123.51 | 0.0880987 | 0.725782 | 3.25407 | 0.385554 | 0.000953128 | 8.78945e-06 | 6.91437e-06 | 2(Loss) | true |
