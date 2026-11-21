
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2014.28 | 0.31885 | 235.1ms | 4857 | 2560 | 137629 | 2299.58 | 0.037861 | 1.21352 | 1(Win) | true |
| Jsonifier (two-stage) | 1789.37 | 0.0873134 | 264.886ms | 4857 | 40 | 204.343 | 2588.62 | 0.0267266 | 1.36956 | 2(Loss) | true |
| Glaze | 1622.6 | 0.0927939 | 289.848ms | 4857 | 80 | 561.361 | 2854.68 | 0.381247 | 1.51111 | 3(Loss) | true |
| simdjson (ondemand) | 823.596 | 0.0604667 | 573.342ms | 4857 | 80 | 925.19 | 5624.11 | 0.0899332 | 2.99244 | 4(Loss) | true |
