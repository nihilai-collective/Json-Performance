
----
### Stream Formats Large Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 9712.68 | 0.142301 | 10083.8ms | 16197086 | 320 | 1.63892e+09 | 1.59037e+06 | 0.117887 | 1(Win) | true |
| simdjson (ondemand) | 8680.6 | 0.198175 | 5564.29ms | 16197086 | 160 | 1.98972e+09 | 1.77946e+06 | 0.216829 | 2(Loss) | true |
