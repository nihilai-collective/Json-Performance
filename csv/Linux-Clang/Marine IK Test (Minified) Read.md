
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 683.276 | 0.0718715 | 8003.39ms | 1834197 | 30 | 1.01563e+08 | 2.56006e+06 | 0.348637 | 3.62333 | 1(Win) | true |
| simdjson (ondemand) | 652.395 | 0.052099 | 8438.21ms | 1834197 | 40 | 7.80528e+07 | 2.68124e+06 | 0.0167662 | 3.79488 | 2(Loss) | true |
