
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 644.402 | 0.461318 | 8558.22ms | 1834197 | 160 | 2.50899e+10 | 2.7145e+06 | 0.389093 | 1(Win) | true |
| Jsonifier (two-stage) | 547.055 | 0.455805 | 10261.8ms | 1834197 | 80 | 1.69933e+10 | 3.19753e+06 | 0.175235 | 2(Loss) | true |
| Glaze | 470.39 | 0.0794318 | 5615.31ms | 1834197 | 40 | 3.48999e+08 | 3.71867e+06 | 0.0787012 | 3(Loss) | true |
| simdjson (ondemand) | 404.34 | 0.538531 | 6548.03ms | 1834197 | 80 | 4.34222e+10 | 4.32613e+06 | 0.551081 | 4(Loss) | true |
