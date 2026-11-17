
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 994.909 | 0.194189 | 8010.5ms | 2251027 | 30 | 5.26705e+08 | 2.15773e+06 | 0.0794211 | 2.48847 | 1(Win) | true |
| Glaze | 915.244 | 0.154725 | 8587.88ms | 2251027 | 30 | 3.95122e+08 | 2.34555e+06 | 0.162601 | 2.70507 | 2(Loss) | true |
| Jsonifier (two-stage) | 878.61 | 0.152255 | 8755.03ms | 2251027 | 40 | 5.53569e+08 | 2.44334e+06 | 0.00248675 | 2.81786 | 3(Loss) | true |
| simdjson (ondemand) | 812.135 | 0.304592 | 9418.7ms | 2251027 | 160 | 1.0372e+10 | 2.64334e+06 | 0.232464 | 3.04852 | 4(Loss) | true |
| simdjson (reflection) | 782.443 | 0.122899 | 9698.48ms | 2251027 | 80 | 9.09579e+08 | 2.74365e+06 | 0.229927 | 3.1642 | 5(Loss) | true |
