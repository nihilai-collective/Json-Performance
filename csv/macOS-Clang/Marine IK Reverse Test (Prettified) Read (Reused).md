
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2235.11 | 0.10096 | 5328.44ms | 7351818 | 30 | 3.00896e+08 | 3.13687e+06 | 0.110719 | 1(Win) | true |
| Jsonifier (two-stage) | 2187.54 | 0.0544466 | 6058.86ms | 7351818 | 30 | 9.13563e+07 | 3.20507e+06 | 0.42696 | 2(Loss) | true |
| Glaze | 1538.57 | 0.763362 | 7228ms | 7351818 | 30 | 3.63027e+10 | 4.55699e+06 | 2.03121 | 3(Loss) | true |
| simdjson (ondemand) | 1436.93 | 1.61193 | 8507.89ms | 7351818 | 40 | 2.47441e+11 | 4.87933e+06 | 2.80295 | 4(Loss) | true |
