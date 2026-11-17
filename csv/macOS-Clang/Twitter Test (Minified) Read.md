
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8324.52 | 0.138049 | 5567.71ms | 466906 | 320 | 1.74485e+06 | 53489.7 | 0.0123782 | 1(Win) | true |
| simdjson (stage-1) | 7758.62 | 0.0783308 | 5969.83ms | 466906 | 2560 | 5.17364e+06 | 57391.2 | 0.0990427 | 2(Loss) | true |
