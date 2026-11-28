
----
### Minify Test Write Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 6940.37 | 0.413985 | 6336.73ms | 466906 | 320 | 2.25742e+07 | 64157.4 | 0.969163 | 1(Win) | true |
| Jsonifier | 6561.44 | 0.410321 | 7391.86ms | 466906 | 640 | 4.96236e+07 | 67862.6 | 0.380784 | 2(Loss) | true |
| Glaze | 1594.79 | 0.346464 | 7916.41ms | 466906 | 160 | 1.49723e+08 | 279207 | 0.242347 | 3(Loss) | true |
