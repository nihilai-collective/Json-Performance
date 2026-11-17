
----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3644.4 | 0.0402175 | 770.693ms | 2158 | 2560 | 132.045 | 564.71 | 0.0388599 | 1.51434 | 5.79564 | 0.988415 | 0.000865783 | 4.01848e-05 | 9.59366e-06 | 1(Win) | true |
| simdjson (ondemand) | 3187.43 | 0.106543 | 792.339ms | 2158 | 640 | 302.869 | 645.67 | 0.293164 | 1.74692 | 7.04032 | 1.13531 | 0.000729842 | 4.19949e-05 | 2.31696e-05 | 2(Loss) | true |
