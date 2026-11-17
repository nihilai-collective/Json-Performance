
----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 957.051 | 0.0484214 | 9771.03ms | 360584 | 1280 | 3.8746e+07 | 359312 | 0.0153012 | 5.32806 | 20.6653 | 3.83763 | 0.0126075 | 0.00010351 | 3.86092e-05 | 1(Win) | true |
| simdjson (ondemand) | 399.633 | 0.122892 | 5578ms | 360584 | 320 | 3.57836e+08 | 860489 | 0.0428843 | 12.6119 | 51.8599 | 8.96679 | 0.054253 | 0.000342145 | 4.50484e-05 | 2(Loss) | true |
