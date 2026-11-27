
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 9134.14 | 0.0883293 | 7794.76ms | 5373214 | 160 | 3.92883e+07 | 561005 | 0.0792235 | 1(Win) | true |
| simdjson (stage-1) | 7985.03 | 0.145188 | 8270.57ms | 5373214 | 80 | 6.94494e+07 | 641738 | 0.0763511 | 2(Loss) | true |
