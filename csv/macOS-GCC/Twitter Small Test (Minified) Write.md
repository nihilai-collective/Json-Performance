
----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12350.2 | 7.29987 | 26.4489ms | 2963 | 640 | 178534 | 228.8 | 2.14286 | 1(Win) | true |
| simdjson (reflection) | 9439.66 | 2.19738 | 35.158ms | 2963 | 4890 | 211578 | 299.347 | 4.66648 | 2(Loss) | true |
| Glaze | 3165.03 | 2.80802 | 91.2172ms | 2963 | 160 | 100561 | 892.8 | 0.722022 | 3(Loss) | true |
