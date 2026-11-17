
----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 593.468 | 0.0309072 | 1470.6ms | 4669 | 1280 | 6883.09 | 7502.86 | 0.0246113 | 8.72402 | 38.6929 | 7.67959 | 0.0092654 | 3.81506e-05 | 2.34258e-06 | 1(Win) | true |
| simdjson (ondemand) | 244.425 | 0.0314529 | 2556.1ms | 4669 | 2560 | 84046.3 | 18217.1 | 0.301549 | 21.0934 | 104.744 | 18.9595 | 0.0354785 | 5.26244e-05 | 9.37031e-06 | 2(Loss) | true |
