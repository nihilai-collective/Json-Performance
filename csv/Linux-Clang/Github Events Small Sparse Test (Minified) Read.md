
----
### Github Events Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4833.25 | 0.0696506 | 762.093ms | 1691 | 4890 | 264.099 | 333.66 | 0.0273925 | 1.19626 | 4.41573 | 0.712596 | 0.000591608 | 7.31649e-05 | 3.84569e-05 | 1(Win) | true |
| simdjson (ondemand) | 3906.53 | 0.638912 | 772.093ms | 1691 | 160 | 1113.03 | 412.812 | 0.0242182 | 1.42323 | 5.11886 | 0.719692 | 0.000591366 | 8.87049e-05 | 7.39208e-05 | 2(Loss) | true |
