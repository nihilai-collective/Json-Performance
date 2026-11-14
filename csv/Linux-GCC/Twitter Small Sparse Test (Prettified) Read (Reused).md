
----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6596.64 | 0.0810141 | 777.289ms | 3770 | 4890 | 953.382 | 545.028 | 0.181777 | 0.827842 | 3.30902 | 0.377984 | 0.00026536 | 2.43012e-05 | 6.61774e-06 | 1(Win) | true |
| simdjson (ondemand) | 6433.7 | 0.0568139 | 778.501ms | 3770 | 1280 | 129.027 | 558.831 | 0.233758 | 0.850427 | 3.41538 | 0.342175 | 0.000266288 | 1.82361e-05 | 3.31565e-06 | 2(Loss) | true |
