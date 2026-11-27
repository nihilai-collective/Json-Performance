
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2515.44 | 0.0312925 | 7914.44ms | 183677 | 1280 | 607816 | 69637.2 | 0.0190229 | 2.01342 | 9.01236 | 1.61519 | 0.00201107 | 7.1457e-06 | 4.28742e-06 | 1(Win) | true |
| simdjson (ondemand) | 2481.23 | 0.0611341 | 7988.11ms | 183677 | 4890 | 9.10858e+06 | 70597.2 | 0.183115 | 2.04886 | 9.79527 | 1.37029 | 0.00362388 | 1.76512e-05 | 1.39148e-05 | 2(Loss) | true |
