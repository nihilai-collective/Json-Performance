
----
### Github Events Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4507.02 | 0.0670422 | 746.052ms | 1691 | 1280 | 73.6573 | 357.812 | 0.407991 | 1.27555 | 4.57363 | 0.735068 | 0.000638029 | 2.40242e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4148.26 | 0.111863 | 750.211ms | 1691 | 320 | 60.5172 | 388.756 | 0.0337729 | 1.3711 | 5.10171 | 0.713187 | 0.000591366 | 4.80485e-05 | 0 | 2(Loss) | true |
