
----
### Marine IK Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 9792.55 | 0.146609 | 9236.86ms | 7351818 | 640 | 7.05176e+08 | 715977 | 0.118352 | 0.524545 | 2.49481 | 0.256655 | 0.000773795 | 0.0424152 | 0.000197785 | 1(Win) | true |
| Jsonifier (generic) | 9420.6 | 0.503668 | 9676.02ms | 7351818 | 40 | 5.62058e+08 | 744246 | 0.140535 | 0.545113 | 2.25894 | 0.261914 | 0.00243191 | 0.0423787 | 0.000213199 | 2(Loss) | true |
