
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1954.66 | 0.222965 | 5382.04ms | 7351818 | 80 | 5.11695e+09 | 3.58694e+06 | 0.300634 | 1.55487 | 1(Win) | true |
| Jsonifier (two-stage) | 1933.16 | 0.49161 | 5395.17ms | 7351818 | 80 | 2.54323e+10 | 3.62683e+06 | 1.1117 | 1.57203 | 2(Loss) | true |
| simdjson (ondemand) | 1113.39 | 0.349351 | 9313.94ms | 7351818 | 80 | 3.87176e+10 | 6.2972e+06 | 0.311665 | 2.72958 | 3(Loss) | true |
| Glaze | 1036.68 | 0.281644 | 10157ms | 7351818 | 80 | 2.90263e+10 | 6.76318e+06 | 0.152824 | 2.93174 | 4(Loss) | true |
