
----
### Marine IK Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 571.72 | 0.0375558 | 1494.21ms | 4604 | 2560 | 21296 | 7679.84 | 0.00215149 | 8.97859 | 35.999 | 7.54551 | 0.0103695 | 0.000141351 | 6.93181e-05 | 1(Win) | true |
| simdjson (ondemand) | 545.704 | 0.0512067 | 1538.85ms | 4604 | 2560 | 43456 | 8045.97 | 0.105488 | 9.47173 | 38.6133 | 6.98176 | 0.0111945 | 0.000178428 | 9.90138e-05 | 2(Loss) | true |
