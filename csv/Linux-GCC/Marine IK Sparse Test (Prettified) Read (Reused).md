
----
### Marine IK Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10318.9 | 0.094668 | 8797.75ms | 7351818 | 320 | 1.32397e+08 | 679455 | 0.281749 | 0.49286 | 2.27773 | 0.235159 | 0.00131787 | 0.0423491 | 2.24902e-05 | 1(Win) | true |
| simdjson (ondemand) | 9572.78 | 0.151571 | 9607.24ms | 7351818 | 40 | 4.92954e+07 | 732414 | 0.133069 | 0.536454 | 2.64671 | 0.256645 | 0.000934436 | 0.0424118 | 0.000266091 | 2(Loss) | true |
