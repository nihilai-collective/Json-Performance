
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2713.68 | 0.0566221 | 5289.66ms | 9930848 | 80 | 3.12405e+08 | 3.49002e+06 | 0.547449 | 0.91232 | 1(Win) | true |
| Glaze | 1326.1 | 0.0432954 | 5053.23ms | 9930228 | 40 | 3.82393e+08 | 7.1414e+06 | 0.710738 | 1.86694 | 2(Loss) | true |
