
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2469.8 | 0.116227 | 9700.68ms | 7351818 | 160 | 1.74183e+09 | 2.83879e+06 | 0.162407 | 1.00242 | 1(Win) | true |
| simdjson (ondemand) | 2405.4 | 0.232636 | 10224.8ms | 7351818 | 80 | 3.67841e+09 | 2.91479e+06 | 0.631914 | 1.02925 | 2(Loss) | true |
