
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3237.89 | 0.0573271 | 5703.26ms | 183677 | 4890 | 4.70342e+06 | 54099.4 | 0.000238611 | 1(Win) | true |
| Jsonifier (two-stage) | 2792.18 | 0.0949536 | 6664.2ms | 183677 | 640 | 2.27104e+06 | 62735.2 | 0.656232 | 2(Loss) | true |
| Glaze | 2078.74 | 0.109936 | 8780.09ms | 183677 | 640 | 5.49246e+06 | 84266.3 | 0.10722 | 3(Loss) | true |
| simdjson (ondemand) | 1179.7 | 0.216281 | 7840.36ms | 183677 | 40 | 4.12538e+06 | 148485 | 0.0426205 | 4(Loss) | true |
