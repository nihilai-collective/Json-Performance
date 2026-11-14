
----
### Twitter Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 752.891 | 0.0829156 | 9184.05ms | 264040 | 320 | 2.46092e+07 | 334455 | 0.0314098 | 6.80607 | 27.0427 | 4.97483 | 0.0205102 | 0.0015017 | 2.81207e-05 | 1(Win) | true |
| simdjson (ondemand) | 290.324 | 0.149989 | 5634.1ms | 264040 | 160 | 2.70776e+08 | 867334 | 0.323481 | 17.3758 | 71.272 | 12.3951 | 0.0834951 | 0.00012446 | 2.7458e-05 | 2(Loss) | true |
