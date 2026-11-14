
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2545.9 | 0.0700552 | 278.371ms | 6701 | 160 | 494.761 | 2510.14 | 0.0945269 | 1(Win) | true |
| Jsonifier (two-stage) | 2153.44 | 0.0883475 | 354.595ms | 6701 | 4890 | 33613.2 | 2967.61 | 0.0964324 | 2(Loss) | true |
| Glaze | 2120.25 | 0.124664 | 322.19ms | 6701 | 2560 | 36143.4 | 3014.06 | 0.472203 | 3(Loss) | true |
| simdjson (ondemand) | 987.195 | 0.139914 | 669.432ms | 6701 | 30 | 2461.02 | 6473.47 | 0.046836 | 4(Loss) | true |
