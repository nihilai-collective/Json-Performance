
----
### Github Events Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5123.63 | 0.237277 | 763.365ms | 1691 | 80 | 44.6203 | 314.75 | 0.474308 | 1.14954 | 4.13779 | 0.645772 | 0.000887049 | 4.43525e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4020.14 | 0.0369495 | 751.598ms | 1691 | 2560 | 56.2423 | 401.146 | 0.167112 | 1.41268 | 5.10171 | 0.722058 | 0.000759305 | 3.04923e-05 | 6.23706e-06 | 2(Loss) | true |
