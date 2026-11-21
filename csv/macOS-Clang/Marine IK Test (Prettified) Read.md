
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2107.34 | 0.296335 | 5209.15ms | 7351818 | 40 | 3.8882e+09 | 3.32706e+06 | 2.91794 | 1(Win) | true |
| Jsonifier (two-stage) | 1666.65 | 0.728825 | 6249.47ms | 7351818 | 30 | 2.82014e+10 | 4.2068e+06 | 0.359659 | 2(Loss) | true |
| Glaze | 1415 | 0.89627 | 7529.62ms | 7351818 | 30 | 5.91662e+10 | 4.95493e+06 | 0.2135 | 3(Loss) | true |
| simdjson (ondemand) | 1226.95 | 0.879947 | 8218.16ms | 7351818 | 40 | 1.01137e+11 | 5.71438e+06 | 0.537914 | 4(Loss) | true |
