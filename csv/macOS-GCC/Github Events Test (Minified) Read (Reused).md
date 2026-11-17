
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1962.72 | 0.258638 | 3358.74ms | 53331 | 4890 | 2.19654e+07 | 25913.3 | 0.825932 | 1(Win) | true |
| Glaze | 1682.2 | 0.43603 | 3801.11ms | 53331 | 1280 | 2.22457e+07 | 30234.4 | 1.01751 | 2(Loss) | true |
| Jsonifier (two-stage) | 1556.14 | 0.243467 | 4123.38ms | 53331 | 4890 | 3.09636e+07 | 32683.7 | 3.14961 | 3(Loss) | true |
| simdjson (reflection) | 1241.98 | 0.231942 | 4827.61ms | 53331 | 4890 | 4.41163e+07 | 40951.1 | 2.03085 | 4(Loss) | true |
| simdjson (ondemand) | 1076.76 | 0.196049 | 5692.43ms | 53331 | 4890 | 4.19331e+07 | 47234.5 | 2.09135 | 5(Loss) | true |
