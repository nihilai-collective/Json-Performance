
----
### Google Maps Response Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 786.513 | 0.0643392 | 2186.66ms | 11812 | 2560 | 217384 | 14322.5 | 0.113899 | 6.50361 | 29.365 | 5.95992 | 0.0147266 | 7.01088e-05 | 4.02133e-05 | 1(Win) | true |
| simdjson (ondemand) | 686.704 | 0.117081 | 2380.27ms | 11812 | 160 | 59020.4 | 16404.2 | 0.05746 | 7.38418 | 33.0921 | 6.09948 | 0.0133662 | 6.98442e-05 | 3.33347e-05 | 2(Loss) | true |
