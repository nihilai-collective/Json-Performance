
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1519.33 | 0.227109 | 7048.58ms | 7351818 | 40 | 4.39354e+09 | 4.6147e+06 | 0.188173 | 1(Win) | true |
| simdjson (ondemand) | 1467.46 | 0.165367 | 7293.3ms | 7351818 | 30 | 1.87274e+09 | 4.77781e+06 | 0.0917437 | 2(Loss) | true |
