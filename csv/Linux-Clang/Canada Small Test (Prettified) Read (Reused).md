
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2166.08 | 0.129998 | 1343.16ms | 11579 | 30 | 1317.62 | 5097.97 | 0.0196118 | 2.35418 | 10.9678 | 2.04379 | 0.00268302 | 5.75755e-05 | 8.63632e-06 | 1(Win) | true |
| simdjson (ondemand) | 2098.15 | 0.114676 | 1371.78ms | 11579 | 2560 | 93250.4 | 5263.01 | 0.026036 | 2.42723 | 11.9661 | 1.92305 | 0.000498647 | 2.54367e-05 | 5.63385e-06 | 2(Loss) | true |
| Jsonifier | 1965.23 | 0.0615145 | 1393.86ms | 11579 | 4890 | 58422.5 | 5618.99 | 0.0204094 | 2.5986 | 11.9049 | 2.60938 | 0.00494838 | 2.76751e-05 | 6.97617e-06 | 3(Loss) | true |
| Glaze | 1662.21 | 0.0753232 | 1497.86ms | 11579 | 2560 | 64101.3 | 6643.31 | 0.0568093 | 3.05867 | 13.2138 | 2.4908 | 0.0039414 | 3.7008e-05 | 1.21111e-05 | 4(Loss) | true |
