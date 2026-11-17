
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4675.62 | 0.0692257 | 201.771ms | 9578 | 30 | 54.869 | 1953.6 | 0.0358185 | 0.522183 | 1(Win) | true |
| simdjson (stage-1) | 3444.3 | 0.0686062 | 266.127ms | 9578 | 30 | 99.3103 | 2652 | 0.075358 | 0.711394 | 2(Loss) | true |
