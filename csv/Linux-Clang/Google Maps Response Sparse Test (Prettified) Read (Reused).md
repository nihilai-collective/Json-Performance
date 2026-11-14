
----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4243.2 | 0.0503064 | 1300.38ms | 25388 | 160 | 1318.36 | 5706.04 | 0.0459827 | 1.22292 | 5.62372 | 0.938475 | 0.00190814 | 7.63156e-06 | 2.46179e-07 | 1(Win) | true |
| simdjson (ondemand) | 3902.55 | 0.0226765 | 1347.94ms | 25388 | 2560 | 5067.03 | 6204.12 | 0.0654504 | 1.32811 | 5.9948 | 0.882543 | 0.00212562 | 7.64694e-06 | 1.53862e-06 | 2(Loss) | true |
