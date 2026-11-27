
----
### Github Events Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9354.18 | 0.0531747 | 1304.54ms | 53331 | 1280 | 10699.6 | 5437.18 | 0.322044 | 0.551709 | 2.58246 | 0.344509 | 0.000635916 | 1.04155e-05 | 6.34305e-06 | 1(Win) | true |
| simdjson (ondemand) | 7057.97 | 0.0729571 | 1477.06ms | 53331 | 30 | 829.197 | 7206.1 | 0.000462573 | 0.73406 | 3.24637 | 0.386173 | 0.000851287 | 6.25027e-06 | 0 | 2(Loss) | true |
