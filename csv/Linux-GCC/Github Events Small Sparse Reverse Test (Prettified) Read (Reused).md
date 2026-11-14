
----
### Github Events Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3930.31 | 0.0809983 | 764.08ms | 2158 | 1280 | 230.257 | 523.63 | 0.14972 | 1.40658 | 5.54866 | 0.921223 | 0.000905425 | 2.42557e-05 | 3.62025e-07 | 1(Win) | true |
| simdjson (ondemand) | 3420.57 | 0.0857026 | 773.444ms | 2158 | 320 | 85.0832 | 601.663 | 0.0301339 | 1.60338 | 6.65941 | 1.08712 | 0.000519868 | 1.59291e-05 | 0 | 2(Loss) | true |
