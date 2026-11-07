
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1655.46 | 0.754027 | 5279.62ms | 94653 | 80 | 1.35236e+07 | 54527.4 | 0.254602 | 1.4948 | 1(Win) | true |
| Jsonifier (two-stage) | 1555.19 | 0.0639252 | 5893.29ms | 94653 | 2560 | 3.52441e+06 | 58043.1 | 0.100208 | 1.59122 | 2(Loss) | true |
| Glaze | 1494.25 | 0.102527 | 6145.37ms | 94653 | 640 | 2.45515e+06 | 60410.4 | 0.0395008 | 1.65619 | 3(Loss) | true |
| simdjson (ondemand) | 1082.3 | 0.0533001 | 8241.11ms | 94653 | 2560 | 5.05911e+06 | 83404.4 | 0.0509971 | 2.2868 | 4(Loss) | true |
