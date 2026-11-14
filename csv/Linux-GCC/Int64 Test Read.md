
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2880.1 | 0.0401274 | 131.495ms | 3862 | 160 | 42.132 | 1278.81 | 0.039572 | 0.842007 | 1(Win) | true |
| simdjson (stage-1) | 1320.58 | 0.0616367 | 285.72ms | 3862 | 40 | 118.205 | 2789 | 0.0310648 | 1.85625 | 2(Loss) | true |
