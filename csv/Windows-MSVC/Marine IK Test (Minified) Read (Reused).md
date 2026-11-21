
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 756.278 | 0.163613 | 8409.06ms | 1834197 | 40 | 5.72832e+08 | 2.31294e+06 | 0.361323 | 3.27364 | 1(Win) | true |
| Jsonifier (two-stage) | 645.338 | 1.04564 | 9321.06ms | 1834197 | 160 | 1.28529e+11 | 2.71056e+06 | 0.413031 | 3.83636 | 2(Loss) | true |
| simdjson (ondemand) | 226.999 | 0.230883 | 5844.81ms | 1834197 | 30 | 9.49621e+09 | 7.70589e+06 | 1.25827 | 10.9064 | 3(Loss) | true |
| Glaze | 206.907 | 0.532597 | 6270.71ms | 1834197 | 30 | 6.08221e+10 | 8.45418e+06 | 0.715741 | 11.9659 | 4(Loss) | true |
