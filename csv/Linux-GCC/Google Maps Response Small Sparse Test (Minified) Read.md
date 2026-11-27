
----
### Google Maps Response Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2579.41 | 0.0441498 | 888.805ms | 4390 | 2560 | 1314.58 | 1623.1 | 0.113386 | 2.04194 | 9.3 | 1.65285 | 0.000886781 | 1.75292e-05 | 3.47024e-06 | 1(Win) | true |
| simdjson (ondemand) | 1942.34 | 0.034684 | 947.587ms | 4390 | 2560 | 1430.8 | 2155.46 | 0.0854293 | 2.68152 | 11.3444 | 1.90456 | 0.00227105 | 3.15881e-05 | 9.87685e-06 | 2(Loss) | true |
