
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 764.212 | 0.0306912 | 1305.39ms | 4630 | 4890 | 15377 | 5777.86 | 0.241235 | 6.72212 | 31.9933 | 6.25465 | 0.00275451 | 0.000115367 | 5.1986e-05 | 1(Win) | true |
| simdjson (ondemand) | 759.67 | 0.065059 | 1297.01ms | 4630 | 640 | 9151.8 | 5812.41 | 0.0789979 | 6.76536 | 32.3782 | 5.6784 | 0.00320161 | 0.000127565 | 4.72462e-05 | 2(Loss) | true |
