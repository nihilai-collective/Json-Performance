
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2153.81 | 0.221229 | 10193.7ms | 7351818 | 160 | 8.29807e+09 | 3.25527e+06 | 0.0518275 | 1.14949 | 1(Win) | true |
| Jsonifier | 2106.11 | 0.433029 | 5167.37ms | 7351818 | 80 | 1.66246e+10 | 3.329e+06 | 0.139237 | 1.17544 | 2(Loss) | true |
| simdjson (ondemand) | 866.814 | 1.58545 | 5657.34ms | 7351818 | 40 | 6.5781e+11 | 8.08852e+06 | 2.28519 | 2.85623 | 3(Loss) | true |
| Glaze DID NOT CONVERGE | 679.785 | 0.57156 | 7152.1ms | 7351818 | 30 | 1.04254e+11 | 1.03139e+07 | 2.54958 | 3.64197 | -(Loss) | false |
