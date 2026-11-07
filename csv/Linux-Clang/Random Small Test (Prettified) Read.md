
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2517.3 | 0.102594 | 308.8ms | 8051 | 40 | 391.682 | 3050.1 | 0.0054646 | 0.975515 | 1(Win) | true |
| Jsonifier | 2004.99 | 0.06652 | 389.34ms | 8051 | 30 | 194.671 | 3829.47 | 0.476463 | 1.22694 | 2(Loss) | true |
| Glaze | 1728.25 | 0.127117 | 450.42ms | 8051 | 30 | 956.782 | 4442.67 | 0.0593089 | 1.42351 | 3(Loss) | true |
| simdjson (ondemand) | 1322.45 | 0.112833 | 582.904ms | 8051 | 4890 | 209857 | 5805.9 | 0.0292505 | 1.86341 | 4(Loss) | true |
