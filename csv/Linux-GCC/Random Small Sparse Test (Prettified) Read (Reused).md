
----
### Random Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3926.49 | 0.0856225 | 923.862ms | 8150 | 160 | 459.622 | 1979.49 | 0.0769808 | 1.33845 | 5.92282 | 0.921595 | 0.00155215 | 2.30061e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3509.66 | 0.0895558 | 946.552ms | 8150 | 80 | 314.676 | 2214.59 | 0.0445708 | 1.49454 | 6.13055 | 0.907853 | 0.00169632 | 6.13497e-06 | 0 | 2(Loss) | true |
