
----
### Stream Formats Small Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Stream%20Formats%20Small%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3307.64 | 0.233523 | 6964.31ms | 16002591 | 40 | 4.64368e+09 | 4.61394e+06 | 0.417625 | 0.748461 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 2015.59 | 0.424934 | 5512.12ms | 16002591 | 40 | 4.14073e+10 | 7.5716e+06 | 13.1089 | 1.2283 | -(Loss) | false |
