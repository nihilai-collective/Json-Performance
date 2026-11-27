
----
### Twitter Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2015.18 | 0.187969 | 8796.11ms | 360584 | 320 | 3.29236e+07 | 170644 | 0.186606 | 1(Win) | true |
| simdjson (ondemand) | 1844.79 | 0.0964952 | 9649.4ms | 360584 | 640 | 2.07067e+07 | 186406 | 0.13102 | 2(Loss) | true |
