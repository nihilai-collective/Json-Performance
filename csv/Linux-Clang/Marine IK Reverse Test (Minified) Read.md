
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 352.156 | 0.242515 | 7545.96ms | 1834197 | 30 | 4.35331e+09 | 4.96719e+06 | 0.0777112 | 7.03002 | 1(Win) | true |
| simdjson (ondemand) | 197.966 | 2.1576 | 6120.82ms | 1834197 | 40 | 1.45382e+12 | 8.83599e+06 | 0.240944 | 12.5059 | 2(Loss) | true |
