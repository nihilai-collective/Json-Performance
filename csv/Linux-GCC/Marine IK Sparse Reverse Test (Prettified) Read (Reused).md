
----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7694.53 | 0.225132 | 5824.46ms | 7351818 | 80 | 3.36658e+08 | 911198 | 0.279849 | 0.665686 | 2.97757 | 0.410118 | 0.00141679 | 0.0635585 | 0.000230531 | 1(Win) | true |
| simdjson (ondemand) | 5942.84 | 0.183878 | 7474.15ms | 7351818 | 160 | 7.52974e+08 | 1.17978e+06 | 0.0671105 | 0.860384 | 4.22109 | 0.606501 | 0.00102076 | 0.084758 | 0.000517061 | 2(Loss) | true |
