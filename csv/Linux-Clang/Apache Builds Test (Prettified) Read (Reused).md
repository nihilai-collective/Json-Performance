
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2597.09 | 0.13838 | 5805.03ms | 124597 | 1280 | 5.13095e+06 | 45753.1 | 0.276148 | 0.952716 | 1(Win) | true |
| Jsonifier | 2347.53 | 0.252315 | 6391.36ms | 124597 | 80 | 1.30488e+06 | 50617 | 0.316993 | 1.0541 | 2(Loss) | true |
| Glaze | 2077.78 | 0.18012 | 6862.6ms | 124597 | 640 | 6.79079e+06 | 57188.4 | 0.222716 | 1.191 | 3(Loss) | true |
| simdjson (ondemand) | 1854.47 | 0.110551 | 7872.94ms | 124597 | 640 | 3.21127e+06 | 64074.9 | 0.624532 | 1.33448 | 4(Loss) | true |
