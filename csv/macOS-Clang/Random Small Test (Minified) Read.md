
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1314.63 | 0.354595 | 401.659ms | 5094 | 80 | 13736.1 | 3695.34 | 3.89114 | 1(Win) | true |
| Jsonifier (two-stage) | 1030.44 | 0.265561 | 530.148ms | 5094 | 40 | 6269.95 | 4714.52 | 0.192825 | 2(Loss) | true |
| Glaze | 921.654 | 0.213448 | 589.742ms | 5094 | 40 | 5063.2 | 5270.98 | 0.101554 | 3(Loss) | true |
| simdjson (ondemand) | 522.706 | 0.956326 | 960.786ms | 5094 | 160 | 1.26396e+06 | 9293.98 | 2.47788 | 4(Loss) | true |
