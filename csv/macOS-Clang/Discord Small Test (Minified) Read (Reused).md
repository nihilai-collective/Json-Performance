
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2503.89 | 0.244385 | 211.971ms | 4857 | 2560 | 52322.9 | 1849.92 | 0.957385 | 1(Win) | true |
| Jsonifier (two-stage) | 1705.85 | 0.105966 | 357.853ms | 4857 | 30 | 248.378 | 2715.37 | 0.30784 | 2(Loss) | true |
| Glaze | 1557.43 | 1.20907 | 307.644ms | 4857 | 1280 | 1.65512e+06 | 2974.13 | 1.90309 | 3(Loss) | true |
| simdjson (ondemand) | 685.927 | 0.464771 | 717.163ms | 4857 | 320 | 315216 | 6752.9 | 0.303161 | 4(Loss) | true |
