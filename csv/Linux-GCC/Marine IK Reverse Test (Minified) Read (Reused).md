
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 422.324 | 0.111781 | 6562.43ms | 1834197 | 40 | 8.57427e+08 | 4.14191e+06 | 0.137507 | 11.9129 | 57.0247 | 12.6111 | 0.0375349 | 0.323185 | 0.00171559 | 1(Win) | true |
| simdjson (ondemand) | 280.702 | 0.132936 | 9707.68ms | 1834197 | 40 | 2.74502e+09 | 6.23162e+06 | 0.081912 | 18.1281 | 98.953 | 20.4767 | 0.0467955 | 0.768582 | 0.0125624 | 2(Loss) | true |
