
----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11593.9 | 2.21749 | 32.716ms | 3643 | 4890 | 215921 | 299.661 | 2.29496 | 1(Win) | true |
| Glaze | 4610.52 | 0.821926 | 80.6602ms | 3682 | 4890 | 191621 | 761.613 | 0.207929 | 2(Loss) | true |
| simdjson (reflection) | 374.5 | 0.184904 | 949.487ms | 3643 | 1280 | 376631 | 9277 | 0.139935 | 3(Loss) | true |
