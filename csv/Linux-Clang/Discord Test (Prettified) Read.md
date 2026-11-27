
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13778.1 | 0.0365499 | 1302.31ms | 83958 | 80 | 360.916 | 5811.29 | 0.0191401 | 0.376603 | 2.09171 | 0.133853 | 3.67743e-05 | 1.93549e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 12665 | 0.0250516 | 1352.01ms | 83958 | 40 | 100.333 | 6322.02 | 0.00303182 | 0.409419 | 1.9729 | 0.0848519 | 3.57322e-05 | 1.78661e-06 | 0 | 2(Loss) | true |
