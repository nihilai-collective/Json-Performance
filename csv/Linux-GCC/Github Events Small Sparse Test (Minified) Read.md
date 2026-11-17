
----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4595.37 | 0.100309 | 746.425ms | 1691 | 4890 | 605.951 | 350.932 | 0.0627767 | 1.249 | 4.70136 | 0.70964 | 0.000592213 | 2.86613e-05 | 8.2235e-06 | 1(Win) | true |
| simdjson (ondemand) | 3976.67 | 0.102081 | 750.829ms | 1691 | 320 | 54.8391 | 405.531 | 0.021572 | 1.42338 | 5.11709 | 0.719692 | 0.00110142 | 4.62005e-05 | 7.39208e-06 | 2(Loss) | true |
