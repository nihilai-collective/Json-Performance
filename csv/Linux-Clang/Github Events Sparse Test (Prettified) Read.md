
----
### Github Events Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8198.93 | 0.0431372 | 1481.06ms | 65103 | 1280 | 13658.5 | 7572.58 | 0.0505367 | 0.631125 | 2.83288 | 0.360045 | 0.00078149 | 6.90012e-06 | 3.32406e-06 | 1(Win) | true |
| simdjson (ondemand) | 7732.02 | 0.0549452 | 1535.75ms | 65103 | 320 | 6229.12 | 8029.86 | 0.0417796 | 0.66941 | 2.98315 | 0.352196 | 0.000814431 | 4.65608e-06 | 1.63203e-06 | 2(Loss) | true |
