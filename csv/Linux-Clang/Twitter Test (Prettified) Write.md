
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18169.7 | 0.174686 | 4530.02ms | 716365 | 2560 | 1.1044e+07 | 37599.8 | 0.238727 | 0.277778 | 1.02706 | 0.178553 | 0.000210653 | 0.00400607 | 1.60756e-05 | 1(Win) | true |
| Glaze | 4706.29 | 0.104761 | 7856.94ms | 716365 | 2560 | 5.92041e+07 | 145163 | 0.18875 | 1.06905 | 2.81727 | 0.463483 | 0.000592644 | 0.047295 | 6.6903e-05 | 2(Loss) | true |
