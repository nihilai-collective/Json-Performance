
----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4572.3 | 0.0467624 | 747.538ms | 1691 | 2560 | 69.6391 | 352.703 | 0.0940058 | 1.24943 | 4.70136 | 0.709639 | 0.000591597 | 3.67294e-05 | 1.61702e-06 | 1(Win) | true |
| simdjson (ondemand) | 4054.46 | 0.214375 | 746.785ms | 1691 | 80 | 58.1646 | 397.75 | 0.0628141 | 1.3954 | 5.11413 | 0.719101 | 0.000657895 | 2.95683e-05 | 0 | 2(Loss) | true |
