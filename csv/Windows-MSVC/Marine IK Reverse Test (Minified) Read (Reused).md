
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 624.178 | 0.501004 | 9545.2ms | 1834197 | 40 | 7.88529e+09 | 2.80245e+06 | 0.0422428 | 4.86897 | 1(Win) | true |
| Jsonifier | 496.936 | 0.198991 | 5688.72ms | 1834197 | 80 | 3.92508e+09 | 3.52002e+06 | 0.213379 | 6.11603 | 2(Loss) | true |
| Glaze | 333.83 | 0.229626 | 8354.17ms | 1834197 | 80 | 1.15817e+10 | 5.23987e+06 | 0.464684 | 9.10402 | 3(Loss) | true |
| simdjson (ondemand) | 203.674 | 0.194806 | 6185.42ms | 1834197 | 30 | 8.39739e+09 | 8.58835e+06 | 0.0612083 | 14.9214 | 4(Loss) | true |
