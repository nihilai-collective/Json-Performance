
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15034.7 | 0.103591 | 876.45ms | 25388 | 30 | 83.4897 | 1610.4 | 0.0787173 | 0.351247 | 1.90941 | 0.118914 | 4.98923e-05 | 1.31296e-05 | 0 | 1(Win) | true |
| simdjson (stage-1) | 13777.1 | 0.0464284 | 889.684ms | 25388 | 30 | 19.9724 | 1757.4 | 0.00758754 | 0.382622 | 1.77726 | 0.0767686 | 7.87774e-05 | 6.56478e-06 | 0 | 2(Loss) | true |
