
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1558.71 | 0.408539 | 6953.98ms | 7351818 | 40 | 1.35078e+10 | 4.49809e+06 | 1.65861 | 1(Win) | true |
| simdjson (ondemand) | 1508.52 | 0.341793 | 6958.46ms | 7351818 | 30 | 7.5707e+09 | 4.64777e+06 | 0.126707 | 2(Loss) | true |
