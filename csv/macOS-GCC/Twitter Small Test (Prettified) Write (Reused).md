
----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 16408 | 2.48589 | 28.4621ms | 4300 | 4890 | 188756 | 249.927 | 1.47267 | 1(Win) | true |
| Glaze | 3503.76 | 1.30003 | 118.886ms | 4300 | 640 | 148168 | 1170.4 | 1.17566 | 2(Loss) | true |
| simdjson (reflection) | 375.972 | 0.604507 | 1144.06ms | 4300 | 640 | 2.78233e+06 | 10907.2 | 1.02253 | 3(Loss) | true |
