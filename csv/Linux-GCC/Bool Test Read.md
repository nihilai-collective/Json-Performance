
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1023.41 | 0.100404 | 793.956ms | 905 | 160 | 114.713 | 843.331 | 0.0200059 | 5.27724 | 28.4133 | 2.51271 | 0.00505525 | 8.9779e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 345.069 | 0.127964 | 969.886ms | 905 | 30 | 307.316 | 2501.17 | 0.151699 | 15.1726 | 76.4972 | 5.79558 | 0.00220994 | 7.36648e-05 | 7.36648e-05 | 2(Loss) | true |
