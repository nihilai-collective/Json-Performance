
----
### Minify Test Write Results [(View the data used in the following test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Minify%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2602.93 | 0.65557 | 9537.16ms | 466906 | 80 | 1.00615e+08 | 171067 | 0.319631 | 1(Win) | true |
| Glaze | 1659.53 | 0.341576 | 7093.86ms | 466906 | 30 | 2.51992e+07 | 268315 | 0.153538 | 2(Loss) | true |
| simdjson (ondemand) | 1199.29 | 0.661171 | 5274.13ms | 466906 | 40 | 2.41047e+08 | 371284 | 0.00455829 | 3(Loss) | true |
