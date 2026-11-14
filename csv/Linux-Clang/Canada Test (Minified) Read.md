
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 729.254 | 0.0606667 | 8597.39ms | 2090234 | 80 | 2.2e+08 | 2.73348e+06 | 0.00785749 | 3.39496 | 1(Win) | true |
| simdjson (ondemand) | 662.154 | 0.0798531 | 9305.15ms | 2090234 | 80 | 4.62324e+08 | 3.01048e+06 | 0.0954974 | 3.73899 | 2(Loss) | true |
