
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3092.52 | 0.128238 | 7769.75ms | 7351818 | 40 | 3.38111e+08 | 2.26716e+06 | 0.0696083 | 0.800568 | 1(Win) | true |
| Jsonifier | 2916.18 | 0.0958362 | 8326.81ms | 7351818 | 40 | 2.12363e+08 | 2.40425e+06 | 0.122165 | 0.848975 | 2(Loss) | true |
| simdjson (ondemand) | 2445.45 | 0.0319982 | 9718.73ms | 7351818 | 80 | 6.73305e+07 | 2.86705e+06 | 0.902023 | 1.0124 | 3(Loss) | true |
| Glaze | 2320.54 | 0.0879482 | 5186.15ms | 7351818 | 40 | 2.82439e+08 | 3.02138e+06 | 0.0631618 | 1.0669 | 4(Loss) | true |
