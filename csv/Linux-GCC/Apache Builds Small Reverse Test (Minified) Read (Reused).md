
----
### Apache Builds Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1416.65 | 0.082987 | 908.492ms | 2632 | 2560 | 5534.88 | 1771.84 | 0.0232202 | 3.68767 | 14.6155 | 2.80395 | 0.00467919 | 5.14996e-05 | 8.90483e-06 | 1(Win) | true |
| simdjson (ondemand) | 782.016 | 0.0380843 | 1057.57ms | 2632 | 160 | 239.085 | 3209.74 | 0.0399335 | 6.67405 | 27.6767 | 5.54825 | 0.00948423 | 2.13716e-05 | 0 | 2(Loss) | true |
