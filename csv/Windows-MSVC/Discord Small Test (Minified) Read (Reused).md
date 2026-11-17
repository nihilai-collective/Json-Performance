
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1550.17 | 0.0819243 | 351.416ms | 4857 | 4890 | 29303 | 2988.06 | 0.0474324 | 1.94775 | 1(Win) | true |
| Glaze | 1524.94 | 0.298821 | 352.769ms | 4857 | 320 | 26363.6 | 3037.5 | 0.123609 | 1.97908 | 2(Loss) | true |
| Jsonifier (two-stage) | 1080.7 | 0.100893 | 488.95ms | 4857 | 2560 | 47872.2 | 4286.09 | 0.187392 | 2.79736 | 3(Loss) | true |
| simdjson (ondemand) | 931.055 | 0.136159 | 545.448ms | 4857 | 80 | 3670.89 | 4975 | 0.250627 | 3.24719 | 4(Loss) | true |
