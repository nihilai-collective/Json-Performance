
----
### Marine IK Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4370.83 | 0.187109 | 5198.84ms | 1834197 | 40 | 2.24292e+07 | 400205 | 0.0570736 | 1.17581 | 6.02462 | 0.923066 | 0.00648131 | 0.0755408 | 1.30302e-05 | 1(Win) | true |
| simdjson (ondemand) | 4341.28 | 0.0758303 | 5234.48ms | 1834197 | 160 | 1.49369e+07 | 402928 | 0.23485 | 1.16996 | 6.37297 | 0.86779 | 0.0034266 | 0.0754631 | 6.32089e-06 | 2(Loss) | true |
