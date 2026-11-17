
----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10244.4 | 2.0044 | 39.029ms | 3643 | 4890 | 225955 | 339.135 | 0.98261 | 1(Win) | true |
| Glaze | 4039.38 | 0.816516 | 95.9519ms | 3682 | 2560 | 128976 | 869.3 | 0.334718 | 2(Loss) | true |
| simdjson (reflection) | 301.598 | 0.245952 | 1114.69ms | 3643 | 4890 | 3.92528e+06 | 11519.4 | 1.99596 | 3(Loss) | true |
