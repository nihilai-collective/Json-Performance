
----
### Canada Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 723.165 | 1.24501 | 9157.18ms | 2251027 | 30 | 4.09782e+10 | 2.96854e+06 | 0.226098 | 4.20261 | 1(Win) | true |
| Jsonifier (two-stage) | 689.124 | 0.396125 | 9665.54ms | 2251027 | 160 | 2.43642e+10 | 3.11518e+06 | 0.542787 | 4.40997 | 2(Loss) | true |
| simdjson (ondemand) | 432.372 | 0.305391 | 7473.11ms | 2251027 | 80 | 1.83929e+10 | 4.96505e+06 | 0.0195076 | 7.02904 | 3(Loss) | true |
| Glaze | 408.983 | 0.415789 | 7894.75ms | 2251027 | 80 | 3.81055e+10 | 5.24899e+06 | 0.193936 | 7.4313 | 4(Loss) | true |
