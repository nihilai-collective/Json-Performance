
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2416.69 | 0.0459026 | 829.005ms | 2632 | 4890 | 1111.51 | 1038.64 | 0.0879358 | 2.21332 | 9.13298 | 1.64058 | 0.000765473 | 4.56859e-05 | 7.53663e-06 | 1(Win) | true |
| simdjson (ondemand) | 1955.86 | 0.136668 | 867.206ms | 2632 | 320 | 984.412 | 1283.36 | 0.0316453 | 2.71792 | 10.3788 | 1.71163 | 0.0024423 | 5.69909e-05 | 3.56193e-06 | 2(Loss) | true |
