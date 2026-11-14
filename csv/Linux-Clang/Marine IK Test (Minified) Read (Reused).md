
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 647.816 | 0.0802714 | 9130.64ms | 1834197 | 160 | 7.51676e+08 | 2.70019e+06 | 0.00378413 | 7.83718 | 33.8187 | 6.60873 | 0.0374876 | 0.118291 | 0.00130065 | 1(Win) | true |
| simdjson (ondemand) | 623.509 | 0.096303 | 9413.75ms | 1834197 | 40 | 2.91975e+08 | 2.80545e+06 | 0.146193 | 8.11485 | 34.2262 | 5.65997 | 0.0443827 | 0.118706 | 0.0010315 | 2(Loss) | true |
