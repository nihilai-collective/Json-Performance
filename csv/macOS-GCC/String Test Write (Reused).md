
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9345.5 | 0.895705 | 116.227ms | 9578 | 1280 | 98103.5 | 977.4 | 0.265306 | 1(Win) | true |
| simdjson (reflection) | 8570.55 | 0.529825 | 106.245ms | 9578 | 4890 | 155921 | 1065.78 | 1.41561 | 2(Loss) | true |
| Glaze | 4487.29 | 0.536903 | 223.174ms | 9578 | 4890 | 584094 | 2035.59 | 0.939577 | 3(Loss) | true |
