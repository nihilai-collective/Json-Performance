
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1052.61 | 0.0796462 | 10061.1ms | 7351818 | 40 | 1.12576e+09 | 6.66083e+06 | 0.0408328 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 598.463 | 0.891703 | 8020.76ms | 7351818 | 30 | 3.27398e+11 | 1.17154e+07 | 6.16762 | -(Loss) | false |
