
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 452.792 | 0.144491 | 5777.18ms | 1834197 | 40 | 1.24635e+09 | 3.8632e+06 | 0.982965 | 1(Win) | true |
| Jsonifier (generic) | 349.597 | 1.38553 | 6653.81ms | 1834197 | 40 | 1.92242e+11 | 5.00355e+06 | 0.881536 | 2(Loss) | true |
