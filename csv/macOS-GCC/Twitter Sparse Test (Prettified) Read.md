
----
### Twitter Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4814.03 | 0.299432 | 7140.37ms | 360584 | 1280 | 5.85601e+07 | 71432.8 | 0.0436965 | 1(Win) | true |
| simdjson (ondemand) | 4164.41 | 0.0834189 | 8316.56ms | 360584 | 4890 | 2.3203e+07 | 82575.9 | 0.0699421 | 2(Loss) | true |
