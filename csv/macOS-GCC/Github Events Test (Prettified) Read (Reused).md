
----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1621.82 | 0.210531 | 4308.02ms | 65103 | 640 | 4.15727e+06 | 38282.4 | 0.180041 | 1(Win) | true |
| simdjson (ondemand) | 1199.11 | 0.0868058 | 5807.43ms | 65103 | 1280 | 2.5858e+06 | 51777.8 | 0.0312778 | 2(Loss) | true |
