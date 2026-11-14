
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 678.75 | 0.0971275 | 8711.34ms | 1834197 | 30 | 1.87966e+08 | 2.57713e+06 | 0.14965 | 3.64759 | 1(Win) | true |
| simdjson (ondemand) | 646.175 | 0.224146 | 9192.98ms | 1834197 | 30 | 1.10453e+09 | 2.70705e+06 | 0.544383 | 3.83144 | 2(Loss) | true |
