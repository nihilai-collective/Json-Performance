
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 617.042 | 0.355297 | 8796.87ms | 1834197 | 160 | 1.62317e+10 | 2.83486e+06 | 0.190716 | 4.92534 | 1(Win) | true |
| Jsonifier (two-stage) | 559.298 | 0.351622 | 9716.37ms | 1834197 | 160 | 1.93498e+10 | 3.12754e+06 | 0.0772575 | 5.43365 | 2(Loss) | true |
| simdjson (ondemand) | 302.089 | 0.42629 | 8669.06ms | 1834197 | 80 | 4.87442e+10 | 5.79043e+06 | 0.250413 | 10.0609 | 3(Loss) | true |
| Glaze | 295.147 | 0.378176 | 8882.52ms | 1834197 | 80 | 4.01877e+10 | 5.92662e+06 | 0.480167 | 10.2976 | 4(Loss) | true |
