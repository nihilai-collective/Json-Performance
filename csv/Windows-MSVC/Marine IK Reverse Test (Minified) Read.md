
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 650.083 | 0.391932 | 8568.03ms | 1834197 | 80 | 8.89747e+09 | 2.69078e+06 | 0.162811 | 3.80826 | 1(Win) | true |
| Jsonifier (two-stage) | 578.02 | 0.445587 | 9521.22ms | 1834197 | 160 | 2.90932e+10 | 3.02624e+06 | 2.47935 | 4.28299 | 2(Loss) | true |
| Glaze | 193.815 | 0.494925 | 6399.92ms | 1834197 | 30 | 5.98571e+10 | 9.02522e+06 | 1.09784 | 12.7733 | 3(Loss) | true |
| simdjson (ondemand) | 127.282 | 0.439616 | 9618.91ms | 1834197 | 30 | 1.09504e+11 | 1.3743e+07 | 2.14685 | 19.451 | 4(Loss) | true |
