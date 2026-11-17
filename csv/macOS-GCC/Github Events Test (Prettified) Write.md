
----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14555.3 | 1.23515 | 531.486ms | 78778 | 160 | 650321 | 5161.6 | 0 | 1(Win) | true |
| Glaze | 3125.1 | 0.205947 | 2606.39ms | 78778 | 4890 | 1.19868e+07 | 24040.4 | 0.214221 | 2(Loss) | true |
| simdjson (reflection) | 383.257 | 0.462386 | 5183.21ms | 78778 | 640 | 5.25798e+08 | 196026 | 0.295411 | 3(Loss) | true |
