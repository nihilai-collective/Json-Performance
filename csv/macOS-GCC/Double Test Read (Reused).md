
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 426.403 | 0.414408 | 409.207ms | 1811 | 320 | 90157.6 | 4050.4 | 0.019755 | 1(Win) | true |
| simdjson (ondemand) | 204.828 | 0.191198 | 846.643ms | 1811 | 4890 | 1.27097e+06 | 8431.98 | 0.02039 | 2(Loss) | true |
