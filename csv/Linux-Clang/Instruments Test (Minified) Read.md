
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2663.63 | 0.174645 | 3875.75ms | 108313 | 1280 | 5.87133e+06 | 38779.9 | 0.279256 | 0.928818 | 1(Win) | true |
| Jsonifier (two-stage) | 2264.92 | 0.581758 | 4651.29ms | 108313 | 80 | 5.63157e+06 | 45606.6 | 0.235648 | 1.09239 | 2(Loss) | true |
| Glaze | 1599.31 | 0.0882751 | 6460.72ms | 108313 | 1280 | 4.16087e+06 | 64587.5 | 0.033344 | 1.54737 | 3(Loss) | true |
| simdjson (ondemand) | 661.684 | 0.728317 | 8062.75ms | 108313 | 30 | 3.87812e+07 | 156110 | 0.338554 | 3.74105 | 4(Loss) | true |
