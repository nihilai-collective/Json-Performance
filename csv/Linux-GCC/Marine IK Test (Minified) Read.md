
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 732.795 | 0.0750259 | 7450.01ms | 1834197 | 160 | 5.13179e+08 | 2.38706e+06 | 0.124379 | 3.37853 | 1(Win) | true |
| simdjson (ondemand) | 621.257 | 0.137002 | 8778.14ms | 1834197 | 160 | 2.38081e+09 | 2.81563e+06 | 0.32553 | 3.98509 | 2(Loss) | true |
