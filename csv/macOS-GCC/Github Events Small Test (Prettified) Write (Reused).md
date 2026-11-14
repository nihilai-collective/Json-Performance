
----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16163.8 | 3.18248 | 19.55ms | 2866 | 4890 | 141615 | 169.096 | 1.51653 | 1(Win) | true |
| Glaze | 3255.4 | 1.24508 | 86.8009ms | 2866 | 1280 | 139879 | 839.6 | 0.709555 | 2(Loss) | true |
| simdjson (reflection) | 382.934 | 0.183258 | 725.423ms | 2866 | 1280 | 218997 | 7137.6 | 0.123443 | 3(Loss) | true |
