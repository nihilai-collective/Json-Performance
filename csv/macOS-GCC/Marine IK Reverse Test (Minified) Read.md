
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 634.39 | 0.418803 | 8705.16ms | 1834197 | 80 | 1.06682e+10 | 2.75734e+06 | 0.0392416 | 1(Win) | true |
| Jsonifier (two-stage) | 503.168 | 0.737205 | 5455.79ms | 1834197 | 30 | 1.97045e+10 | 3.47643e+06 | 1.08079 | 2(Loss) | true |
| simdjson (reflection) | 487.825 | 0.0824801 | 5415.15ms | 1834197 | 30 | 2.62412e+08 | 3.58577e+06 | 0.669442 | 3(Loss) | true |
| Glaze | 482.007 | 0.295616 | 5448.45ms | 1834197 | 40 | 4.60365e+09 | 3.62905e+06 | 0.0528197 | 4(Loss) | true |
| simdjson (ondemand) | 386.64 | 1.99708 | 6460.46ms | 1834197 | 30 | 2.44902e+11 | 4.52417e+06 | 0.195589 | 5(Loss) | true |
