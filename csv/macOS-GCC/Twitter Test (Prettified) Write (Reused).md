
----
### Twitter Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17835.7 | 0.190975 | 4073.85ms | 716365 | 40 | 214042 | 38304 | 0.0167112 | 1(Win) | true |
| Glaze | 4641.97 | 0.313321 | 7847.53ms | 716365 | 40 | 8.50556e+06 | 147174 | 0.375462 | 2(Loss) | true |
| simdjson (reflection) | 395.576 | 0.46777 | 5425.73ms | 716365 | 160 | 1.04422e+10 | 1.72705e+06 | 1.75214 | 3(Loss) | true |
