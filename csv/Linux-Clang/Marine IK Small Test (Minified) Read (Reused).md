
----
### Marine IK Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1154.32 | 0.0619695 | 465.742ms | 4604 | 30 | 166.685 | 3803.73 | 0.265355 | 2.13068 | 1(Win) | true |
| Jsonifier (two-stage) | 965.441 | 0.0830894 | 534.6ms | 4604 | 80 | 1142.35 | 4547.89 | 0.199666 | 2.54832 | 2(Loss) | true |
| Glaze | 774.291 | 0.17398 | 653.636ms | 4604 | 2560 | 249172 | 5670.63 | 0.143166 | 3.18298 | 3(Loss) | true |
| simdjson (ondemand) | 588.889 | 0.0943111 | 829.723ms | 4604 | 30 | 1483.37 | 7455.93 | 0.220444 | 4.18744 | 4(Loss) | true |
