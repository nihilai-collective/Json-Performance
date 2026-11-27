
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2080.8 | 0.569882 | 5706.38ms | 7351818 | 40 | 1.47489e+10 | 3.3695e+06 | 1.28103 | 1(Win) | true |
| Jsonifier | 2051.38 | 0.433925 | 5719.53ms | 7351818 | 80 | 1.75961e+10 | 3.41781e+06 | 0.256177 | 2(Loss) | true |
| Glaze | 1501.86 | 0.414181 | 7550.82ms | 7351818 | 40 | 1.49545e+10 | 4.66838e+06 | 0.777244 | 3(Loss) | true |
| simdjson (ondemand) | 1476.28 | 0.193123 | 7763.92ms | 7351818 | 80 | 6.72995e+09 | 4.74926e+06 | 0.677549 | 4(Loss) | true |
