
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2336.03 | 0.0483886 | 5514.13ms | 94653 | 30 | 10488.6 | 38641.7 | 0.0897073 | 1(Win) | true |
| Jsonifier (two-stage) | 1471.34 | 0.0713407 | 7984.55ms | 94653 | 4890 | 9.36761e+06 | 61351.2 | 0.184997 | 2(Loss) | true |
| Glaze | 1461.53 | 0.0958948 | 7625.65ms | 94653 | 2560 | 8.98014e+06 | 61762.7 | 0.0199018 | 3(Loss) | true |
| simdjson (ondemand) | 1065.56 | 0.29396 | 5228.88ms | 94653 | 30 | 1.8604e+06 | 84713.9 | 0.0180182 | 4(Loss) | true |
