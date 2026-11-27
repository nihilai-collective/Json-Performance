
----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2220.92 | 0.206996 | 1122ms | 8150 | 40 | 2099.11 | 3499.65 | 0.499919 | 2.34697 | 9.28613 | 1.62012 | 0.00515337 | 5.21472e-05 | 2.76074e-05 | 1(Win) | true |
| simdjson (ondemand) | 1836.96 | 0.194082 | 1191.72ms | 8150 | 40 | 2697.41 | 4231.15 | 0.104494 | 2.83181 | 10.7043 | 1.72699 | 0.0061319 | 6.13497e-05 | 3.06748e-05 | 2(Loss) | true |
