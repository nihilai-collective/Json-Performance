
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1037 | 0.605233 | 6050.01ms | 124597 | 320 | 1.53905e+08 | 114585 | 0.702204 | 2.93033 | 1(Win) | true |
| simdjson (ondemand) | 960.056 | 0.484834 | 6481.86ms | 124597 | 80 | 2.8807e+07 | 123769 | 0.402563 | 3.16522 | 2(Loss) | true |
