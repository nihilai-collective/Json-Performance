
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1348.42 | 0.256997 | 6673.01ms | 360584 | 640 | 2.74915e+08 | 255024 | 0.681715 | 1.8358 | 1(Win) | true |
| simdjson (ondemand) | 1148.16 | 0.382065 | 7754.85ms | 360584 | 320 | 4.19019e+08 | 299506 | 0.29835 | 2.15597 | 2(Loss) | true |
