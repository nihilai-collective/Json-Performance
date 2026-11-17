
----
### Apache Builds Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1267.33 | 0.030277 | 919.156ms | 2632 | 4890 | 1758.44 | 1980.6 | 0.00305431 | 4.14641 | 16.5935 | 3.2538 | 0.00559272 | 7.07044e-05 | 1.39078e-05 | 1(Win) | true |
| simdjson (ondemand) | 722.694 | 0.0714281 | 1068.19ms | 2632 | 320 | 1969.48 | 3473.21 | 0.00521824 | 7.20903 | 30.9183 | 5.91224 | 0.011505 | 4.51178e-05 | 2.37462e-06 | 2(Loss) | true |
