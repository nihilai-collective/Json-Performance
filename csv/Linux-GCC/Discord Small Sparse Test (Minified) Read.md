
----
### Discord Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4085.02 | 0.0356751 | 827.16ms | 4857 | 1280 | 209.454 | 1133.9 | 0.162246 | 1.30388 | 5.5176 | 0.850731 | 0.000208301 | 2.39667e-05 | 6.43401e-07 | 1(Win) | true |
| simdjson (ondemand) | 3721.57 | 0.0626394 | 839.522ms | 4857 | 4890 | 2972.27 | 1244.64 | 0.171046 | 1.42639 | 5.97694 | 0.835084 | 0.000265676 | 2.58097e-05 | 3.78936e-06 | 2(Loss) | true |
