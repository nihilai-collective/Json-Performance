
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (stage-1) | 6875.55 | 0.18971 | 2572.93ms | 183677 | 4890 | 1.14231e+07 | 25476.9 | 2.03504 | 1(Win) | true |
| Jsonifier (stage-1) | 6422.61 | 0.41142 | 2910.09ms | 183677 | 640 | 8.05817e+06 | 27273.6 | 0.979324 | 2(Loss) | true |
