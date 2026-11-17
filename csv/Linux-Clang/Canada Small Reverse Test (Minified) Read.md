
----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 715.298 | 0.0508107 | 1340.76ms | 4630 | 320 | 3148.1 | 6172.97 | 0.0837514 | 7.24869 | 36.4618 | 7.09374 | 0.00552916 | 3.57721e-05 | 4.04968e-06 | 1(Win) | true |
| simdjson (ondemand) | 680.515 | 0.0229876 | 1373.84ms | 4630 | 4890 | 10878.8 | 6488.48 | 0.0730479 | 7.6105 | 37.4309 | 6.78726 | 0.00410323 | 9.65518e-05 | 3.74105e-05 | 2(Loss) | true |
