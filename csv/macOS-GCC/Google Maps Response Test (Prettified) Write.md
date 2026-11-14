
----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18379.7 | 0.455979 | 165.204ms | 31235 | 4890 | 267059 | 1620.71 | 0.765053 | 1(Win) | true |
| Glaze | 2720.27 | 1.12131 | 1106.76ms | 31235 | 80 | 1.20615e+06 | 10950.4 | 0 | 2(Loss) | true |
| simdjson (reflection) | 309.222 | 0.0952416 | 9653.57ms | 31235 | 1280 | 1.07747e+07 | 96332.2 | 0.269169 | 3(Loss) | true |
