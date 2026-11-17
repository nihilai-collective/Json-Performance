
----
### Canada Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 999.799 | 0.433038 | 7502.41ms | 5212421 | 80 | 3.70849e+10 | 4.97195e+06 | 0.188928 | 1(Win) | true |
| Jsonifier (generic) | 959.251 | 0.79417 | 7312.55ms | 5212421 | 40 | 6.77488e+10 | 5.18212e+06 | 0.525889 | 2(Loss) | true |
