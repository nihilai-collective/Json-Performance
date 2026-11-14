
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 672.427 | 0.102427 | 8825.25ms | 1834197 | 40 | 2.83982e+08 | 2.60136e+06 | 0.30137 | 3.68184 | 1(Win) | true |
| simdjson (ondemand) | 669.115 | 0.069719 | 8805.57ms | 1834197 | 30 | 9.96584e+07 | 2.61424e+06 | 0.126876 | 3.70006 | 2(Loss) | true |
