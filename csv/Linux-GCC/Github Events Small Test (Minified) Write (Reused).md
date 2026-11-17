
----
### Github Events Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14414.4 | 0.0734141 | 15.994ms | 1996 | 2560 | 24.0619 | 132.058 | 0.173332 | 0.133194 | 1(Win) | true |
| simdjson (reflection) | 11953.1 | 0.312964 | 18.464ms | 1996 | 40 | 9.9359 | 159.25 | 0.031407 | 0.168687 | 2(Loss) | true |
| Glaze | 6038.5 | 0.0719778 | 34.4898ms | 1996 | 640 | 32.9488 | 315.233 | 0.0133848 | 0.372008 | 3(Loss) | true |
