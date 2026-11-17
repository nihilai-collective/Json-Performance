
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 2390.84 | 0.486995 | 845.902ms | 2889 | 640 | 20156.9 | 1152.39 | 0.110382 | 2.22821 | 8.75597 | 1.50294 | 0.000702557 | 1.94704e-05 | 1.08169e-06 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2374.21 | 0.280051 | 844.283ms | 2889 | 4890 | 51646.5 | 1160.46 | 0.0816445 | 2.22777 | 6.70682 | 1.13361 | 0.00141082 | 5.21688e-05 | 1.38032e-05 | 1(Tie) | true |
| Jsonifier (two-stage) | 2152.15 | 0.253191 | 859.035ms | 2889 | 4890 | 51375.3 | 1280.19 | 0.0453548 | 2.43443 | 8.06127 | 1.25961 | 0.000707217 | 7.80055e-05 | 2.6049e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1005.2 | 0.113681 | 1009.59ms | 2889 | 4890 | 47476.3 | 2740.92 | 0.232927 | 5.15355 | 16.9031 | 2.86812 | 0.000367447 | 0.000163656 | 9.09592e-05 | 4(Loss) | true |
