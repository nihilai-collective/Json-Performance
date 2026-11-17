
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 895.857 | 1.31374 | 5482.54ms | 7351818 | 40 | 4.22857e+11 | 7.8263e+06 | 0.0450608 | 2.76361 | 1(Win) | true |
| simdjson (ondemand) | 759.579 | 2.01169 | 6144.8ms | 7351818 | 30 | 1.03439e+12 | 9.23043e+06 | 0.798732 | 3.25938 | 2(Loss) | true |
