
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 678.874 | 0.136713 | 8230.8ms | 1834197 | 30 | 3.72265e+08 | 2.57666e+06 | 3.02018 | 3.6469 | -(Win) | false |
| Jsonifier (two-stage) | 569.898 | 0.500257 | 9089.6ms | 1834197 | 30 | 7.07303e+09 | 3.06937e+06 | 0.914112 | 4.34396 | 2(Loss) | true |
| simdjson (ondemand) | 236.194 | 0.49725 | 5364.9ms | 1834197 | 40 | 5.42455e+10 | 7.40589e+06 | 1.4037 | 10.4821 | 3(Loss) | true |
| Glaze | 198.939 | 0.357518 | 6239.64ms | 1834197 | 40 | 3.95283e+10 | 8.79278e+06 | 1.0441 | 12.445 | 4(Loss) | true |
