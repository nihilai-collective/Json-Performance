
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2087.12 | 0.593772 | 5172.62ms | 7351818 | 80 | 3.1829e+10 | 3.35929e+06 | 0.00985984 | 1(Win) | true |
| Jsonifier (two-stage) | 1823.53 | 1.15523 | 5747.1ms | 7351818 | 40 | 7.89148e+10 | 3.84488e+06 | 1.4165 | 2(Loss) | true |
| Glaze | 1494.11 | 0.451092 | 7401.06ms | 7351818 | 30 | 1.34423e+10 | 4.69257e+06 | 0.354002 | 3(Loss) | true |
| simdjson (ondemand) | 1430.83 | 0.188365 | 7463.82ms | 7351818 | 80 | 6.81559e+09 | 4.90011e+06 | 0.252811 | 4(Loss) | true |
