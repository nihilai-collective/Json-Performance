
----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10349.2 | 2.79128 | 36.3351ms | 3643 | 2560 | 224776 | 335.7 | 0.326603 | 1(Win) | true |
| Glaze | 3901.23 | 0.504741 | 92.6182ms | 3682 | 4890 | 100928 | 900.083 | 0.664007 | 2(Loss) | true |
| simdjson (reflection) | 369.497 | 0.149348 | 941.2ms | 3643 | 2560 | 504821 | 9402.6 | 0.253764 | 3(Loss) | true |
