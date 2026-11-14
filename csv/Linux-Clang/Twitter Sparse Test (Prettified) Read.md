
----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9034.39 | 0.302727 | 3773.32ms | 360584 | 320 | 4.2488e+06 | 38063.4 | 0.324804 | 0.273831 | 1(Win) | true |
| simdjson (ondemand) | 8497.89 | 0.0425549 | 4141.37ms | 360584 | 4890 | 1.4501e+06 | 40466.5 | 0.0678642 | 0.291139 | 2(Loss) | true |
