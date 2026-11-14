
----
### Twitter Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 694.51 | 0.0400772 | 9445.27ms | 264040 | 1280 | 2.70264e+07 | 362570 | 0.133142 | 7.3778 | 28.4659 | 5.3042 | 0.0245361 | 0.00786881 | 5.78274e-05 | 1(Win) | true |
| simdjson (ondemand) | 280.461 | 0.143521 | 5706.31ms | 264040 | 160 | 2.6567e+08 | 897836 | 0.0444182 | 17.9673 | 72.701 | 12.7247 | 0.0883643 | 0.00156446 | 7.51307e-05 | 2(Loss) | true |
