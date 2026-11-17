
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1335.19 | 0.700163 | 8166.91ms | 7351818 | 40 | 5.40707e+10 | 5.25112e+06 | 2.9227 | 1(Win) | true |
| simdjson (ondemand) | 1279.2 | 0.942777 | 8317.11ms | 7351818 | 80 | 2.1361e+11 | 5.48096e+06 | 3.20111 | 2(Loss) | true |
