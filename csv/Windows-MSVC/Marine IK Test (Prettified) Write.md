
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2477.25 | 0.43325 | 5669.48ms | 9930848 | 40 | 1.09741e+10 | 3.82311e+06 | 1.85926 | 0.999385 | 1(Win) | true |
| Glaze | 1233.78 | 1.32934 | 5310.72ms | 9930228 | 30 | 3.12344e+11 | 7.67574e+06 | 0.655718 | 2.00659 | 2(Loss) | true |
