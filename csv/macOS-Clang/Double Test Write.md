
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 243.97 | 1.52681 | 675.832ms | 1811 | 80 | 934591 | 7079.16 | 0.205639 | 1(Win) | true |
| Glaze | 202.757 | 0.263921 | 913.102ms | 1798 | 640 | 318829 | 8456.96 | 0.403963 | 2(Loss) | true |
