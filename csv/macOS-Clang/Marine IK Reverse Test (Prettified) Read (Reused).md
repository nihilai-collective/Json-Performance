
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2311.38 | 0.39264 | 5172.58ms | 7351818 | 40 | 5.67407e+09 | 3.03335e+06 | 0.164798 | 1(Win) | true |
| Jsonifier (two-stage) | 2124.31 | 0.48106 | 5641.89ms | 7351818 | 30 | 7.5626e+09 | 3.30047e+06 | 1.28999 | 2(Loss) | true |
| Glaze | 1594.34 | 0.119448 | 7215.75ms | 7351818 | 80 | 2.20737e+09 | 4.39759e+06 | 1.30635 | 3(Loss) | true |
| simdjson (ondemand) | 1536.81 | 0.188549 | 7502.1ms | 7351818 | 30 | 2.21982e+09 | 4.5622e+06 | 0.0856183 | 4(Loss) | true |
