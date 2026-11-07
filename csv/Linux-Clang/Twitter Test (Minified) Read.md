
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1784.83 | 0.0603119 | 6364.93ms | 466906 | 1280 | 2.89787e+07 | 249478 | 0.0791757 | 1.38687 | 1(Win) | true |
| Jsonifier | 1777.9 | 0.0615365 | 6463.56ms | 466906 | 1280 | 3.04032e+07 | 250451 | 0.127796 | 1.39231 | 2(Loss) | true |
| Glaze | 1729.18 | 0.0841798 | 6607.43ms | 466906 | 640 | 3.0073e+07 | 257508 | 0.130653 | 1.43159 | 3(Loss) | true |
| simdjson (ondemand) | 938.849 | 0.134776 | 6032.99ms | 466906 | 80 | 3.26877e+07 | 474279 | 0.0887 | 2.63683 | 4(Loss) | true |
