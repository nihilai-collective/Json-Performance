
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1533.68 | 1.39422 | 389.223ms | 5094 | 2560 | 4.99291e+06 | 3167.56 | 2.59227 | 1(Win) | true |
| Jsonifier (two-stage) | 1286.57 | 1.38013 | 508.757ms | 5094 | 40 | 108631 | 3775.95 | 1.17856 | 2(Loss) | true |
| Glaze | 1127.32 | 0.129672 | 593.83ms | 5094 | 80 | 2498.11 | 4309.36 | 0.118496 | 3(Loss) | true |
| simdjson (ondemand) | 631.423 | 0.273375 | 801.476ms | 5094 | 2560 | 1.13249e+06 | 7693.76 | 1.08034 | 4(Loss) | true |
