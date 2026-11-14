
----
### Github Events Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8099.61 | 0.0406566 | 1352.41ms | 53331 | 4890 | 31871.5 | 6279.37 | 0.00792967 | 0.637198 | 3.01418 | 0.39898 | 0.000712669 | 3.38588e-06 | 9.12617e-07 | 1(Win) | true |
| simdjson (ondemand) | 6829.08 | 0.0801078 | 1463.94ms | 53331 | 640 | 22780.6 | 7447.62 | 0.0279373 | 0.756721 | 3.39 | 0.417768 | 0.000833913 | 1.19829e-05 | 5.62525e-06 | 2(Loss) | true |
