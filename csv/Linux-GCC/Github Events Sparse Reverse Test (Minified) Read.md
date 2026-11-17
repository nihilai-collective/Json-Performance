
----
### Github Events Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5634.53 | 0.215028 | 1635.48ms | 53331 | 320 | 120555 | 9026.56 | 0.0355328 | 0.909259 | 4.34646 | 0.704637 | 0.00169314 | 3.1056e-06 | 1.17193e-07 | 1(Win) | true |
| simdjson (ondemand) | 4220.43 | 0.0505927 | 1928.22ms | 53331 | 640 | 23790.4 | 12051 | 0.0238124 | 1.22353 | 5.85993 | 0.956761 | 0.00236351 | 3.1642e-06 | 7.03156e-07 | 2(Loss) | true |
