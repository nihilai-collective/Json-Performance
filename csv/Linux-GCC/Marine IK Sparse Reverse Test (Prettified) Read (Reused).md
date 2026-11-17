
----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7872.39 | 0.191997 | 5661.82ms | 7351818 | 80 | 2.33912e+08 | 890611 | 0.0432938 | 0.646791 | 2.97757 | 0.410118 | 0.00136001 | 0.0635568 | 5.61426e-06 | 1(Win) | true |
| simdjson (ondemand) | 5990.43 | 0.298709 | 7423.32ms | 7351818 | 160 | 1.95565e+09 | 1.17041e+06 | 1.47103 | 0.849939 | 4.22109 | 0.606501 | 0.000976823 | 0.0847759 | 0.000386586 | 2(Loss) | true |
