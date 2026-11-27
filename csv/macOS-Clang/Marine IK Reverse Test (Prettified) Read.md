
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2002.47 | 0.275003 | 5242.5ms | 7351818 | 80 | 7.41686e+09 | 3.50129e+06 | 1.02911 | 1(Win) | true |
| Jsonifier (two-stage) | 1854.11 | 0.729861 | 5645.5ms | 7351818 | 40 | 3.0469e+10 | 3.78146e+06 | 1.41007 | 2(Loss) | true |
| Glaze DID NOT CONVERGE | 1272.56 | 0.68973 | 7722.83ms | 7351818 | 40 | 5.77636e+10 | 5.50958e+06 | 5.04919 | -(Loss) | false |
| simdjson (ondemand) | 1241.78 | 0.916254 | 8547.5ms | 7351818 | 30 | 8.0289e+10 | 5.64614e+06 | 0.73342 | 4(Loss) | true |
