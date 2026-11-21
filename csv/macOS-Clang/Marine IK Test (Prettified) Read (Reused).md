
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2062.57 | 0.401659 | 5619.8ms | 7351818 | 80 | 1.49135e+10 | 3.39928e+06 | 0.716863 | 1(Win) | true |
| Jsonifier (two-stage) | 1933.46 | 0.844624 | 6022.9ms | 7351818 | 30 | 2.81427e+10 | 3.62626e+06 | 1.10923 | 2(Loss) | true |
| Glaze | 1527.93 | 0.820209 | 7476.68ms | 7351818 | 30 | 4.24967e+10 | 4.58873e+06 | 1.36441 | 3(Loss) | true |
| simdjson (ondemand) | 1398.62 | 0.439147 | 8347.87ms | 7351818 | 40 | 1.93851e+10 | 5.01296e+06 | 3.13936 | 4(Loss) | true |
