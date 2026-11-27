
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 7405.32 | 0.181356 | 6357.62ms | 1834197 | 80 | 1.4681e+07 | 236212 | 0.316297 | 0.694399 | 3.00091 | 0.221873 | 0.00679348 | 0.037707 | 1.30166e-06 | 1(Win) | true |
| simdjson (stage-1) | 7035.98 | 0.0566393 | 6575.29ms | 1834197 | 640 | 1.26899e+07 | 248612 | 0.243604 | 0.730844 | 3.08886 | 0.152979 | 0.00431101 | 0.0376926 | 2.08453e-06 | 2(Loss) | true |
