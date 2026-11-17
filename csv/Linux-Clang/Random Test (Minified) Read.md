
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1164.75 | 0.289445 | 8506.97ms | 409725 | 80 | 7.54297e+07 | 335475 | 0.308084 | 2.12535 | 1(Win) | true |
| simdjson (ondemand) | 990.604 | 0.0947882 | 5028.15ms | 409725 | 320 | 4.47345e+07 | 394450 | 0.351372 | 2.49904 | 2(Loss) | true |
