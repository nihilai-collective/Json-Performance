
----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8920.77 | 0.0203041 | 1437.81ms | 65103 | 4890 | 9765.05 | 6959.83 | 0.0723617 | 0.580482 | 2.72779 | 0.310508 | 0.000688492 | 3.16629e-06 | 5.21433e-07 | 1(Win) | true |
| simdjson (ondemand) | 8082.64 | 0.0233357 | 1502.81ms | 65103 | 2560 | 8225.78 | 7681.53 | 0.00600095 | 0.640407 | 2.93235 | 0.327282 | 0.000752239 | 6.94212e-06 | 2.74205e-06 | 2(Loss) | true |
