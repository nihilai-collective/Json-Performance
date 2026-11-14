
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2624.2 | 0.123457 | 939.271ms | 4857 | 4890 | 23221.2 | 1765.11 | 0.146831 | 1.96897 | 7.40416 | 1.31213 | 0.000873615 | 3.54936e-05 | 7.53661e-06 | 1(Win) | true |
| Glaze | 2533.78 | 0.0936754 | 944.263ms | 4857 | 4890 | 14340.3 | 1828.1 | 0.182667 | 2.0416 | 8.92506 | 1.60984 | 0.00119782 | 4.51355e-05 | 6.02087e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2165.28 | 0.10576 | 976.18ms | 4857 | 4890 | 25029.9 | 2139.22 | 0.0453427 | 2.37871 | 9.68376 | 1.60552 | 0.00077345 | 3.26306e-05 | 4.2525e-06 | 3(Loss) | true |
| simdjson (ondemand) | 865.241 | 0.10179 | 1298.86ms | 4857 | 2560 | 76017.8 | 5353.42 | 0.0965341 | 5.88647 | 20.6695 | 3.47622 | 0.0035823 | 3.81215e-05 | 4.02126e-06 | 4(Loss) | true |
