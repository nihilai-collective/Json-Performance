
----
### Marine IK Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3372.61 | 0.111312 | 598.725ms | 18245 | 4890 | 161268 | 5159.15 | 0.165885 | 0.730169 | 1(Win) | true |
| Jsonifier | 2850.79 | 0.116815 | 698.284ms | 18245 | 4890 | 248578 | 6103.5 | 0.273014 | 0.864844 | 2(Loss) | true |
| simdjson (reflection) | 2614.51 | 0.1 | 744.093ms | 18245 | 4890 | 216580 | 6655.09 | 0.285784 | 0.943262 | 3(Loss) | true |
| simdjson (ondemand) | 2073.87 | 0.12965 | 942.41ms | 18245 | 40 | 4732.95 | 8390.02 | 0.0261291 | 1.19012 | 4(Loss) | true |
| Glaze | 1981.19 | 0.0787139 | 938.627ms | 18245 | 30 | 1433.71 | 8782.5 | 0.252893 | 1.24568 | 5(Loss) | true |
