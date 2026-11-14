
----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10138 | 0.0916172 | 821.698ms | 11579 | 160 | 159.336 | 1089.23 | 0.00745883 | 0.526267 | 2.72381 | 0.340962 | 0.00025909 | 8.09655e-06 | 1.07954e-06 | 1(Win) | true |
| simdjson (ondemand) | 8096.72 | 0.117149 | 849.748ms | 11579 | 640 | 1633.72 | 1363.84 | 0.0971725 | 0.654524 | 3.0247 | 0.359703 | 0.000259225 | 5.93747e-06 | 1.07954e-06 | 2(Loss) | true |
