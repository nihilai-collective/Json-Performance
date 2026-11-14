
----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5249.07 | 0.141635 | 747.844ms | 2158 | 160 | 49.3403 | 392.075 | 0.0669067 | 1.10124 | 3.98424 | 0.592678 | 0.000706673 | 5.7924e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4931.3 | 0.0689836 | 749.993ms | 2158 | 1280 | 106.092 | 417.34 | 0.263706 | 1.15824 | 4.23726 | 0.568582 | 0.000922802 | 4.01848e-05 | 1.15848e-05 | 2(Loss) | true |
