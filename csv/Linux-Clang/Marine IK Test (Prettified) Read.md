
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2542.53 | 0.150221 | 8773.51ms | 7351818 | 40 | 6.86401e+08 | 2.75758e+06 | 0.383528 | 1.97391 | 8.70937 | 1.66341 | 0.00991554 | 0.0609903 | 0.00292447 | 1(Win) | true |
| Jsonifier | 2486.88 | 0.095911 | 8781.7ms | 7351818 | 80 | 5.84936e+08 | 2.8193e+06 | 0.0379826 | 2.01487 | 9.47474 | 2.25109 | 0.0069067 | 0.0339058 | 0.00179411 | 2(Loss) | true |
| simdjson (ondemand) | 2098.33 | 0.150814 | 5032.58ms | 7351818 | 80 | 2.03148e+09 | 3.34134e+06 | 0.230707 | 2.39022 | 10.1985 | 1.61033 | 0.0111461 | 0.0610155 | 0.00444872 | 3(Loss) | true |
| Glaze | 2088.81 | 0.162357 | 5122.65ms | 7351818 | 30 | 8.90954e+08 | 3.35656e+06 | 0.640193 | 2.40714 | 11.0264 | 2.24172 | 0.00924686 | 0.0333502 | 0.00135087 | 4(Loss) | true |
