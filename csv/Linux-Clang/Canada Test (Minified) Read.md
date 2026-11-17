
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 707.88 | 0.119767 | 8783.93ms | 2090234 | 160 | 1.81997e+09 | 2.81602e+06 | 1.13457 | 3.49744 | 1(Win) | true |
| simdjson (ondemand) | 666.908 | 0.159263 | 9700.48ms | 2090234 | 30 | 6.79844e+08 | 2.98902e+06 | 0.639852 | 3.71238 | 2(Loss) | true |
