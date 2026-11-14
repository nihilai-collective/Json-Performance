
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2373.23 | 0.124031 | 10239.6ms | 7351818 | 160 | 2.14829e+09 | 2.95431e+06 | 0.10149 | 1(Win) | true |
| Jsonifier (two-stage) | 2251.73 | 0.205086 | 5836.03ms | 7351818 | 30 | 1.22335e+09 | 3.11371e+06 | 0.118556 | 2(Loss) | true |
| Glaze | 1662.68 | 0.280354 | 6917.61ms | 7351818 | 40 | 5.59047e+09 | 4.21684e+06 | 0.00961732 | 3(Loss) | true |
| simdjson (ondemand) | 1311.25 | 0.696182 | 8835.98ms | 7351818 | 80 | 1.10854e+11 | 5.34698e+06 | 0.0849155 | 4(Loss) | true |
