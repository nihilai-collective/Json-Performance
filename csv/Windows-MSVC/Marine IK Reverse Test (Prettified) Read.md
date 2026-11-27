
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) DID NOT CONVERGE | 1992.34 | 1.3097 | 5318.14ms | 7351818 | 40 | 8.497e+10 | 3.5191e+06 | 6.41833 | 1.52528 | -(Win) | false |
| Jsonifier DID NOT CONVERGE | 1868.58 | 1.50687 | 5388.35ms | 7351818 | 40 | 1.27873e+11 | 3.75217e+06 | 3.29945 | 1.62644 | -(Loss) | false |
| Glaze | 1107.59 | 0.308788 | 9582.15ms | 7351818 | 80 | 3.05664e+10 | 6.33019e+06 | 0.7101 | 2.7441 | 3(Loss) | true |
| simdjson (ondemand) | 681.193 | 0.733406 | 7246.11ms | 7351818 | 30 | 1.70946e+11 | 1.02926e+07 | 1.12292 | 4.46178 | 4(Loss) | true |
