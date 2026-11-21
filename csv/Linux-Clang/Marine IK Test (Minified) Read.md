
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 847.508 | 0.144554 | 6572.07ms | 1834197 | 40 | 3.56059e+08 | 2.06396e+06 | 4.60301 | 2.92123 | -(Win) | false |
| Jsonifier (two-stage) | 789.709 | 0.0534151 | 6888.47ms | 1834197 | 80 | 1.11989e+08 | 2.21503e+06 | 0.146347 | 3.13504 | 2(Loss) | true |
| Glaze | 677.441 | 0.501139 | 8208.6ms | 1834197 | 160 | 2.67908e+10 | 2.58211e+06 | 0.416448 | 3.65461 | 3(Loss) | true |
| simdjson (ondemand) | 626.239 | 0.0982681 | 8773.81ms | 1834197 | 80 | 6.02735e+08 | 2.79322e+06 | 0.220126 | 3.95341 | 4(Loss) | true |
